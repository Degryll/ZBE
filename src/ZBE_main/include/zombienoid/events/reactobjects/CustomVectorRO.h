/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BoardInteractionTesterRO.h
 * @since 2017-10-15
 * @date 2017-10-15
 * @author Batis Degryll Ludo
 * @brief Interface for a ReactObject capable create a custom collision normal.
 */

#ifndef EVENTS_REACTOBJECTS_CUSTOMVETORRO_H_
#define EVENTS_REACTOBJECTS_CUSTOMVETORRO_H_

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/events/generators/util/CollisionData.h"


namespace zombienoid {

/** @brief Interface for a ReactObject capable create a custom collision normal.
 */
class CustomVectorRO {
public:
  virtual ~CustomVectorRO(){}

  virtual zbe::Vector2D getNormal(zbe::CollisionData*) = 0;
};

}  // namespace zombienoid

#endif  // EVENTS_REACTOBJECTS_CUSTOMVETORRO_H_
