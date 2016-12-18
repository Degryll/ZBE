/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Reactor.h
 * @since 2016-12-11
 * @date 2016-12-12
 * @author Batis Ludo
 * @brief Second Actuator interface.
 */

#ifndef CORE_HANDLERS_COLLISION_ZOMBIENOIDREACTOR_H
#define CORE_HANDLERS_COLLISION_ZOMBIENOIDREACTOR_H

#include "ZBE/core/entities/avatars/ReactObject.h"
#include "ZBE/core/tools/math/collisions/CollisionData.h"

namespace zbe {
class ZombienoidReactor {
  public:
      void act(Bounceable * b) {};

};

}  // namespace

#endif //CORE_HANDLERS_COLLISION_ZOMBIENOIDREACTOR_H

