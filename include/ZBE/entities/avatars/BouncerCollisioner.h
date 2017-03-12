/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncerCollisioner.h
 * @since 2017-03-12
 * @date 2017-03-12
 * @author Batis Degryll Ludo
 * @brief This define a collisioner avatar that can bounce.
 */

#ifndef ZBE_ENTITIES_AVATARS_BOUNCERCOLLISIONER_H_
#define ZBE_ENTITIES_AVATARS_BOUNCERCOLLISIONER_H_

#include <cstdint>

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/entities/avatars/Bouncer.h"

namespace zbe {

/** \brief This define a collisioner avatar that can bounce.
 */
template <typename R, unsigned s>
class BouncerCollisioner : virtual public Bouncer<s>, virtual public Collisioner<R> {
  public:
    virtual ~BouncerCollisioner() {}
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_BOUNCERCOLLISIONER_H_
