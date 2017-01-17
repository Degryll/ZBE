/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableCollisionator.h
 * @since 2016-12-16
 * @date 2017-01-17
 * @author Degryll Ludo
 * @brief This define a collisionator avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_MOVABLECOLLISIONATOR_H_
#define ZBE_ENTITIES_AVATARS_MOVABLECOLLISIONATOR_H_

#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/entities/avatars/Movable.h"

namespace zbe {

/** \brief This define a collisionator avatar that can be moved.
 */
template <typename R, unsigned s>
class MovableCollisionator : public Movable<s> ,public CollisionatorCommon<Movable<s>, R> {
  public:
    MovableCollisionator(CollisionObject<R>* object, std::forward_list<Actuator<Movable, R> > * actuators) : CollisionatorCommon<Movable<s>, R>(this, object) {}

};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_MOVABLECOLLISIONATOR_H_
