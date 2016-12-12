/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Actor.h
 * @since 2016-12-11
 * @date 2016-12-11
 * @author Batis
 * @brief First Actuator interface.
 */

#ifndef CORE_HANDLERS_COLLISION_ACTOR_H
#define CORE_HANDLERS_COLLISION_ACTOR_H

#include "ZBE/core/entities/avatars/ReactObject.h"
#include "ZBE/core/tools/math/collisions/CollisionData.h"

namespace zbe {

/** \brief Entity that can be seen as a collisionator using an adaptor.
 */
template <typename T>
class Actor {
  public:

    void act(T collisioner, ReactObject rObject, CollisionData cData){

    };
};
}

#endif //CORE_HANDLERS_COLLISION_ACTOR_H
