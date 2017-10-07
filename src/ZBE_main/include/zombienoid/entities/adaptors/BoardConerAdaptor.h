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

#include "zombienoid/events/reactobjects/BoardInteractionTesterRO.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/Element2D.h"

namespace zbe {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BoardConerAdaptor : public Adaptor<Collisioner<R> > {
public:
  BoardConerAdaptor(const BoardConerAdaptor&) = delete;
  void operator=(const BoardConerAdaptor&) = delete;

  BoardConerAdaptor(std::weak_ptr<Element2D<R> > entity): e(entity), s(nullptr) {
    std::shared_ptr<Element2D<R> > ent = e.lock();
    std::shared_ptr<WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> > aeContainer = std::make_shared<WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >(ent);
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()}, {(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<StaticLimiterAABB2D<R> > cObject(new zbe::StaticLimiterAABB2D<R>(aabb));
    std::shared_ptr<BoardInteractionTesterRO<R> > it(new zbe::BoardInteractionTesterRO<R>(aabb));//{ent->getX(), ent->getY()}, {ent->getX()+ent->getW(), ent->getY()+ent->getH()})

    s = new CollisionerCommon<R,Avatar, Positionable<2>, Stated>(aeContainer, cObject, it, ent->getActuatorsList());
  }

  ~BoardConerAdaptor() {delete s;}

  Collisioner<R>* getAvatar() {
    std::shared_ptr<Element2D<R> > ent = e.lock();
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()}, {(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<StaticLimiterAABB2D<R> > cObject(new zbe::StaticLimiterAABB2D<R>(aabb));

    s->setCollisionObject(cObject);
    return (s);
  }

private:
    std::weak_ptr<Element2D<R> > e;
    CollisionerCommon<R,Avatar, Positionable<2>, Stated>* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BOARDCONERADAPTOR_H_
