/**
 * Copyright 2012 Batis Degryll Ludo
 * @file VoidCollisioner.h
 * @since 2017-01-28
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Collisionator with no avatars.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONATOR_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONATOR_H_

#include <memory>

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/AvatarEntity.h"


namespace zbe {

/** \brief Collisionator with no avatars.
*/
template <typename R>
class VoidCollisionator : public zbe::CollisionatorCommon<R, void> {
public:

  /** \brief Parametric constructor.
   *  \param collisionObject
   *  \param reactObject
   *  \param actuatorsList
   *  \param collisionablesListId
   */
  VoidCollisionator(std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList, uint64_t collisionablesListId)
    : CollisionatorCommon<R, void>(std::make_shared<WeakAvatarEntityContainer<void> >((WeakAvatarEntityContainer<void>*)nullptr), collisionObject, reactObject, actuatorsList, collisionablesListId) {}
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONATOR_H_
