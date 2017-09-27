/**
 * Copyright 2012 Batis Degryll Ludo
 * @file VoidCollisioner.h
 * @since 2017-01-28
 * @date 2017-04-26
 * @author Degryll Batis Ludo
 * @brief Simple implementation for a collisioner.
 */

#ifndef CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONATOR_H_
#define CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONATOR_H_

#include <memory>

#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"

namespace zbe {

template <typename R>
class VoidCollisionator : public zbe::CollisionatorCommon<R, void> {
public:
  VoidCollisionator(std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList, uint64_t collisionablesListId)
  //AvatarEntityContainer<Bases...>* collisionator, std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList, uint64_t collisionablesListId
    //: CollisionatorCommon<R, void>(new AvatarEntityContainer<void>((AvatarEntityContainer<void>*)nullptr), collisionObject, reactObject, actuatorsList, collisionablesListId) {}
    : CollisionatorCommon<R, void>((AvatarEntityContainer<void>*)nullptr, collisionObject, reactObject, actuatorsList, collisionablesListId) {}
};

} // namespace zbe

#endif //CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONATOR_H_
