/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CustomVector.h
 * @since 2017-10-15
 * @date 2017-10-15
 * @author Batis Degryll Ludo
 * @brief Interface capable of create a custom vector.
 */

#ifndef ZOMBIENOID_ENTITIES_AVATARS_CUSTOMVETOR_H_
#define ZOMBIENOID_ENTITIES_AVATARS_CUSTOMVETOR_H_

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/events/generators/util/CollisionData.h"


namespace zombienoid {

/** @brief Interface capable of create a custom vector.
 */
class CustomVector {
public:
  using Base = void;

  virtual ~CustomVector() {}
  virtual zbe::Vector2D getNormal(zbe::CollisionData*) = 0;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_ENTITIES_AVATARS_CUSTOMVETOR_H_
