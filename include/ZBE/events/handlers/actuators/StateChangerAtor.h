/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateChangerAtor.h
 * @since 2017-08-05
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of change an entity state.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_STATECHANGERATOR_H_
#define ZBE_EVENTS_HANDLERS_ACTUATORS_STATECHANGERATOR_H_

#include <memory>
#include <cstdint>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/AvatarEntity.h"



namespace zbe {

/** \brief Actuator capable of change an entity state.
 */
template <typename R, typename T>
class StateChangerSelfAtor: public zbe::Actuator<WeakAvatarEntityContainer<zbe::Stated>, R> {
  public:
    StateChangerSelfAtor(int64_t value) : v(value) {}

    /** \brief Set given state to entity when interact whit template type.
     *  \param entity. Not used.
     */
    void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<T> >) {
      zbe::Stated * s;
      zbe::Actuator<WeakAvatarEntityContainer<zbe::Stated>, R>::getCollisioner()->get()->assignAvatar(&s);
      s->add(v);
    }
  private:
    int64_t v;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_ACTUATORS_STATECHANGERATOR_H_
