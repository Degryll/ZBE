/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncerActuator.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of making a entity bounce.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_BOUNCERACTUATOR
#define ZBE_EVENTS_HANDLERS_ACTUATORS_BOUNCERACTUATOR

#include <cstdio>
#include <stdlib.h>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/reactobjects/VoidReactObject.h"

namespace zbe {

/** \brief Actuator capable of making a entity bounce.
 */
template <typename R>
class BouncerActuator: public Actuator<Bouncer<2>, R> {
  public:
    void act(VoidReactObject<R>*) {
      Bouncer<2> * gb = Actuator<Bouncer<2>, R>::getCollisioner();
      CollisionData * cd = Actuator<Bouncer<2>, R>::getCollisionData();
      Vector<2> n = gb->getPosition() - cd->getPoint();
      gb->addNormal(n);
    }
};

}  // namespace zbe

#endif // ZBE_EVENTS_HANDLERS_ACTUATORS_BOUNCERACTUATOR
