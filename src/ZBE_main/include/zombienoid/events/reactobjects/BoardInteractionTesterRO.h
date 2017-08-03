/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BoardInteractionTesterRO.h
 * @since 2017-06-26
 * @date 2017-06-26
 * @author Batis Degryll Ludo
 * @brief Interface for a ReactObject capable of test if a collisionData meets a given condition.
 */

#ifndef EVENTS_REACTOBJECTS_BOARDINTERACTIONTESTERRO_H_
#define EVENTS_REACTOBJECTS_BOARDINTERACTIONTESTERRO_H_

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"
#include "ZBE/events/reactobjects/InteractionTesterRO.h"

#include "ZBE/core/tools/math/objects.h"

namespace zbe {

/** @brief Interface for a ReactObject capable of test if a collisionData meets a given condition.
 */
 template<typename R>
class BoardInteractionTesterRO : public InteractionTesterRO<R> {
public:

  BoardInteractionTesterRO(AABB2D square)
    : InteractionTesterRO<R>(this),
      square(square) {}

  bool test(CollisionData *data) {
    return (square.maximum.y == data->getPoint().y);
  }

private:
  AABB2D square;
};

}  // namespace zbe

#endif  // EVENTS_REACTOBJECTS_BOARDINTERACTIONTESTERRO_H_
