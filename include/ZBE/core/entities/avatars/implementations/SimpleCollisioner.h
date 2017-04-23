/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleCollisioner.h
 * @since 2017-01-28
 * @date 2017-01-28
 * @author Degryll Batis Ludo
 * @brief Simple implementation for a collisioner.
 */

#ifndef CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLECOLLISIONER_H_
#define CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLECOLLISIONER_H_

#include <memory>

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"

namespace zbe {

template <typename R>
class SimpleCollisioner : public zbe::CollisionerCommon<SimpleCollisioner<R>, R> {
public:
  SimpleCollisioner(std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList)
    : CollisionerCommon<SimpleCollisioner<R>, R>(this, collisionObject, reactObject, actuatorsList) {}
};

} // namespace zbe

#endif //CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLECOLLISIONER_H_
