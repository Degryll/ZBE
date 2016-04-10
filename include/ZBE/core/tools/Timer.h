/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2016-03-23
 * @date 2016-03-24
 * @author Batis
 * @brief Define a timer that gives elapsed times between events.
 */

#ifndef CORE_TOOLS_TIMER_H_
#define CORE_TOOLS_TIMER_H_

#include <stdint.h>

namespace zbe {

/** \brief Stopwatch interface. A timer that can Start, Stop or Reset a time count.
 *
 * It can return elapsed times from the beginning or from the last lap.
*/
class Timer {
  public:

    /** \brief Starts counting.
     *
    */
    virtual void start() {}

    /** \brief Stops counting. Returns the lap time at this point.
     *
    */
    virtual uint64_t stop() {}

    /** \brief Stops counting and sets to 0 all the saved times.
     *
    */
    virtual void reset() {}


    /** \brief Returns the lap time: the time since the last lap time or since the beginning.
     *
    */
    virtual uint64_t lapTime() {}

    /** \brief Returns the amount of time the timer has been active from the start.
     *
    */
    virtual uint64_t totalTime() {}

    /** \brief Returns true if the timer is running, and false otherwise.
     *
    */
    virtual bool running() {}

};

}  // namespace zbe

#endif  // CORE_TOOLS_TIMER_H_
