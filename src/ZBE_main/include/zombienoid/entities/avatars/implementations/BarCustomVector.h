/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BarCustomVector.h
 * @since 2017-10-15
 * @date 2017-10-15
 * @author Batis Degryll Ludo
 * @brief Zombienoid bar bounce vector.
 */

#ifndef ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BARCUSTOMVETOR_H_
#define ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BARCUSTOMVETOR_H_

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/events/generators/util/CollisionData.h"

#include "zombienoid/entities/avatars/CustomVector.h"

namespace zombienoid {

/** @brief Zombienoid bar bounce vector.
 */
class BarCustomVector : virtual public CustomVector {
public:

  BarCustomVector (zbe::AABB2D square) : s(square) {}

  virtual ~BarCustomVector(){}

  zbe::Vector2D getNormal(zbe::CollisionData* cdata) {
      double half = (s.maximum.x - s.minimum.x)/2;
      double sqcenterX = s.minimum.x + (half);
      double collsionX = cdata->getPoint().x;
      zbe::Vector2D out({(collsionX -sqcenterX)/ half, -1.0});
      return out;
  }

  void setAABB(zbe::AABB2D square) {
      s = square;
  }

private:
  zbe::AABB2D s;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BARCUSTOMVETOR_H_
