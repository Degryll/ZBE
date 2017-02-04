/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2016-03-23
 * @date 2016-04-04
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
    virtual void start() = 0;

    /** \brief Stops counting. Returns the lap time at this point.
     *
    */
    virtual int64_t stop() = 0;

    /** \brief Stops counting and sets to 0 all the saved times.
     *
    */
    virtual void reset() = 0;


    /** \brief Returns the lap time: the time since the last lap time or since the beginning.
     *
    */
    virtual int64_t lapTime() = 0;

    /** \brief Returns the amount of time the timer has been active from the start.
     *
    */
    virtual int64_t totalTime() = 0;

    /** \brief Returns true if the timer is running, and false otherwise.
     *
    */
    virtual bool isRunning() = 0;

    virtual ~Timer(){};

};

}  // namespace zbe

#endif  // CORE_TOOLS_TIMER_H_
