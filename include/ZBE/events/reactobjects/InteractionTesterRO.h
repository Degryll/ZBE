/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InteractionTesterRO.h
 * @since 2017-06-26
 * @date 2017-06-26
 * @author Batis Degryll Ludo
 * @brief Interface for a ReactObject capable of test if a collisionData meets a given condition.
 */

#ifndef EVENTS_REACTOBJECTS_INTERACTIONTESTERRO_H_
#define EVENTS_REACTOBJECTS_INTERACTIONTESTERRO_H_

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

namespace zbe {

/** @brief Interface for a ReactObject capable of test if a collisionData meets a given condition.
 */
template<typename R>
class InteractionTesterRO : public ReactObjectCommon<R, InteractionTesterRO<R> > {
public:
  InteractionTesterRO(InteractionTesterRO* itRO)
    : ReactObjectCommon<R, InteractionTesterRO<R> >(itRO) {}

  virtual bool test(CollisionData *data) = 0;
};

}  // namespace zbe

#endif  // EVENTS_REACTOBJECTS_INTERACTIONTESTERRO_H_
