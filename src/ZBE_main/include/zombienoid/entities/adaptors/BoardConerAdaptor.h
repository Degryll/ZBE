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

  BoardConerAdaptor(Element2D<R>* entity): e(entity), s(nullptr) {}

  ~BoardConerAdaptor() {delete s;}

  Collisioner<R>* getAvatar() {

    delete s;

    AvatarEntityContainer<Avatar, Positionable<2>, Stated>* aeContainer (new AvatarEntityContainer<Avatar, Positionable<2>, Stated>(e, e, e));
    zbe::AABB2D aabb({e->getX(), e->getY()}, {e->getX()+e->getW(), e->getY()+e->getH()});
    std::shared_ptr<StaticLimiterAABB2D<R> > cObject(new zbe::StaticLimiterAABB2D<R>(aabb));
    std::shared_ptr<BoardInteractionTesterRO<R> > it(new zbe::BoardInteractionTesterRO<R>(aabb));//{e->getX(), e->getY()}, {e->getX()+e->getW(), e->getY()+e->getH()})

    s = new CollisionerCommon<R,Avatar, Positionable<2>, Stated>(aeContainer, cObject, it, e->getActuatorsList());

    return (s);
  }

private:
    Element2D<R>* e;
    Collisioner<R>* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BOARDCONERADAPTOR_H_
