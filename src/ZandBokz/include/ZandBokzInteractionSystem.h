/**
 * Copyright 2012 Batis Degryll Ludo
 * @file interactionSystem.h
 * @since 2016-08-15
 * @date 2018-03-20
 * @author Degryll Batis Ludo
 * @brief An event caused by input devices.
 */

#ifndef ZANDBOKZ_ZANDBOKZINTERACTIONSYSTEM_H_
#define ZANDBOKZ_ZANDBOKZINTERACTIONSYSTEM_H_

#include "ZBE/core/events/interactionSystem.h"
#include "ZBE/core/events/interactionFunctions.h"

namespace zandbokz {

using ZandBokzPhysicsOverloaded = zbe::overloaded<zbe::MovingSphereFunctor>;

class ZandBokzPhysicsSelector : public zbe::InteractionSelector<zbe::CollisionData3D, ZandBokzPhysicsOverloaded, zbe::MovingSphere> {
public:
  virtual ~ZandBokzPhysicsSelector() = default;
protected:
  virtual ZandBokzPhysicsOverloaded getOverloaded() {
    return ZandBokzPhysicsOverloaded {zbe::MovingSphereFunctor{}};
  }
};

struct Solid {};

using ZandBokzActor = zbe::Actor<zbe::CollisionData3D, Solid>;
using ZandBokzReactor = zbe::Reactor<zbe::CollisionData3D, Solid>;

using ZandBokzIEGFtry = zbe::InteractionEventGeneratorFtry<ZandBokzPhysicsSelector, ZandBokzPhysicsOverloaded, zbe::CollisionData3D, ZandBokzActor, ZandBokzReactor, zbe::MovingSphere>;

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZINTERACTIONSYSTEM_H_
