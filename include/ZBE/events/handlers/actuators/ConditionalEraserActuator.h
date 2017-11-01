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

#include <memory>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/entities/avatars/InteractionTester.h"

#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Actuator capable of erasing an entity if collisiondata meets a condition.
 */
template <typename R>
class ConditionalEraserActuator: public zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Avatar>, R> {
  public:
    void act(std::shared_ptr<WeakAvatarEntityContainer<InteractionTester> > ro) {
      InteractionTester* it;
      ro->get()->assignAvatar(&it);
      zbe::CollisionData * cd = zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Avatar>, R>::getCollisionData();
      if (it->test(cd)){
        zbe::Avatar * a;
        zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Avatar>, R>::getCollisioner()->get()->assignAvatar(&a);
        a->setERASED();
      }
    }
};

}  // namespace zbe

#endif // ZBE_EVENTS_HANDLERS_ACTUATORS_CONDITIONALERASERACTUATOR
