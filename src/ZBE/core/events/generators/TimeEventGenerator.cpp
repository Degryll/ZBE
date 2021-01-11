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


inline void TimerTicket::setACTIVE() {
  if(s != ERASED) {
    if((s == INACTIVE) && (td.time > 0)) {
      td.time += contextTime->getEventTime();
      iter = timers.insert(td);
    }
    s = ACTIVE;
  }
}

inline void TimerTicket::setINACTIVE() {
  if(s != ERASED) {
    if(s == ACTIVE) {
      td = (*iter);
      timers.erase(iter);
      td.time -= contextTime->getEventTime();
    }
    s = INACTIVE;
  }
}

inline void TimerTicket::setERASED() {
  if(s != ERASED) {
    if(s == ACTIVE){
      timers.erase(iter);
    }
    s = ERASED;
  }
}

inline void TimerTicket::toggle() {
  if(s == ACTIVE) {
    s = INACTIVE;
  } else if(s == INACTIVE) {
    s = ACTIVE;
  }
}  //!< Set the state as state.

inline void TimerTicket::setState(State state) {
  if(state == ACTIVE) this->setACTIVE();
  if(state == INACTIVE) this->setINACTIVE();
  if(state == ERASED) this->setERASED();
}

bool TimerTicket::increaseTime(int64_t increment) {
  TimerData data = (*iter);
  timers.erase(iter);
  data.time += zbe::quantizeTime(increment);
  if(data.time>0){
    iter = timers.insert(data);
    return (false);
  } else {
    es.storeInstantEvent(new TimeEvent(eventId, 0, iter->handler));
    return (true);
  }

}

void TimeEventGenerator::run() {
  timers.erase(timers.begin(),timers.upper_bound(TimerData(0,contextTime->getInitFrameTime())));

  int64_t v = 0;
  auto it = timers.begin();
  if (timers.size() > 0) {
    v = it->time;
  }

  for(; it != timers.end(); ++it) {
    if((it->time > contextTime->getEndFrameTime())
    || (it->time != v)) {
      break;
    }
    es.storeEvent(new TimeEvent(eventId, v, it->handler));
  }  // for each timer
}

}  // namespace zbe
