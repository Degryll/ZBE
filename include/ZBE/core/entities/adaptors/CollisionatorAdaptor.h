/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionatorAdaptor.h
 * @since 2016-11-22
 * @date 2016-11-23
 * @author Degryll
 * @brief Template that adapts an entity to a collisionator.
 */

#ifndef CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_
#define CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_

#include <memory>

#include "ZBE/core/entities/avatars/Collisionator.h"

namespace zbe {

/** \brief Template that adapts an entity to a collisionator.
 */
template <typename T, typename R>
class CollisionatorAdaptor {
  public:
    virtual std::shared_ptr<Collisionator<R> > getCollisionator(T* entity) = 0;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_
