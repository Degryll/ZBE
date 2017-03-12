/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseBouncerMCMAPOAdaptor.h
 * @since 2017-03-09
 * @date 2017-03-09
 * @author Batis Degryll Ludo
 * @brief Implementation that adapts a BouncingMobileAPO entity to a BouncerMovableCator.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BASEBOUNCERMOVABLECATORMOBILEAPOADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BASEBOUNCERMOVABLECATORMOBILEAPOADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/adaptors/BouncerMovableCollisionatorAdaptor.h"
#include "ZBE/entities/avatars/implementations/BaseBouncerMovableCator.h"
#include "ZBE/archetypes/BouncingMobileAPO.h"

namespace zbe {

/** \brief Implementation that adapts a mobileAPO entity to a movableCator.
 */
template <typename R, unsigned s>
class BaseBouncerMCMAPOAdaptor : public BouncerMovableCollisionatorAdaptor<R, BouncingMobileAPO<s>, s> {
  public:
  
    std::shared_ptr<BouncerMovableCollisionator<R, s> > getBouncerMovableCollisionator(BouncingMobileAPO<s>* entity) {
        std::shared_ptr<BouncerMovableCollisionator<R, s> > p(new BaseBouncerMovableCator<R, s>(entity));
        return (p);
    }

    std::shared_ptr<MovableCollisionator<R, s> > getMovableCollisionator(BouncingMobileAPO<s>* entity) {
        std::shared_ptr<MovableCollisionator<R, s> > p(new BaseBouncerMovableCator<R, s>(entity));
        return (p);
    }

    std::shared_ptr<Movable<s> > getMovable(BouncingMobileAPO<s>* entity) {
        std::shared_ptr<Movable<s> > p(new BaseBouncerMovableCator<R, s>(entity));
        return (p);
    }

    std::shared_ptr<Collisionator<R> > getCollisionator(BouncingMobileAPO<s>* entity) {
        std::shared_ptr<Collisionator<R> > p(new BaseBouncerMovableCator<R, s>(entity));
        return (p);
    }

    std::shared_ptr<Bouncer<s> > getBouncer(BouncingMobileAPO<s>* entity) {
        std::shared_ptr<Bouncer<s> > p(new BaseBouncerMovableCator<R, s>(entity));
        return (p);
    }
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BASEBOUNCERMOVABLECATORMOBILEAPOADAPTOR_H_
