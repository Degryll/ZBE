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
using PhysicsOverloaded = zbe::overloaded<zbe::MovingSphereFunctor, zbe::MovingSphereMovingTriangle3DFunctor, zbe::MovingTriangle3DMovingSphereFunctor, zbe::NotIntersectFunctor<zbe::Triangle<3>, zbe::Triangle<3>, 3>>;

class PhysicsSelector : public zbe::InteractionSelector<zbe::CollisionData3D, PhysicsOverloaded, zbe::MovingSphere, zbe::MovingTriangle3D> {
public:
  virtual ~PhysicsSelector() = default;
protected:
  virtual PhysicsOverloaded getOverloaded() {
    return PhysicsOverloaded {zbe::MovingSphereFunctor{}, zbe::MovingSphereMovingTriangle3DFunctor{}, zbe::MovingTriangle3DMovingSphereFunctor{}, zbe::NotIntersectFunctor<zbe::Triangle<3>, zbe::Triangle<3>, 3>{}};
  }
};

struct Solid {};

using Actor = zbe::Actor<zbe::CollisionData3D, Solid>;
using Reactor = zbe::Reactor<zbe::CollisionData3D, Solid>;
using Shapes = zbe::Shape<zbe::MovingSphere, zbe::MovingTriangle3D>;

using Iner = zbe::Interactioner<Actor, Reactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using Inator = zbe::Interactionator<Actor, Reactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InatorList = zbe::TicketedForwardList<Inator>;
using InerList = zbe::TicketedForwardList<Iner>;

using IEG = zbe::InteractionEventGenerator<PhysicsSelector, PhysicsOverloaded, zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

// zandbokz interaction types builders
using ActorBldr = zbe::ActorBldr<zbe::CollisionData3D, Solid>;
using ReactorBldr = zbe::ReactorBldr<zbe::CollisionData3D, Solid>;
//using ShapeBldr = zbe::ShapeBldr<zbe::MovingSphere, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InerBldr = zbe::InteractionerBldr<zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using InatorBldr = zbe::InteractionatorBldr<zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

// zandbokz interaction types builders factories
using ActorBldrFtry = zbe::ActorBldrFtry<zbe::CollisionData3D, Solid>;
using ReactorBldrFtry = zbe::ReactorBldrFtry<zbe::CollisionData3D, Solid>;
using ShapeMSphereBldrFtry = zbe::ShapeBldrFtry<zbe::MovingSphere, zbe::MovingSphere, zbe::MovingTriangle3D>;
using ShapeMTriangleBldrFtry = zbe::ShapeBldrFtry<zbe::MovingTriangle3D, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InatorBldrFtry = zbe::InteractionatorBldrFtry<zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using InerBldrFtry = zbe::InteractionerBldrFtry<zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

using IEGFtry = zbe::InteractionEventGeneratorFtry<PhysicsSelector, PhysicsOverloaded, zbe::CollisionData3D, Actor, Reactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

// TODO falta incluir las funcionaes en PhysicsSelector y PhysicsOverloaded. Los pongo los dos porque no recuerdo que hacía exactamente cada uno :D

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZINTERACTIONSYSTEM_H_
