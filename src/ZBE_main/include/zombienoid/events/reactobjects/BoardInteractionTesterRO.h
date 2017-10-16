/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BoardInteractionTesterRO.h
 * @since 2017-06-26
 * @date 2017-06-26
 * @author Batis Degryll Ludo
 * @brief InteractionTesterRO Implementation for zombienoid board. Check if collision has been on the floor.
 */

#ifndef EVENTS_REACTOBJECTS_BOARDINTERACTIONTESTERRO_H_
#define EVENTS_REACTOBJECTS_BOARDINTERACTIONTESTERRO_H_

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"
#include "ZBE/events/reactobjects/InteractionTesterRO.h"

#include "ZBE/core/tools/math/objects.h"

namespace zombienoid {

/** @brief InteractionTesterRO Implementation for zombienoid board. Check if collision has been on the floor.
 */
 template<typename R>
class BoardInteractionTesterRO : public zbe::InteractionTesterRO<R> {
public:

  BoardInteractionTesterRO(zbe::AABB2D square)
    : zbe::InteractionTesterRO<R>(this),
      s(square) {}

  bool test(zbe::CollisionData *data) {
    return (s.maximum.y == data->getPoint().y);
  }

private:
  zbe::AABB2D s;
};

}  // namespace zombienoid

#endif  // EVENTS_REACTOBJECTS_BOARDINTERACTIONTESTERRO_H_
