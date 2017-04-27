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
class VoidCollisionator : public zbe::CollisionatorCommon<VoidCollisionator<R>, R> {
public:
  VoidCollisionator(std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList)
    : CollisionerCommon<VoidCollisionator<R>, R>(this, collisionObject, reactObject, actuatorsList) {}
};

} // namespace zbe

#endif //CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_VOIDCOLLISIONATOR_H_
