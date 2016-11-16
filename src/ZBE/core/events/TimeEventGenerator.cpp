/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventGenerator.h
 * @since 2016-08-17
 * @date 2016-08-19
 * @author Degryll
 * @brief Generate time events.
 */

#include "ZBE/core/events/generators/TimeEventGenerator.h"

#include "ZBE/core/events/EventDispatcher.h"

namespace zbe {

void TimeEventGenerator::generate(uint64_t initTime, uint64_t endTime) {
  timers.erase(timers.begin(),timers.upper_bound(TimerData(0,initTime)));

  uint64_t v = 0;
  auto it = timers.begin();
  if (timers.size() > 0) {
    v = it->time;
  }

  for(; it != timers.end(); ++it) {
    if((it->time > endTime)
    || (it->time != v)) {
      break;
    }

    es.storeEvent(new TimeEvent(eventId, v, it->id));
  }  // for each timer
}

}  // namespace zbe
