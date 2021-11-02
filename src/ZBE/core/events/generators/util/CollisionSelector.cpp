/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionSelector.cpp
 * @since 2016-05-01
 * @date 2018-08-07
 * @author Degryll Ludo
 * @brief Apply the correct function to solve a collision.
 */

#include "ZBE/core/events/generators/util/CollisionSelector.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"

namespace zbe {

bool CollisionSelector::select(std::shared_ptr<CollisionObject> param1, std::shared_ptr<CollisionObject> param2, int64_t& time, OldCollisionData *data) {
  return (param2->accept(this, *param1, time, data));
}

}  // namespace zbe
