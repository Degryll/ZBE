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
using PhysicsOverloaded = zbe::overloaded<zbe::MovingSphereFunctor>;

class PhysicsSelector : public zbe::InteractionSelector<zbe::CollisionData3D, PhysicsOverloaded, zbe::MovingSphere> {
public:
  virtual ~PhysicsSelector() = default;
protected:
  virtual PhysicsOverloaded getOverloaded() {
    return PhysicsOverloaded {zbe::MovingSphereFunctor{}};
  }
};

struct Solid {};

using Actor = zbe::Actor<zbe::CollisionData3D, Solid>;
using Reactor = zbe::Reactor<zbe::CollisionData3D, Solid>;
using Shapes = zbe::Shape<zbe::MovingSphere>;

using Iner = zbe::Interactioner<Actor, Reactor, zbe::MovingSphere>;
using Inator = zbe::Interactionator<Actor, Reactor, zbe::MovingSphere>;

using InatorList = zbe::TicketedForwardList<Inator>;
using InerList = zbe::TicketedForwardList<Iner>;

using IEG = zbe::InteractionEventGenerator<PhysicsSelector, PhysicsOverloaded, zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere>;

// zandbokz interaction types builders
using ActorBldr = zbe::ActorBldr<zbe::CollisionData3D, Solid>;
using ReactorBldr = zbe::ReactorBldr<zbe::CollisionData3D, Solid>;
using ShapeBldr = zbe::ShapeBldr<zbe::MovingSphere, zbe::MovingSphere>;

using InerBldr = zbe::InteractionerBldr<zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere>;
using InatorBldr = zbe::InteractionatorBldr<zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere>;

// zandbokz interaction types builders factories
using ActorBldrFtry = zbe::ActorBldrFtry<zbe::CollisionData3D, Solid>;
using ReactorBldrFtry = zbe::ActorBldrFtry<zbe::CollisionData3D, Solid>;
using ShapeBldrFtry = zbe::ShapeBldrFtry<zbe::MovingSphere, zbe::MovingSphere>;

using InatorBldrFtry = zbe::InteractionatorBldrFtry<zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere>;
using InerBldrFtry = zbe::InteractionerBldrFtry<zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere>;

using IEGFtry = zbe::InteractionEventGeneratorFtry<PhysicsSelector, PhysicsOverloaded, zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere>;

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZINTERACTIONSYSTEM_H_
