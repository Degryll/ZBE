/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableBouncer.h
 * @since 2016-12-17
 * @date 2016-12-18
 * @author Ludo
 * @brief Actuator capable of making a Movable bounce in a Bounceable.
 */

#ifndef ZBE_ACTUATORS_MOVABLEBOUNCER
#define ZBE_ACTUATORS_MOVABLEBOUNCER

#include "ZBE/core/handlers/collision/Actuator.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/Bounceable.h"

namespace zbe {

    class Bounceable;

/** \brief Actuator capable of making a Movable bounce in a Bounceable.
 */
template <typename R, unsigned s>
class MovableBouncer: public Actuator<Movable<s>, R> {
  public:
    void act(Bounceable * b) {
      Movable<s> * m = Actuator<Movable<s>, R>::getCollisioner();
      CollisionData * cd = Actuator<Movable<s>, R>::getCollisionData();
      Vector<s> v = m->getVelocity();
      Vector<s> n = m->getPosition() - cd->getPoint();
      v*=b->getFactor();
      m->setVelocity(v.reflect(n));
    }
};

}  // namespace

#endif //ZBE_ACTUATORS_MOVABLEBOUNCER