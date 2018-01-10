/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TimeEventGenerator.h
 * @since 2016-08-17
 * @date 2016-08-19
 * @author Degryll
 * @brief Generate time events.
 */

#ifndef CORE_EVENTS_TIMEEVENTGENERATOR_H
#define CORE_EVENTS_TIMEEVENTGENERATOR_H

#include <memory>
#include <set>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

struct TimerData {
  std::shared_ptr<TimeHandler> handler;    //!< A handler that will be executed when the event is triggered.
  int64_t time;  //!< When time reaches 0, the time event is triggered.

  TimerData(std::shared_ptr<TimeHandler> handler, int64_t time) : handler(handler), time(time) {}
  inline bool operator<(const TimerData& rhs) const {return (this->time < rhs.time);}
};

class TimerTicket {
public:

  TimerTicket(const TimerTicket&) = delete;
  void operator=(const TimerTicket&) = delete;

  TimerTicket(std::multiset<TimerData>::iterator iter, std::multiset<TimerData>& timers, int eventId) : iter(iter), timers(timers), eventId(eventId), es(EventStore::getInstance()), sysTime(SysTime::getInstance()) {}

  /**
   * return true if the increment makes the timer go to zero or less.
   */
  bool increaseTime(int64_t increment) {
    TimerData td = (*iter);
    timers.erase(iter);
    td.time += increment;
    if(td.time>0){
      iter = timers.insert(td);
      return (false);
    } else {
      es.storeInstantEvent(new TimeEvent(eventId, 0, iter->handler));
      return (true);
    }

  }

  void erase() {
    timers.erase(iter);
  }

  int64_t getTime() {
    return (iter->time);
  }

private:
  std::multiset<TimerData>::iterator iter;
  std::multiset<TimerData>& timers;
  int eventId;
  EventStore& es;
  SysTime &sysTime;
};

/** \brief Generate collision events.
 */
class TimeEventGenerator : virtual public Daemon {
  public:
    /** \brief Empty Constructor.
     */
    TimeEventGenerator(int eventId) : eventId(eventId), es(EventStore::getInstance()), timers(), sysTime(SysTime::getInstance()) {};

//    /** \brief Empty destructor.
//    */
//    ~TimeEventGenerator() {};

    /** Add a new Timer that only triggers onces.
     * \param id Id of the Timer, to identify the action to accomplish when the event is triggered
     * \param time Time to wait until the time event is triggered
     * \return return An iterator used to erase the timer.
     * \sa eraseTimer
     */
    inline std::shared_ptr<TimerTicket> addTimer(std::shared_ptr<TimeHandler> handler, int64_t time) {
      return (std::make_shared<TimerTicket>(timers.insert(TimerData(handler,quantizeTime(time))), timers, eventId));
    }

    /** Will search for time events occurred between initTime and finalTime and send it to the EventStore.
     * \param initTime Initial time of the frame
     * \param endTime End time of the frame
     */
    void run();

  private:
    int eventId;
    EventStore& es;
    std::multiset<TimerData> timers;
    SysTime &sysTime;
};

}  // namespace zbe

#endif // CORE_EVENTS_TIMEEVENTGENERATOR_H
