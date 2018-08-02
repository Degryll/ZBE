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

#include "entities/avatars/implementations/BoardInteractionTester.h"

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/ActiveElement2D.h"
#include "ZBE/entities/avatars/Resizable.h"

#include "entities/avatars/Solid.h"
#include "entities/avatars/Scorer.h"
#include "entities/avatars/implementations/SimpleScorer.h"

namespace zombienoid {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BallCatorAdaptor : public zbe::Adaptor<zbe::Interactionator<R> > {
public:
  BallCatorAdaptor(const BallCatorAdaptor&) = delete;
  void operator=(const BallCatorAdaptor&) = delete;

  BallCatorAdaptor(std::weak_ptr<zbe::ActiveElement2D<R> > entity, std::weak_ptr<zbe::AvatarEntity<zbe::Resizable> > resizeable)
    : e(entity), resizeable(resizeable), s(nullptr), aes(new zbe::AvatarEntityFixed<Solid>(new Solid())), aesc(new zbe::AvatarEntityFixed<Scorer>(new SimpleScorer())) {
    std::shared_ptr<zbe::ActiveElement2D<R> > ent = e.lock();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated, Scorer, zbe::Resizable> > aeContainer = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Bouncer<2>, zbe::Stated, Scorer, zbe::Resizable> >(ent,ent,ent,aesc, resizeable);
    std::shared_ptr<zbe::ConstantMovingCircle > cObject(new zbe::ConstantMovingCircle(zbe::Circle(zbe::Point2D({(ent->getPosition().x), ent->getPosition().y}), ent->getWidth()/2.0), ent->getVelocity()));

    std::shared_ptr<zbe::WeakAvatarEntityContainer<Solid> > weakAEC = std::make_shared<zbe::WeakAvatarEntityContainer<Solid> >(aes);
    std::shared_ptr<zbe::ReactObject<R> > ro(new zbe::ReactObjectCommon<R, Solid>(weakAEC));
    s = new zbe::InteractionatorCommon<R, zbe::Avatar, zbe::Bouncer<2>, zbe::Stated, Scorer, zbe::Resizable>(aeContainer, cObject, ro, ent->getActuatorsList(), ent->getCollisionablesList());
  }

  ~BallCatorAdaptor() {delete s;}

  zbe::Interactionator<R>* getAvatar() {
    std::shared_ptr<zbe::ActiveElement2D<R> > ent = e.lock();
    std::shared_ptr<zbe::ConstantMovingCircle > cObject(new zbe::ConstantMovingCircle(zbe::Circle(zbe::Point2D({(ent->getPosition().x), ent->getPosition().y}), ent->getWidth()/2.0), ent->getVelocity()));

    s->setInteractionObject(cObject);
    return (s);
  }

private:
    std::weak_ptr<zbe::ActiveElement2D<R> > e;
    std::weak_ptr<zbe::AvatarEntity<zbe::Resizable> > resizeable;
    zbe::InteractionatorCommon<R, zbe::Avatar, zbe::Bouncer<2>, zbe::Stated, Scorer, zbe::Resizable>* s;
    std::shared_ptr<zbe::AvatarEntity<Solid> > aes;
    std::shared_ptr<zbe::AvatarEntity<Scorer> > aesc;
};

}  // namespace zombienoid

#endif  // ZBE_ENTITIES_ADAPTORS_BALLCATORADAPTOR_H_
