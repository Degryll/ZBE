/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Runnable.h
 * @since 2014-09-08
 * @date 2014-09-08
 * @author Ludo and Degryll
 * @brief Define a class with a void run(void) function.
 */

#ifndef CORE_ARCHETYPES_RUNNABLE_H_
#define CORE_ARCHETYPES_RUNNABLE_H_

namespace zbe {

class Runnable {
  public:
    virtual ~Runnable() {}

    virtual void run() = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_RUNNABLE_H_
