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

#include <cstdint>
#include <set>

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

namespace zbe {

struct TimerData {
  TimeHandler* handler;    //!< A handler that will be executed when the event is triggered.
  uint64_t time;  //!< When time reaches 0, the time event is triggered.

  TimerData(TimeHandler* handler, uint64_t time) : handler(handler), time(time) {}
  inline bool operator<(const TimerData& rhs) const {return (this->time < rhs.time);}
};

typedef std::multiset<TimerData>::iterator TimerIter;

/** \brief Generate collision events.
 */
class TimeEventGenerator {
  public:
    /** \brief Empty Constructor.
     */
    TimeEventGenerator(int eventId) : eventId(eventId), es(EventStore::getInstance()), timers() {};

//    /** \brief Empty destructor.
//    */
//    ~TimeEventGenerator() {};

    /** Add a new Timer that only triggers onces.
     * \param id Id of the Timer, to identify the action to accomplish when the event is triggered
     * \param time Time to wait until the time event is triggered
     * \return return An iterator used to erase the timer.
     * \sa eraseTimer
     */
    inline TimerIter addTimer(TimeHandler* handler, uint64_t time) {
      return (timers.insert(TimerData(handler,time)));
    }

    /** Erase a Timer.
     * \param it Iterator to the timer
     * \sa addTimer
     */
    inline void eraseTimer(TimerIter it) {
      timers.erase(it);
    }

    /** Will search for time events occurred between initTime and finalTime and send it to the EventStore.
     * \param initTime Initial time of the frame
     * \param endTime End time of the frame
     */
    void generate(uint64_t initTime, uint64_t endTime);

  private:
    int eventId;
    EventStore& es;
    std::multiset<TimerData> timers;
};

}  // namespace zbe

#endif // CORE_EVENTS_TIMEEVENTGENERATOR_H
