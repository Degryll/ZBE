/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventGenerator.h
 * @since 2016-08-17
 * @date 2016-08-19
 * @author Degryll
 * @brief Generate time events.
 */

#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/TimeEvent.h"

namespace zbe {


void TimerTicket::setACTIVE() {
  if(s != ERASED) {
    if((s == INACTIVE) && (td.time > 0)) {
      td.time += contextTime->getEventTime();
      iter = timers.insert(td);
    }
    s = ACTIVE;
  }
}

void TimerTicket::setINACTIVE() {
  if(s != ERASED) {
    if(s == ACTIVE) {
      td = (*iter);
      timers.erase(iter);
      td.time -= contextTime->getEventTime();
    }
    s = INACTIVE;
  }
}

void TimerTicket::setERASED() {
  if(s != ERASED) {
    if(s == ACTIVE){
      timers.erase(iter);
    }
    s = ERASED;
  }
}

void TimerTicket::toggle() {
  if(s == ACTIVE) {
    setINACTIVE();
  } else if(s == INACTIVE) {
    setACTIVE();
  }
}  //!< Set the state as state.

void TimerTicket::setState(State state) {
  if(state == ACTIVE) this->setACTIVE();
  if(state == INACTIVE) this->setINACTIVE();
  if(state == ERASED) this->setERASED();
}

bool TimerTicket::increaseTime(uint64_t increment) {
  // Copy the handler before erasing the node: iter becomes invalid after
  // erase(), including when the timer expires immediately.
  TimerData data = (*iter);
  std::shared_ptr<TimeHandler> handler = data.handler;
  timers.erase(iter);
  data.time += zbe::quantizeTime(increment);
  if(data.time>0){
    iter = timers.insert(data);
    return (false);
  } else {
    store->storeInstantEvent(
      new TimeEvent(
      eventId,
      0u,
      handler)
      );
    s = ERASED;
    return (true);
  }

}

void TimeEventGenerator::run() {
  if(contextTime->isPaused()) {
    return;
  }
  uint64_t currentTotalPausedTime = contextTime->getTotalPausedTime();
  if(currentTotalPausedTime > lastTotalPausedTime) {
    uint64_t pausedTime = currentTotalPausedTime - lastTotalPausedTime;
    std::multiset<TimerData> newTimers;

    // Timers use absolute times. Add the time spent paused so that the pause
    // does not consume any of their active lifetime.
    for(auto it = timers.begin(); it != timers.end(); ++it) {
      TimerData td = (*it);
      td.time += pausedTime;
      newTimers.insert(td);
    }

    // Assigning a new multiset destroys the old nodes and invalidates every
    // TimerTicket::iter. Save each active ticket's position before replacing
    // the container so its iterator can be rebuilt afterwards.
    std::vector<std::pair<std::shared_ptr<TimerTicket>, std::size_t>> bindings;
    for(auto& weakTicket : timerTickets) {
      auto ticket = weakTicket.lock();
      if(!ticket || !ticket->isACTIVE()) {
        continue;
      }
      std::size_t index = 0;
      for(auto it = timers.begin(); it != timers.end(); ++it, ++index) {
        if(ticket->iter == it) {
          bindings.emplace_back(ticket, index);
          break;
        }
      }
    }

    timers = newTimers;
    for(const auto& binding : bindings) {
      // Recreate the iterator into the new container. The position is stable
      // because both multisets contain the same timers in sorted order.
      auto it = timers.begin();
      std::advance(it, static_cast<std::ptrdiff_t>(binding.second));
      binding.first->iter = it;
    }
  }
  lastTotalPausedTime = currentTotalPausedTime;
  auto timersToEraseEnd = timers.upper_bound(TimerData(0,contextTime->getInitFrameTime()));
  // Mark tickets before erasing their nodes. Otherwise they would keep a
  // dangling iterator and crash on the next ticket operation.
  for(auto& weakTicket : timerTickets) {
    auto ticket = weakTicket.lock();
    if(!ticket || !ticket->isACTIVE()) {
      continue;
    }
    for(auto it = timers.begin(); it != timersToEraseEnd; ++it) {
      if(ticket->iter == it) {
        ticket->s = Ticket::ERASED;
        break;
      }
    }
  }
  timers.erase(timers.begin(), timersToEraseEnd);
  int64_t v = 0;
  auto it = timers.begin();
  if (timers.size() > 0) {
    v = static_cast<int64_t>(it->time);
  }

  for(; it != timers.end(); ++it) {
    if((it->time > contextTime->getEndFrameTime())
    || (static_cast<int64_t>(it->time) != v)) {
      break;
    }
    store->storeEvent(new TimeEvent(eventId, static_cast<uint64_t>(v), it->handler));
  }  // for each timer
}

}  // namespace zbe
