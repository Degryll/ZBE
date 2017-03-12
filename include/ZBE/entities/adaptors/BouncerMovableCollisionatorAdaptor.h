/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableCollisionatorAdaptor.h
 * @since 2016-12-16
 * @date 2017-01-21
 * @author Degryll
 * @brief Template that adapts an entity to a bouncer movable collisionator.
 * If you inherit this class, please use BouncerMCAdaptor in your naming
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BOUNCERMOVABLECOLLISIONATORADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BOUNCERMOVABLECOLLISIONATORADAPTOR_H_

#include <memory>

#include "ZBE/entities/adaptors/MovableCollisionatorAdaptor.h"
#include "ZBE/entities/adaptors/BouncerCollisionatorAdaptor.h"
#include "ZBE/entities/avatars/BouncerMovableCollisionator.h"

namespace zbe {

/** \brief Template that adapts an entity to a bouncer movable collisionator.
 */
template <typename R, typename T, unsigned s>
class BouncerMovableCollisionatorAdaptor : virtual public BouncerCollisionatorAdaptor<R, T, s>, virtual public MovableCollisionatorAdaptor<R, T, s> {
  public:
    virtual ~BouncerMovableCollisionatorAdaptor(){};

    virtual std::shared_ptr< BouncerMovableCollisionator<R, s> > getBouncerMovableCollisionator(T* entity) = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BOUNCERMOVABLECOLLISIONATORADAPTOR_H_
