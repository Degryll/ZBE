/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseSphereMovableCator.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll Ludo Batis
 * @brief This implements a Collisionator base 1:1 avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESPHEREMOVABLECATOR_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESPHEREMOVABLECATOR_H_

#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"
#include "ZBE/entities/avatars/MovableCollisionator.h"
#include "ZBE/archetypes/WideMobileAPO.h"

namespace zbe {

/** \brief This implements a base 1:1 avatar that can be moved.
 */
template <typename R, unsigned s>
class BaseSphereMovableCator : public MovableCollisionator<R, s>, public BaseMovable<s>, public CollisionatorCommon<MovableCollisioner<R, s>, R> {
  public:

    BaseMovableCator(WideMobileAPO<R, s>* mobile)
      : BaseMovable<s>(mobile),
  			CollisionatorCommon<MovableCollisioner<R, s>, R>(
          this,
       		std::make_shared<zbe::ConstantMovingCircle<GameReactor> >(zbe::ConstantMovingCircle<GameReactor>(zbe::Circle({x, y}, radius), {vx, vy})),
          std::make_shared<VoidReactObject>(),
          mobile->getActuatorsList(),
          mobile->getCollisionablesList()) {}
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESPHEREMOVABLECATOR_H_
