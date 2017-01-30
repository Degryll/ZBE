/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovableMobileAdaptor.h
 * @since 2016-12-16
 * @date 2017-01-21
 * @author Degryll Ludo
 * @brief Implementation that adapts a mobileAPO entity to a movableCator.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BASEMOVABLECATORMOBILEAPOADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BASEMOVABLECATORMOBILEAPOADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/adaptors/MovableCollisionatorAdaptor.h"
#include "ZBE/entities/avatars/implementations/BaseSphereMovableCator.h"
#include "ZBE/archetypes/implementations/SimpleWideMobileAPO.h"

namespace zbe {

/** \brief Implementation that adapts a mobileAPO entity to a movableCator.
 */
template <typename R, unsigned s>
class BaseSphereMCMAPOAdaptor : public MovableCollisionatorAdaptor<R, SimpleWideMobileAPO<s>, s> {
  public:
    std::shared_ptr<MovableCollisionator<R, s> > getMovableCollisionator(SimpleWideMobileAPO<s>* entity) {
        std::shared_ptr<MovableCollisionator<R, s> > p(new BaseSphereMovableCator<R, s>(entity));
        return (p);
    }

    std::shared_ptr<Movable<s> > getMovable(SimpleWideMobileAPO<s>* entity) {
        std::shared_ptr<Movable<s> > p(new BaseSphereMovableCator<R, s>(entity));
        return (p);
    }

    std::shared_ptr<Collisionator<R> > getCollisionator(SimpleWideMobileAPO<s>* entity) {
        std::shared_ptr<Collisionator<R> > p(new BaseSphereMovableCator<R, s>(entity));
        return (p);
    }
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BASEMOVABLECATORMOBILEAPOADAPTOR_H_
