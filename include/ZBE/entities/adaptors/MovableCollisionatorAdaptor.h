/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableCollisionatorAdaptor.h
 * @since 2016-12-16
 * @date 2017-01-21
 * @author Degryll
 * @brief Template that adapts an entity to a movable collisionator.
 * If you inherit this class, please use MovableCatorAdaptor in your naming
 */

#ifndef ZBE_ENTITIES_ADAPTORS_MOVABLECOLLISIONATORADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_MOVABLECOLLISIONATORADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/MovableCollisionator.h"
#include "ZBE/entities/adaptors/MovableAdaptor.h"
#include "ZBE/core/entities/adaptors/CollisionatorAdaptor.h"

namespace zbe {

/** \brief Template that adapts an entity to a movable collisionator.
 */
template <typename R, typename T, unsigned s>
class MovableCollisionatorAdaptor : virtual public MovableAdaptor<T, s>, virtual public CollisionatorAdaptor<T, R> {
  public:
    virtual ~MovableCollisionatorAdaptor(){};

    virtual std::shared_ptr< MovableCollisionator<R, s> > getMovableCollisionator(T* entity) = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_MOVABLECOLLISIONATORADAPTOR_H_
