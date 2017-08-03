/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BlockConerAdaptor.h
 * @since 2017-07-06
 * @date 2017-07-09
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BLOCKCONERADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BLOCKCONERADAPTOR_H_

#include "ZBE/core/entities/avatars/implementations/VoidCollisioner.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/Element2D.h"

#include "ZBE/core/tools/math/objects.h"

namespace zombienoid {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BlockConerAdaptor : public zbe::Adaptor<zbe::Collisioner<R> > {
public:
  BlockConerAdaptor(const BlockConerAdaptor&) = delete;
  void operator=(const BlockConerAdaptor&) = delete;

  BlockConerAdaptor(zbe::Element2D<R>* entity): e(entity), s(nullptr) {}

  ~BlockConerAdaptor() {delete s;}

  zbe::Collisioner<R>* getAvatar() {

    delete s;

    zbe::AvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated>* aeContainer (new zbe::AvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated>(e, e, e));
    zbe::AABB2D aabb({e->getX(), e->getY()},{e->getX()+e->getW(), e->getY()+e->getH()});
    std::shared_ptr<zbe::StaticSolidAABB2D<R> > cObject(new zbe::StaticSolidAABB2D<R>(aabb));
    std::shared_ptr<zbe::VoidReactObject<R> > vro(new zbe::VoidReactObject<R>());

    s = new zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>(aeContainer, cObject, vro, e->getActuatorsList());
    return (s);
  }

private:
    zbe::Element2D<R>* e;
    zbe::Collisioner<R>* s;
};

}  // namespace zombienoid

#endif  // ZBE_ENTITIES_ADAPTORS_BLOCKCONERADAPTOR_H_
