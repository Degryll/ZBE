/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncerCollisionatorEntity.h
 * @since 2017-03-12
 * @date 2017-03-12
 * @author Batis Degryll Ludo
 * @brief Entity that can be seen as a Bouncer collisionator.
 */

#ifndef ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERCOLLISIONATORENTITY_H_
#define ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERCOLLISIONATORENTITY_H_

#include <memory>

#include "ZBE/entities/adaptorentities/BouncerEntity.h"
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/avatars/BouncerCollisionator.h"
#include "ZBE/core/entities/adaptorentities/CollisionatorEntity.h"

namespace zbe {

/** \brief Entity that can be seen as a Bouncer collisionator.
 */
template <typename R, unsigned s>
class BouncerCollisionatorEntity : virtual public BouncerEntity<s> , virtual public CollisionatorEntity<R> {
  public:
    virtual ~BouncerCollisionatorEntity(){}

    virtual std::shared_ptr< BouncerCollisionator<R, s> > getBouncerCollisionator() = 0;

};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERCOLLISIONATORENTITY_H_
