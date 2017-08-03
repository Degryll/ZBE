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

namespace zbe {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BallCatorAdaptor : public Adaptor<Collisionator<R> > {
public:
  BallCatorAdaptor(const BallCatorAdaptor&) = delete;
  void operator=(const BallCatorAdaptor&) = delete;

  BallCatorAdaptor(ActiveElement2D<R>* entity): e(entity), s(nullptr) {}

  ~BallCatorAdaptor() {delete s;}

  Collisionator<R>* getAvatar() {

    delete s;

    AvatarEntityContainer<Avatar, Positionable<2>, Stated >* aeContainer (new AvatarEntityContainer<Avatar, Positionable<2>, Stated >(e, e, e));
    std::shared_ptr<StaticLimiterAABB2D<R> > cObject(new StaticLimiterAABB2D<R>(AABB2D({e->getX(), e->getY()}, {e->getX()+e->getW(), e->getY()+e->getH()})));
    std::shared_ptr<VoidReactObject<R> > vro(new VoidReactObject<R>());

    s = new CollisionatorCommon<R,Avatar, Positionable<2>, Stated >(aeContainer, cObject, vro, e->getActuatorsList(), e->getCollisionablesList());

    return (s);
  }

private:
    ActiveElement2D<R>* e;
    Collisionator<R>* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BALLCATORADAPTOR_H_
