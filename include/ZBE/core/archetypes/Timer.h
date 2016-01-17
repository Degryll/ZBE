/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2014-09-09
 * @date 2015-12-01
 * @author Ludo and Degryll
 * @brief Abstract timer class.
 */

#ifndef CORE_TIMER_H_
#define CORE_TIMER_H_

namespace zbe {

/** \brief An abstract class to inform about time.
 *
 *  Declare the basic functions of every Timer.
 */
class Timer {
  public:
    virtual ~Timer() {}  //!< Virtual destructor for inheritance.

    virtual void restart() = 0;  //!< Set the Timer to zero.
    virtual void pause()   = 0;  //!< Pause the Timer, stop counting.
    virtual void resume()  = 0;  //!< Resume the Timer, continue the counting.

    virtual unsigned int getMilliseconds() = 0;  //!< Get the elapsed time in milliseconds.
};

}  // namespace zbe

#endif  // CORE_TIMER_H_
