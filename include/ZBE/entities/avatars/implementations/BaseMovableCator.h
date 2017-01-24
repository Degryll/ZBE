/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovableCollisionator.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll Ludo Batis
 * @brief This implements a Collisionator base 1:1 avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLECOLLISIONATOR_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLECOLLISIONATOR_H_

#include "ZBE/entities/avatars/implementations/BaseMovable.h"
#include "ZBE/entities/avatars/MovableCollisionator.h"
#include "ZBE/archetypes/MobileAPO.h"

namespace zbe {

/** \brief This implements a base 1:1 avatar that can be moved.
 */
template <typename R, unsigned s>
class BaseMovableCator : public MovableCollisionator<R, s>, public BaseMovable<s> {
  public:
    BaseMovableCator(const BaseMovableCator<R, s>&) = delete;
    void operator=(const BaseMovableCator<R, s>&) = delete;

    BaseMovableCator(MobileAPO<R, s>* mobile) : MovableCollisionator<R, s>(mobile->getCollisionObject(), mobile->getReactObject(),mobile->getActuatorsList(), mobile->getCollisionablesList()), BaseMovable<s>(mobile), m(mobile) {}

  private:
    MobileAPO<R, s>* m;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLECOLLISIONATOR_H_
