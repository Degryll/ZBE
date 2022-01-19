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

// template<typename ...T>
// struct TypeContainer {using Type = T...};
// using ZBTraits = TypeContainer<CollisionData3D, Solid>::Type;

// zandbokz interaction types
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

using Actor = zbe::Actor<zbe::CollisionData3D, Solid>;
using Reactor = zbe::Reactor<zbe::CollisionData3D, Solid>;
using Shapes = zbe::Shapes<zbe::MovingSphere>;

using Iner = zbe::Interactioner<ActorType, ReactorType, Shapes...>;
using Inator = zbe::Interactionator<ActorType, ReactorType, Shapes...>;

using IEG = InteractionEventGenerator<ZandBokzPhysicsSelector, ZandBokzPhysicsOverloaded, zbe::CollisionData3D, ZandBokzActor, ZandBokzReactor, zbe::MovingSphere>;

// zandbokz interaction types builders
using ActorBldr = zbe::ActorBldr<CollisionData3D, Solid>;
using ReactorBldr = zbe::ReactorBldr<CollisionData3D, Solid>;
using ShapeBldr = zbe::ShapeBldr<zbe::MovingSphere>;

using InerBldr = InteractionerBldr<ActorType, ReactorType, Shapes...>;
using InatorBldr = InteractionatorBldr<ActorType, ReactorType, Shapes...>;

// zandbokz interaction types builders factories
using ActorBldrFtry = zbe::ActorBldrFtry<CollisionData3D, Solid>;
using ReactorBldrFtry = zbe::ActorBldrFtry<CollisionData3D, Solid>;
using ShapeBldrFtry = zbe::ShapeBldrFtry<zbe::MovingSphere>;

using InerBldrFtry = InteractionerBldrFtry<ActorType, ReactorType, Shapes...>;
using InatorBldrFtry = InteractionatorBldrFtry<ActorType, ReactorType, Shapes...>;

using ZandBokzIEGFtry = zbe::InteractionEventGeneratorFtry<ZandBokzPhysicsSelector, ZandBokzPhysicsOverloaded, zbe::CollisionData3D, ZandBokzActor, ZandBokzReactor, zbe::MovingSphere

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZINTERACTIONSYSTEM_H_
