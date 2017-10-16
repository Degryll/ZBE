/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncerActuator.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of making a entity bounce.
 */

#ifndef ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_CustomVectorBOUNCERACTUATOR
#define ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_CustomVectorBOUNCERACTUATOR

#include <cstdio>
#include <stdlib.h>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/entities/avatars/Bouncer.h"

#include "zombienoid/events/reactobjects/CustomVectorRO.h"

namespace zombienoid {

/** \brief Actuator capable of making a entity bounce.
 */
template <typename R>
class CustomVectorBouncerActuator: public zbe::Actuator<zbe::Bouncer<2>, R> {
  public:
    void act(CustomVectorRO* customVector) {
      zbe::Bouncer<2> * gb = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisioner();
      zbe::CollisionData * cd = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisionData();
      zbe::Vector2D v = customVector->getNormal(cd);
      v = v * (gb->getVelocity().getModule()/v.getModule());
      gb->setVelocity(v);
      //gb->addNormal(n);
    }
};

}  // namespace zombienoid

#endif // ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_ACTUATORS_CustomVectorBOUNCERACTUATOR
