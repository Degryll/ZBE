/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableBouncer.h
 * @since 2016-12-17
 * @date 2016-12-17
 * @author Ludo
 * @brief Actuator capable of making a Movable bounce in a Bounceable.
 */

#ifndef ZBE_ACTUATORS_MOVABLEBOUNCER
#define ZBE_ACTUATORS_MOVABLEBOUNCER

#include "ZBE/core/handlers/collision/Actuator.h"
#include "ZBE/core/entities/avatars/Bounceable.h"
#include "ZBE/core/entities/avatars/Movable2D.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

    class Bounceable;

/** \brief Actuator capable of making a Movable bounce in a Bounceable.
 */
template <typename R, unsigned s>
class MovableBouncer: public Actuator<Movable2D, R> {
  public:
    void act(Bounceable * b) {
      Movable2D * m = getCollisioner();
      CollisionData * cd = getCollisionData();
      Vector2D v = m->getVelocity();
      Vector2D n = m->getPosition() - cd->getPoint();
      v*=b->getFactor();
      m->setVelocity(v);
    }
};

}  // namespace

#endif //ZBE_ACTUATORS_MOVABLEBOUNCER
