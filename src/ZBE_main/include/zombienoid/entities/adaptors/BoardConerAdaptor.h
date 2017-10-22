/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BoardConerAdaptor.h
 * @since 2017-07-09
 * @date 2017-07-09
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BOARDCONERADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BOARDCONERADAPTOR_H_

#include "ZBE/entities/avatars/InteractionTester.h"

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/Element2D.h"

#include "zombienoid/entities/avatars/implementations/BoardInteractionTester.h"

namespace zombienoid {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BoardConerAdaptor : public zbe::Adaptor<zbe::Collisioner<R> > {
public:
  BoardConerAdaptor(const BoardConerAdaptor&) = delete;
  void operator=(const BoardConerAdaptor&) = delete;

  BoardConerAdaptor(std::weak_ptr<zbe::Element2D<R> > entity) : e(entity), s(nullptr), aeIT(){
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> > aeContainer = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >(ent);
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()}, {(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticLimiterAABB2D<R> > cObject(new zbe::StaticLimiterAABB2D<R>(aabb));
    aeIT = std::make_shared<zbe::AvatarEntityFixed<zbe::InteractionTester> >(new BoardInteractionTester(aabb));
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::InteractionTester> > waecIT = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::InteractionTester> >(aeIT);
    std::shared_ptr<zbe::ReactObject<R> > ro(new zbe::ReactObjectCommon<R, zbe::InteractionTester>(waecIT));

    s = new zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>(aeContainer, cObject, ro, ent->getActuatorsList());
  }

  ~BoardConerAdaptor() {delete s;}

  zbe::Collisioner<R>* getAvatar() {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()}, {(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticLimiterAABB2D<R> > cObject(new zbe::StaticLimiterAABB2D<R>(aabb));

    s->setCollisionObject(cObject);
    return (s);
  }

private:
    std::weak_ptr<zbe::Element2D<R> > e;
    zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>* s;
    std::shared_ptr<zbe::AvatarEntity<zbe::InteractionTester> > aeIT;
};

}  // namespace zombienoid

#endif  // ZBE_ENTITIES_ADAPTORS_BOARDCONERADAPTOR_H_
