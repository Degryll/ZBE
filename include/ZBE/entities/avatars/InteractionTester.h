/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InteractionTester.h
 * @since 2017-06-26
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Interface for an avatar capable of test if a collisionData meets a given condition.
 */

#ifndef ZBE_ENTITIES_AVATARS_INTERACTIONTESTER_H_
#define ZBE_ENTITIES_AVATARS_INTERACTIONTESTER_H_

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** @brief Interface for an avatar capable of test if a collisionData meets a given condition.
 */
class InteractionTester {
public:
  using Base = void; //!< inheritance info

  /** \brief Virtual destructor.
   */
  virtual ~InteractionTester(){}

  /** \brief Tells if interaction condition is fullfilled.
   * \return true if interaction condition is fullfilled.
   */
  virtual bool test(CollisionData *data) = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_INTERACTIONTESTER_H_
