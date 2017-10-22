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

namespace ludo {

template <typename R>
class DestroyerReactObject;

/** \brief Actuator capable of making a MovableCollisioner bounce in a Bounceable.
 */
template <typename R>
class AvatarEraser: public zbe::Actuator<zbe::Avatar, R> {
  public:
    void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<Destroyer> >) {
      zbe::Avatar * a = zbe::Actuator<zbe::Avatar, R>::getCollisioner();
      a->setERASED();
    }
};

/** \brief Actuator capable of making a Bouncer bounce in a Bounceable.
 */
template <typename R>
class LudoBallBouncer: public zbe::Actuator<zbe::Bouncer<2>, R> {
  public:
    void act() {
      zbe::Bouncer<2> * gb = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisioner();
      zbe::CollisionData * cd = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisionData();
      zbe::Vector<2> n = gb->getPosition() - cd->getPoint();
      gb->addNormal(n);
    }
};

/** \brief Actuator capable of making a Bouncer get Annoyed by a Destroyer.
 */
template <typename R>
class BouncerAnnoyer: public zbe::Actuator< zbe::Bouncer<2>, R> {
  public:
    void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<Destroyer> >) {
      zbe::Bouncer<2> * gb = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisioner();
      zbe::Vector<2> v = gb->getVelocity();
      v.setCartesian(100,100);
      gb->setVelocity(v);
    }
};

}  // namespace

#endif //LUDO_EVENTS_HANDLERS_LUDOACTUATORS
