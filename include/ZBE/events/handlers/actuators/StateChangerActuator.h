/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateChangerActuator.h
 * @since 2017-08-05
 * @date 2017-08-05
 * @author Batis Degryll Ludo
 * @brief Actuator capable of erasing an entity.vaasdf
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_STATECHANGERACTUATOR
#define ZBE_EVENTS_HANDLERS_ACTUATORS_STATECHANGERACTUATOR

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/avatars/Avatar.h"


namespace zbe {

/** \brief Actuator capable of erasing an entity.
 */
template <typename R, typename T>
class StateChangerActuator: public zbe::Actuator<zbe::Stated, R> {
  public:
    StateChangerActuator(int64_t value) : v(value) {}

    void act(T*) {
      zbe::Stated * s = zbe::Actuator<zbe::Stated, R>::getCollisioner();
      s->add(v);
    }
  private:
    int64_t v;
};

}  // namespace zbe

#endif // ZBE_EVENTS_HANDLERS_ACTUATORS_STATECHANGERACTUATOR
