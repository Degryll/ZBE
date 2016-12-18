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

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/Bounceable.h"

namespace zbe {


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
      //n.setPolars(1.0, n.getRads()+RECTRADS);
      v = v.reflect(n);
      v *= b->getFactor();
      m->setVelocity(v);
    }
};

}  // namespace

#endif //ZBE_ACTUATORS_MOVABLEBOUNCER
