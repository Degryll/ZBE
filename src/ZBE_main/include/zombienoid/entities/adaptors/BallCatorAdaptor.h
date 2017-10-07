/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BallCatorAdaptor.h
 * @since 2017-07-09
 * @date 2017-07-09
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BALLCATORADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BALLCATORADAPTOR_H_

#include "zombienoid/events/reactobjects/BoardInteractionTesterRO.h"

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/ActiveElement2D.h"

namespace zombienoid {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BallCatorAdaptor : public zbe::Adaptor<zbe::Collisionator<R> > {
public:
  BallCatorAdaptor(const BallCatorAdaptor&) = delete;
  void operator=(const BallCatorAdaptor&) = delete;

  BallCatorAdaptor(std::weak_ptr<zbe::ActiveElement2D<R> > entity): e(entity), s(nullptr) {
    std::shared_ptr<zbe::ActiveElement2D<R> > ent = e.lock();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated > > aeContainer = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated > >(ent);
    std::shared_ptr<zbe::ConstantMovingCircle<R> > cObject(new zbe::ConstantMovingCircle<R>(zbe::Circle(zbe::Point2D({(ent->getPosition().x), ent->getPosition().y}), ent->getWidth()/2.0), ent->getVelocity()));
    std::shared_ptr<zbe::VoidReactObject<R> > vro(new zbe::VoidReactObject<R>());

    s = new zbe::CollisionatorCommon<R,zbe::Avatar, zbe::Bouncer<2>, zbe::Stated >(aeContainer, cObject, vro, ent->getActuatorsList(), ent->getCollisionablesList());
  }

  ~BallCatorAdaptor() {delete s;}

  zbe::Collisionator<R>* getAvatar() {
    std::shared_ptr<zbe::ActiveElement2D<R> > ent = e.lock();
    std::shared_ptr<zbe::ConstantMovingCircle<R> > cObject(new zbe::ConstantMovingCircle<R>(zbe::Circle(zbe::Point2D({(ent->getPosition().x), ent->getPosition().y}), ent->getWidth()/2.0), ent->getVelocity()));

    s->setCollisionObject(cObject);
    return (s);
  }

private:
    std::weak_ptr<zbe::ActiveElement2D<R> > e;
    zbe::CollisionatorCommon<R,zbe::Avatar, zbe::Bouncer<2>, zbe::Stated >* s;
};

}  // namespace zombienoid

#endif  // ZBE_ENTITIES_ADAPTORS_BALLCATORADAPTOR_H_
