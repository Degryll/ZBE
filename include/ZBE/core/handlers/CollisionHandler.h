/**
 * Copyright 2015 Batis Degryll Ludo
 * @file CollisionHandler.h
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
  class CollisionHandler {
    public:

      /** \brief Do the Handler job.
       */
      virtual void run(CollisionEvent* e) = 0;

      /** \brief Destructor.
       */
      virtual ~CollisionHandler(){};
  };

}  // namespace zbe

#endif // CORE_GUARDS_COLLISIONGUARD_H
