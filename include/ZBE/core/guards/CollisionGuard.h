/**
 * Copyright 2015 Batis Degryll Ludo
 * @file CollisionGuard.h
 * @since 2016-08-21
 * @date 2016-08-21
 * @author Degryll
 * @brief Receives a Collision event and reacts to that.
 */

#ifndef CORE_GUARDS_COLLISIONGUARD_H
#define CORE_GUARDS_COLLISIONGUARD_H

#include "ZBE/core/events/CollisionEvent.h"

namespace zbe {

  /** \brief Receives a Collision event and reacts to that.
   */
  class CollisionGuard {
    public:

      /** \brief Do the Guard job.
       */
      virtual void run(CollisionEvent* e) = 0;

      /** \brief Destructor.
       */
      virtual ~CollisionGuard(){};
  };

}  // namespace zbe

#endif // CORE_GUARDS_COLLISIONGUARD_H
