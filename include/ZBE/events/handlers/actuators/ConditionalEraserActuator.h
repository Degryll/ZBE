/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ConditionalEraserActuator.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of erasing an entity if collisiondata meets a condition.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_CONDITIONALERASERACTUATOR
#define ZBE_EVENTS_HANDLERS_ACTUATORS_CONDITIONALERASERACTUATOR

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/events/ReactObjects/InteractionTesterRO.h"

namespace zbe {

/** \brief Actuator capable of erasing an entity if collisiondata meets a condition.
 */
template <typename R>
class ConditionalEraserActuator: public zbe::Actuator<zbe::Avatar, R> {
  public:
    void act(InteractionTesterRO<R> *ro) {
      zbe::CollisionData * cd = zbe::Actuator<zbe::Avatar, R>::getCollisionData();
      if (ro->test(cd)){
        zbe::Avatar * a = zbe::Actuator<zbe::Avatar, R>::getCollisioner();
        a->setERASED();
      }
    }
};

}  // namespace zbe

#endif // ZBE_EVENTS_HANDLERS_ACTUATORS_CONDITIONALERASERACTUATOR
