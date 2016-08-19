/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventGenerator.h
 * @since 2016-08-17
 * @date 2016-08-19
 * @author Degryll
 * @brief Generate time events.
 */

#include "ZBE/core/events/TimeEventGenerator.h"

#include "ZBE/core/events/EventDispatcher.h"

namespace zbe {

void TimeEventGenerator::addTimer(uint64_t id, uint64_t start, uint64_t time) {
  timers.push_front(TimerData(id,start+time));
}

repeatdIter TimeEventGenerator::addRepeatedTimer(uint64_t id, uint64_t start, uint64_t time) {
  repeatdIter it = iter;
  iter = repeatdTimers.insert_after(it, RepeatdTimerData(id, start+time, time));
  return (it);
}

void TimeEventGenerator::eraseRepeatedTimer(repeatdIter it) {
  repeatdTimers.erase_after(it);
}

void TimeEventGenerator::generate(uint64_t initTime, uint64_t endTime) {
  uint64_t duration = endTime - initTime + 1;  // +1 inclusive endTime

  auto pre = timers.before_begin();
  auto it =  timers.begin();
  while (it != timers.end()) {
    uint64_t time = it->time;
    if ((time - initTime) < duration) {
      es.storeEvent(new TimeEvent(eventId, time, it->id));
      it = timers.erase_after(pre);
    } else {
      pre = it;
      ++it;
    }
  }  // while timers

  for (auto it = repeatdTimers.begin(); it != repeatdTimers.end(); ++it) {
    uint64_t time = it->time;
    if ((time - initTime) < duration) {
      es.storeEvent(new TimeEvent(eventId, time, it->id));
      it->time += it->totalTime;
    }
  }
}

}  // namespace zbe
