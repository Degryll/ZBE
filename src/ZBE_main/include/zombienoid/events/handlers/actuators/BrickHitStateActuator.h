/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BrickHitStateActuator.h
 * @since 2017-08-05
 * @date 2017-08-05
 * @author Batis Degryll Ludo
 * @brief Actuator capable of modify the state of a brick when it is hit.
 */

#ifndef ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BRICKHITSTATEACTUATOR_H
#define ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BRICKHITSTATEACTUATOR_H

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/AvatarEntity.h"


namespace zombienoid {

/** \brief Actuator capable of modify the state of a brick when it is hit.
 */
template <typename R, typename T>
class BrickHitStateActuator: public zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Stated>, R> {
  public:
    BrickHitStateActuator(int64_t increment, int64_t highLimit, int64_t deadValue) : increment(increment), highLimit(highLimit), deadValue(deadValue) {}

    void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<T> >) {
      zbe::Stated* s;
      zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Stated>, R>::getCollisioner()->get()->assignAvatar(&s);
      if(s->getState()<highLimit) {
        s->add(increment);
      } else {
        s->setState(deadValue);
      }
    }

  private:
    int64_t increment;
    int64_t highLimit;
    int64_t deadValue;
};

}  // namespace zombienoid

#endif // ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_BRICKHITSTATEACTUATOR_H
