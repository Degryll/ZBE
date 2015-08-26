/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Behavior.h
 * @since 2014-09-12
 * @date 2015-05-04
 * @author Ludo and Degryll
 * @brief Define the minimal functions of every behavior.
 */

#ifndef CORE_BEHAVIORS_BEHAVIOR_H_
#define CORE_BEHAVIORS_BEHAVIOR_H_

namespace zbe {

class Behavior {
  public:
    virtual ~Behavior() {}

    virtual void behaveUntil(double time) = 0;
};

}  // namespace zbe

#endif  // CORE_BEHAVIORS_BEHAVIOR_H_
