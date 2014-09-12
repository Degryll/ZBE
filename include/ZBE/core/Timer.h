/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2014-09-09
 * @date 2014-09-09
 * @author Ludo and Degryll
 * @brief Abstract timer class.
 */

#ifndef CORE_TIMER_H_
#define CORE_TIMER_H_

namespace zbe {

class Timer {
  public:
    virtual ~Timer() {}

    virtual void restart() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual unsigned int getMilliseconds() = 0;
};

}  // namespace zbe

#endif  // CORE_TIMER_H_
