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

#include "entities/avatars/implementations/BoardInteractionTester.h"
#include "entities/avatars/Wall.h"

namespace zombienoid {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BoardConerAdaptor : public zbe::Adaptor<zbe::Interactioner<R> > {
public:
  BoardConerAdaptor(const BoardConerAdaptor&) = delete;
  void operator=(const BoardConerAdaptor&) = delete;

  BoardConerAdaptor(std::weak_ptr<zbe::Element2D<R> > entity) : e(entity), s(nullptr), aeIT(), aew(new zbe::AvatarEntityFixed<Wall>(new Wall())){
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> > aeContainer = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >(ent);
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()}, {(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticLimiterAABB2D > cObject(new zbe::StaticLimiterAABB2D(aabb));
    aeIT = std::make_shared<zbe::AvatarEntityFixed<zbe::InteractionTester> >(new BoardInteractionTester(aabb));
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::InteractionTester, Wall> > waecIT = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::InteractionTester, Wall> >(aeIT, aew);
    std::shared_ptr<zbe::ReactObject<R> > ro(new zbe::ReactObjectCommon<R, zbe::InteractionTester, Wall>(waecIT));

    s = new zbe::InteractionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>(aeContainer, cObject, ro, ent->getActuatorsList());
  }

  ~BoardConerAdaptor() {delete s;}

  zbe::Interactioner<R>* getAvatar() {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()}, {(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticLimiterAABB2D > cObject(new zbe::StaticLimiterAABB2D(aabb));

    s->setInteractionObject(cObject);
    return (s);
  }

private:
    std::weak_ptr<zbe::Element2D<R> > e;
    zbe::InteractionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>* s;
    std::shared_ptr<zbe::AvatarEntity<zbe::InteractionTester> > aeIT;
    std::shared_ptr<zbe::AvatarEntity<Wall> > aew;
};

}  // namespace zombienoid

#endif  // ZBE_ENTITIES_ADAPTORS_BOARDCONERADAPTOR_H_
