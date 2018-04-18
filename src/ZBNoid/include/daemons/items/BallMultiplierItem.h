/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BallMultiplierItem.h
 * @since 2017-10-09
 * @date 2017-10-09
 * @author Ludo
 * @brief Daemon capable build balls
 */

#ifndef ZOMBIENOID_DAEMONS_ITEMS_BALLMULTIPLIERITEM
#define ZOMBIENOID_DAEMONS_ITEMS_BALLMULTIPLIERITEM

#include <memory>
#include <cstdint>

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"

namespace zombienoid {

/** \brief Daemon capable build balls
 */
template <typename BL>
class BallMultiplierItem : public zbe::Daemon {
public:

  BallMultiplierItem(const BallMultiplierItem&) = delete;
  void operator=(const BallMultiplierItem&) = delete;

  BallMultiplierItem(std::shared_ptr<zbe::Behavior<zbe::Movable<2> > > builder, uint64_t listId, const double* angles, unsigned amount)
    : builder(builder), ballList(zbe::RsrcStore<BL>::getInstance().get(listId)),
      archetype(new zbe::SimpleMobile<2>()), avatar(new zbe::BaseMovable<2>(archetype)),
      aem2(new zbe::AvatarEntityFixed<zbe::Movable<2> >(avatar)), model(new zbe::AvatarEntityContainer<zbe::Movable<2> >(aem2)),
      angles(angles), amount(amount) {
  }

  ~BallMultiplierItem(){
      delete archetype;
  }

  void run(){
    for(auto ball : (*ballList)) {
      zbe::Movable<2>* sample;
      assignAvatar((std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2> > >)ball,&sample);
      double degrees = sample->getVelocity().getDegrees();
      double radious = sample->getVelocity().getModule();
      zbe::Point2D p = sample->getPosition();
      for(unsigned i = 0; i< amount;i++){
        double a = angles[i];
        zbe::Vector2D vLocal;
        vLocal.setPolarsDegrees(radious, degrees + a);
        archetype->setPosition(p);
        archetype->setVelocity(vLocal);
        builder->apply(model);
      }
    }
  }

private:
  std::shared_ptr<zbe::Behavior<zbe::Movable<2> > > builder;
  std::shared_ptr<BL> ballList;
  zbe::SimpleMobile<2>* archetype;
  zbe::BaseMovable<2>* avatar;
  std::shared_ptr<zbe::AvatarEntity<zbe::Movable<2> > > aem2;
  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2> > > model;
  const double* angles;
  unsigned amount;
};

}  // namespace zombienoid

#endif // ZOMBIENOID_DAEMONS_ITEMS_BALLMULTIPLIERITEM
