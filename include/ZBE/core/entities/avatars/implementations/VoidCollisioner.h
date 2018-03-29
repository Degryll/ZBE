/**
 * Copyright 2012 Batis Degryll Ludo
 * @file VoidCollisioner.h
 * @since 2017-01-28
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Collsioner with no avatars.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONER_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONER_H_

#include <memory>

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Collsioner with no avatars.
*/
template <typename R>
class VoidCollisioner : public zbe::CollisionerCommon<R, void> {
public:

  /** \brief Parametric constructor.
   *  \param collisionObject
   *  \param reactObject
   *  \param actuatorsList
   */
  VoidCollisioner(std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList)
    : CollisionerCommon<R, void>(std::make_shared<WeakAvatarEntityContainer<void> >(), collisionObject, reactObject, actuatorsList) {}
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONER_H_
