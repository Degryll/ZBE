/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Behavior.h
 * @since 2014-09-12
 * @date 2016-04-29
 * @author Ludo and Degryll
 * @brief Define the minimal functions of every behavior.
 */

#ifndef CORE_BEHAVIORS_BEHAVIOR_H_
#define CORE_BEHAVIORS_BEHAVIOR_H_

namespace zbe {

template<typename T>

/** \brief Define the minimal functions of every behavior.
 */
class Behavior {
  public:

    /** \brief Default destructor.
     */
    virtual ~Behavior() {}

    /** \brief Do the behavior work over the given entity
     */
    virtual void apply(T * entity) = 0;
};

}  // namespace zbe

#endif  // CORE_BEHAVIORS_BEHAVIOR_H_
