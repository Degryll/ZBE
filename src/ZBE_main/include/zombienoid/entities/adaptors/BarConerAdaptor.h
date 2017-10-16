/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BarConerAdaptor.h
 * @since 2017-07-06
 * @date 2017-07-09
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_ENTITIES_ADAPTORS_BARCONERADAPTOR_H_
#define ZBE_MAIN_ZOMBIENOID_ENTITIES_ADAPTORS_BARCONERADAPTOR_H_

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/Element2D.h"

#include "ZBE/core/tools/math/objects.h"

#include "zombienoid/events/reactobjects/CustomVectorRO.h"
#include "zombienoid/events/reactobjects/BarCustomVectorRO.h"

namespace zombienoid {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BarConerAdaptor : public zbe::Adaptor<zbe::Collisioner<R> > {
public:
  BarConerAdaptor(const BarConerAdaptor&) = delete;
  void operator=(const BarConerAdaptor&) = delete;

  BarConerAdaptor(std::weak_ptr<zbe::Element2D<R> > entity): e(entity), s(nullptr), customVector(new BarCustomVectorRO(zbe::AABB<2>())) {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> > aeContainer = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >(ent);
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()},{(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticSolidAABB2D<R> > cObject(new zbe::StaticSolidAABB2D<R>(aabb));
    std::shared_ptr<zbe::ReactObjectCommon<R, CustomVectorRO> > ro(new zbe::ReactObjectCommon<R, CustomVectorRO>(customVector));

    s = new zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>(aeContainer, cObject, ro, ent->getActuatorsList());
  }

  ~BarConerAdaptor() {
      delete s;
      delete customVector;
   }

  zbe::Collisioner<R>* getAvatar() {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    double halfW = ent->getW() / 2.0;
    double halfH = ent->getH() / 2.0;
    zbe::AABB2D aabb({(double)ent->getX() - halfW, (double)ent->getY() - halfH},{(double)ent->getX() + halfW, (double)ent->getY() + halfH});
    std::shared_ptr<zbe::StaticSolidAABB2D<R> > cObject(new zbe::StaticSolidAABB2D<R>(aabb));
    customVector->setAABB(aabb);
    s->setCollisionObject(cObject);
    return (s);
  }

private:
    std::weak_ptr<zbe::Element2D<R> > e;
    zbe::CollisionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>* s;
    BarCustomVectorRO* customVector;
};

}  // namespace zombienoid

#endif  // ZBE_MAIN_ZOMBIENOID_ENTITIES_ADAPTORS_BARCONERADAPTOR_H_
