/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2016-03-23
 * @date 2018-03-25
 * @author Batis Degryll Ludo
 * @brief Stopwatch interface. A timer that can Start, Stop or Reset a time count.
 */

#ifndef ZBE_CORE_TOOLS_TIME_TIMER_H_
#define ZBE_CORE_TOOLS_TIME_TIMER_H_

#include <cstdint>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Stopwatch interface. A timer that can Start, Stop or Reset a time count.
 *  It can return elapsed times from the beginning or from the last lap.
*/
class ZBEAPI Timer {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Timer() {}

  /** \brief Starts counting.
  */
  virtual void start() = 0;

  /** \brief Stops counting. Returns the lap time at this point.
  */
  virtual int64_t stop() = 0;

  /** \brief Stops counting and sets to 0 all the saved times.
  */
  virtual void reset() = 0;

  /** \brief Returns the lap time: the time since the last lap time or since the beginning.
  */
  virtual int64_t lapTime() = 0;

  /** \brief Returns the amount of time the timer has been active from the start.
  */
  virtual int64_t totalTime() = 0;

  /** \brief Returns true if the timer is running, and false otherwise.
  */
  virtual bool isRunning() = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_TIME_TIMER_H_
