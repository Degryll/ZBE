/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncerActuator.h
 * @since 2017-06-25
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of making a entity bounce.
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTUATORS_BOUNCERACTUATOR
#define ZBE_EVENTS_HANDLERS_ACTUATORS_BOUNCERACTUATOR

#include <memory>

#include "ZBE/core/events/generators/util/CollisionData.h"
#include "ZBE/core/events/handlers/Actuator.h"

#include "ZBE/entities/avatars/Bouncer.h"

namespace zbe {

/** \brief Actuator capable of making a entity bounce.
 */
template <typename R, typename RO>
class BouncerActuator: public Actuator<WeakAvatarEntityContainer<Bouncer<2> >, R> {
  public:

    /** \brief Acumulates bounce normal when template type is collided.
     *  \param entity. Not used.
     */
    void act(std::shared_ptr< zbe::WeakAvatarEntityContainer<RO> > ) {
      Bouncer<2> * gb;
      Actuator<WeakAvatarEntityContainer<Bouncer<2> >, R>::getCollisioner()->get()->assignAvatar(&gb);
      CollisionData * cd = Actuator<WeakAvatarEntityContainer<Bouncer<2> >, R>::getCollisionData();
      gb->addNormal(cd->getNormal());
    }
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_ACTUATORS_BOUNCERACTUATOR
