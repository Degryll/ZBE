/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movable.h
 * @since 2016-12-16
 * @date 2017-01-17
 * @author Degryll Ludo
 * @brief This define a collisioner avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_MOVABLECOLLISIONER_H_
#define ZBE_ENTITIES_AVATARS_MOVABLECOLLISIONER_H_

#include <cstdint>

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/entities/avatars/Movable.h"

namespace zbe {

/** \brief This define a collisioner avatar that can be moved.
 */
template <typename R, unsigned s>
class MovableCollisioner : public Movable<s> ,public CollisionerCommon<Movable<s>, R> {
  public:
    MovableCollisioner(CollisionObject<R>* object, uint64_t actuatorsList) : CollisionerCommon<Movable<s>, R>(this, object, actuatorsList) {}
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_MOVABLECOLLISIONER_H_
