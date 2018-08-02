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

#include "entities/avatars/Magnet.h"
#include "entities/avatars/CustomVector.h"
#include "entities/avatars/implementations/BarCustomVector.h"
#include "entities/avatars/implementations/BasePositionMagnet.h"

namespace zombienoid {

/** \brief Implementation that adapts a Drawable to a AnimatedSprite.
 */
template <typename R>
class BarConerAdaptor : public zbe::Adaptor<zbe::Interactioner<R> > {
 public:
  BarConerAdaptor(const BarConerAdaptor&) = delete;
  void operator=(const BarConerAdaptor&) = delete;

  BarConerAdaptor(std::weak_ptr<zbe::Element2D<R> > entity)
    : e(entity),
      s(nullptr),
      customVector(new BarCustomVector(zbe::AABB<2>())),
      aeCustoVector(new zbe::AvatarEntityFixed<CustomVector>(customVector)),
      aeMagnet(new zbe::AvatarEntityFixed<Magnet<2> >(new BasePositionMagnet<2>(&(*entity.lock())))),
      roBase(), roMagnet() {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> > aeContainer = std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Positionable<2>, zbe::Stated> >(ent);
    zbe::AABB2D aabb({(double)ent->getX(), (double)ent->getY()}, {(double)ent->getX()+ent->getW(), (double)ent->getY()+ent->getH()});
    std::shared_ptr<zbe::StaticSolidAABB2D > cObject(new zbe::StaticSolidAABB2D(aabb));

    std::shared_ptr<zbe::WeakAvatarEntityContainer<CustomVector> > weakAECCustomVector(new zbe::WeakAvatarEntityContainer<CustomVector>(aeCustoVector));
    roBase = std::make_shared<zbe::ReactObjectCommon<R, CustomVector> >(weakAECCustomVector);

    std::shared_ptr<zbe::WeakAvatarEntityContainer<CustomVector, Magnet<2> > > weakAECMagnet(new zbe::WeakAvatarEntityContainer<CustomVector, Magnet<2> >(aeCustoVector, aeMagnet));
    roMagnet = std::make_shared<zbe::ReactObjectCommon<R, CustomVector, Magnet<2> > >(weakAECMagnet);

    s = new zbe::InteractionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>(aeContainer, cObject, roBase, ent->getActuatorsList());
  }

  ~BarConerAdaptor() {
    delete s;
    delete customVector;
  }

  zbe::Interactioner<R>* getAvatar() {
    std::shared_ptr<zbe::Element2D<R> > ent = e.lock();
    double halfW = ent->getW() / 2.0;
    double halfH = ent->getH() / 2.0;
    zbe::AABB2D aabb({(double)ent->getX() - halfW, (double)ent->getY() - halfH}, {(double)ent->getX() + halfW, (double)ent->getY() + halfH});
    std::shared_ptr<zbe::StaticSolidAABB2D > cObject(new zbe::StaticSolidAABB2D(aabb));
    customVector->setAABB(aabb);
    s->setInteractionObject(cObject);
    s->setReactObject(getReactObject(ent));
    return (s);
  }

 private:

  std::shared_ptr<zbe::ReactObject<R> > getReactObject(std::shared_ptr<zbe::State> state) {
    if(state->getState() == 1) {
      return roMagnet;
    }
    return roBase;
  }

  std::weak_ptr<zbe::Element2D<R> > e;
  zbe::InteractionerCommon<R,zbe::Avatar, zbe::Positionable<2>, zbe::Stated>* s;
  BarCustomVector* customVector;
  std::shared_ptr<zbe::AvatarEntity<CustomVector> > aeCustoVector;
  std::shared_ptr<zbe::AvatarEntity<Magnet<2> > > aeMagnet;

  std::shared_ptr<zbe::ReactObjectCommon<R, CustomVector> > roBase;
  std::shared_ptr<zbe::ReactObjectCommon<R, CustomVector, Magnet<2> > > roMagnet;
};

}  // namespace zombienoid

#endif  // ZBE_MAIN_ZOMBIENOID_ENTITIES_ADAPTORS_BARCONERADAPTOR_H_
