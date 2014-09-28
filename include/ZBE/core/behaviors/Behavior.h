/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Behavior.h
 * @since 2014-09-12
 * @date 2014-09-12
 * @author Ludo and Degryll
 * @brief Define the minimal functions of every behavior.
 */

#ifndef CORE_ARCHETYPES_BEHAVIOR_H_
#define CORE_ARCHETYPES_BEHAVIOR_H_

namespace zbe {

class Behavior {
  public:
    virtual ~Behavior() {}

    virtual void updateBehaviors(double time) = 0;

    virtual void behaveUntil(double time) = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_BEHAVIOR_H_
