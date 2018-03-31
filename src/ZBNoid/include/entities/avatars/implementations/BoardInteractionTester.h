/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BoardInteractionTester.h
 * @since 2017-06-26
 * @date 2017-10-21
 * @author Batis Degryll Ludo
 * @brief InteractionTester Implementation for zombienoid board. Check if collision has been on the floor.
 */

#ifndef ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BOARDINTERACTIONTESTER_H_
#define ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BOARDINTERACTIONTESTER_H_

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

#include "ZBE/entities/avatars/InteractionTester.h"

#include "ZBE/core/tools/math/objects.h"

namespace zombienoid {

/** @brief InteractionTester Implementation for zombienoid board. Check if collision has been on the floor.
 */
class BoardInteractionTester : public zbe::InteractionTester {
public:

  BoardInteractionTester(zbe::AABB2D square) : s(square) {}

  bool test(zbe::CollisionData *data) {
    return (s.maximum.y == data->getPoint().y);
  }

private:
  zbe::AABB2D s;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BOARDINTERACTIONTESTER_H_
