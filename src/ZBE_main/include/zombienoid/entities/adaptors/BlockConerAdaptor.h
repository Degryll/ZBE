/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BlockConerAdaptor.h
 * @since 2017-07-06
 * @date 2017-07-09
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_ENTITIES_ADAPTORS_BLOCKCONERADAPTOR_H_
#define ZBE_MAIN_ZOMBIENOID_ENTITIES_ADAPTORS_BLOCKCONERADAPTOR_H_

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

  BlockConerAdaptor(std::weak_ptr<zbe::Element2D<R> > entity): e(entity), s(nullptr) {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> > aeContainer = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >(ent);
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()},{(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticSolidAABB2D<R> > cObject(new zbe::StaticSolidAABB2D<R>(aabb));
    std::shared_ptr<zbe::VoidReactObject<R> > vro(new zbe::VoidReactObject<R>());

    s = new zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>(aeContainer, cObject, vro, ent->getActuatorsList());
  }

  ~BlockConerAdaptor() {delete s;}

  zbe::Collisioner<R>* getAvatar() {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()},{(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticSolidAABB2D<R> > cObject(new zbe::StaticSolidAABB2D<R>(aabb));

    s->setCollisionObject(cObject);
    return (s);
  }

private:
    std::weak_ptr<zbe::Element2D<R> > e;
    zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>* s;
};

}  // namespace zombienoid

#endif  // ZBE_MAIN_ZOMBIENOID_ENTITIES_ADAPTORS_BLOCKCONERADAPTOR_H_
