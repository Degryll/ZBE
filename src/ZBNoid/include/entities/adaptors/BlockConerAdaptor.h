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

#include "ZBE/core/events/generators/util/ReactObject.h"

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/Element2D.h"

#include "ZBE/core/tools/math/objects.h"

#include "entities/avatars/Solid.h"
#include "entities/avatars/Breakable.h"
#include "entities/avatars/Boombizer.h"

namespace zombienoid {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BlockConerAdaptor : public zbe::Adaptor<zbe::Collisioner<R> > {
 public:
  BlockConerAdaptor(const BlockConerAdaptor&) = delete;
  void operator=(const BlockConerAdaptor&) = delete;

  BlockConerAdaptor(std::weak_ptr<zbe::Element2D<R> > entity, int64_t boomState)
    : e(entity), boomState(boomState), s(nullptr),
      aeSolid(new zbe::AvatarEntityFixed<Solid>(new Solid())),
      aeBreak(new zbe::AvatarEntityFixed<Breakable>(new Breakable())),
      aeBoomb(new zbe::AvatarEntityFixed<Boombizer>(new Boombizer())),
      roSB(nullptr), roSBB(nullptr) {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> > aeContainer = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >(ent);
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()}, {(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticSolidAABB2D<R> > cObject(new zbe::StaticSolidAABB2D<R>(aabb));

    std::shared_ptr<zbe::WeakAvatarEntityContainer<Solid, Breakable> > weakAECSB = std::make_shared<zbe::WeakAvatarEntityContainer<Solid, Breakable> >(aeSolid, aeBreak);
    std::shared_ptr<zbe::WeakAvatarEntityContainer<Solid, Breakable, Boombizer> > weakAECSBB = std::make_shared<zbe::WeakAvatarEntityContainer<Solid, Breakable, Boombizer> >(aeSolid, aeBreak, aeBoomb);

    roSB  = std::make_shared<zbe::ReactObjectCommon<R, Solid, Breakable> >(weakAECSB);
    roSBB = std::make_shared<zbe::ReactObjectCommon<R, Solid, Breakable, Boombizer> >(weakAECSBB);

    s = new zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>(aeContainer, cObject, getReactObject(ent), ent->getActuatorsList());
  }

  ~BlockConerAdaptor() {
    delete s;
  }

  zbe::Collisioner<R>* getAvatar() {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    double halfW = ent->getW() / 2.0;
    double halfH = ent->getH() / 2.0;
    zbe::AABB2D aabb({(double)ent->getX() - halfW, (double)ent->getY() - halfH}, {(double)ent->getX() + halfW, (double)ent->getY() + halfH});
    std::shared_ptr<zbe::StaticSolidAABB2D<R> > cObject(new zbe::StaticSolidAABB2D<R>(aabb));
    s->setReactObject(getReactObject(ent));
    s->setCollisionObject(cObject);
    return (s);
  }

 private:

  std::shared_ptr<zbe::ReactObject<R> > getReactObject(std::shared_ptr<zbe::State> state) {
    if(state->getState() == boomState) {
      return roSBB;
    }
    return roSB;
  }

  std::weak_ptr<zbe::Element2D<R> > e;
  int64_t boomState;
  zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>* s;
  std::shared_ptr<zbe::AvatarEntity<Solid> > aeSolid;
  std::shared_ptr<zbe::AvatarEntity<Breakable> > aeBreak;
  std::shared_ptr<zbe::AvatarEntity<Boombizer> > aeBoomb;
  std::shared_ptr<zbe::ReactObjectCommon<R, Solid, Breakable> > roSB;
  std::shared_ptr<zbe::ReactObjectCommon<R, Solid, Breakable, Boombizer> > roSBB;
};

}  // namespace zombienoid

#endif  // ZBE_MAIN_ZOMBIENOID_ENTITIES_ADAPTORS_BLOCKCONERADAPTOR_H_
