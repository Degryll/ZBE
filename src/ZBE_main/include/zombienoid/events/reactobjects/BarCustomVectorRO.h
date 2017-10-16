/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BoardInteractionTesterRO.h
 * @since 2017-10-15
 * @date 2017-10-15
 * @author Batis Degryll Ludo
 * @brief Interface for a ReactObject capable create a custom collision normal.
 */

#ifndef EVENTS_REACTOBJECTS_BARCUSTOMVETORRO_H_
#define EVENTS_REACTOBJECTS_BARCUSTOMVETORRO_H_

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/events/generators/util/CollisionData.h"

#include "zombienoid/events/reactobjects/CustomVectorRO.h"

namespace zombienoid {

/** @brief Interface for a ReactObject capable create a custom collision normal.
 */
class BarCustomVectorRO : virtual public CustomVectorRO {
public:

  BarCustomVectorRO (zbe::AABB2D square) : s(square) {}

  virtual ~BarCustomVectorRO(){}

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

#endif  // EVENTS_REACTOBJECTS_BARCUSTOMVETORRO_H_
