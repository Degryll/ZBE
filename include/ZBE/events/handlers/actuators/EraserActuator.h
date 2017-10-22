/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EraserActuator.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of erasing an entity.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_ERASERACTUATOR
#define ZBE_EVENTS_HANDLERS_ACTUATORS_ERASERACTUATOR

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/avatars/Avatar.h"

namespace zbe {

/** \brief Actuator capable of erasing an entity.
 */
template <typename R, typename T>
class EraserActuator: public zbe::Actuator<zbe::Avatar, R> {
  public:
    void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<T> >) {
      zbe::Avatar * a = zbe::Actuator<zbe::Avatar, R>::getCollisioner();
      a->setERASED();
    }
};

}  // namespace zbe

#endif // ZBE_EVENTS_HANDLERS_ACTUATORS_ERASERACTUATOR
