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
#include <forward_list>

#include "ZBE/core/events/EventStore.h"

namespace zbe {

struct TimerData {
  uint64_t id;    //!< id to identify what timer trigger the event.
  uint64_t time;  //!< When time reaches 0, the time event is triggered.

  TimerData(uint64_t id, uint64_t time) : id(id), time(time) {}
};

struct RepeatdTimerData {
  uint64_t id;         //!< id to identify what timer trigger the event.
  uint64_t time;       //!< When time reaches 0, the time event is triggered.
  uint64_t totalTime;  //!< Total time of the timer to generate a new one when the event is triggered.

  RepeatdTimerData(uint64_t id, uint64_t time, uint64_t totalTime) : id(id), time(time), totalTime(totalTime) {}
};

typedef std::forward_list<RepeatdTimerData>::iterator repeatdIter;

/** \brief Generate collision events.
 */
class TimeEventGenerator {
  public:
    /** \brief Empty Constructor.
     */
    TimeEventGenerator(int eventId) : eventId(eventId), es(EventStore::getInstance()), timers(), repeatdTimers(), iter(repeatdTimers.before_begin()) {};

//    /** \brief Empty destructor.
//    */
//    ~TimeEventGenerator() {};

    /** Add a new Timer that only triggers onces.
     * \param id Id of the Timer, to identify the action to accomplish when the event is triggered
     * \param time Time to wait until the time event is triggered
     * \sa addRepeatedTimer
     */
    inline void addTimer(uint64_t id, uint64_t start, uint64_t time);

    /** Add a new Timer that triggers many times (until is erased).
     * \param id Id of the Timer, to identify the action to accomplish when the event is triggered
     * \param time Time to wait until the time event is triggered
     * \return return An iterator used to erase the timer.
     * \sa addTimer, eraseRepeatedTimer
     */
    inline repeatdIter addRepeatedTimer(uint64_t id, uint64_t start, uint64_t time);

    /** Erase a repeatedTimer.
     * \param it Iterator to the timer
     * \sa addRepeatedTimer
     */
    inline void eraseRepeatedTimer(repeatdIter it);

    /** Will search for time events occurred between initTime and finalTime and send it to the EventStore.
     * \param initTime Initial time of the frame
     * \param endTime End time of the frame
     */
    void generate(uint64_t initTime, uint64_t endTime);

  private:
    int eventId;
    EventStore& es;
    std::forward_list<TimerData> timers;
    std::forward_list<RepeatdTimerData> repeatdTimers;
    repeatdIter iter;
};

}  // namespace zbe

#endif // CORE_EVENTS_TIMEEVENTGENERATOR_H
