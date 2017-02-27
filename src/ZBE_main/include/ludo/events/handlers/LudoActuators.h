/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoActuators.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Collection of zbe::Actuators for ludomain.
 */

#ifndef LUDO_EVENTS_HANDLERS_LUDOACTUATORS
#define LUDO_EVENTS_HANDLERS_LUDOACTUATORS

#include <cstdio>
#include <stdlib.h>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/entities/avatars/MovableCollisioner.h"
#include "ZBE/reactobjects/VoidReactObject.h"

namespace ludo {

/** \brief Actuator capable of making a MovableCollisioner bounce in a Bounceable.
 */
template <typename R>
class MovableCollisionerBouncer: public zbe::Actuator<zbe::MovableCollisioner<R, 2>, R> {
  public:
    void act(zbe::VoidReactObject<R>*) {
      zbe::MovableCollisioner<R, 2> * gb = zbe::Actuator<zbe::MovableCollisioner<R, 2>, R>::getCollisioner();
      zbe::CollisionData * cd = zbe::Actuator<zbe::MovableCollisioner<R, 2>, R>::getCollisionData();
      zbe::Vector<2> v = gb->getVelocity();
      zbe::Point<2> p = cd->getPoint();
      zbe::Point<2> c = gb->getPosition();
      zbe::Vector<2> n = c - p;
      v.reflect(n);
      gb->setVelocity(v);
    }
};
}  // namespace

#endif //LUDO_EVENTS_HANDLERS_LUDOACTUATORS
