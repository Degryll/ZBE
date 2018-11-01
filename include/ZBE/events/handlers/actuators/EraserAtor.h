/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EraserAtor.h
 * @since 2017-06-25
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of erasing an entity.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_ERASERATOR_H_
#define ZBE_EVENTS_HANDLERS_ACTUATORS_ERASERATOR_H_

#include <memory>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Actuator capable of erasing an entity.
 */
template <typename R, typename T>
class EraserAtor: public zbe::Actuator<WeakAvatarEntityContainer<zbe::Avatar>, R> {
  public:

    /** \brief Erases entity when interact with template given ReactObject.
     *  \param ro not used.
     */
    void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<T> >) {
      zbe::Avatar * a;
      zbe::Actuator<WeakAvatarEntityContainer<zbe::Avatar>, R>::getCollisioner()->get()->assignAvatar(&a);
      a->setERASED();
    }
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_ACTUATORS_ERASERATOR_H_
