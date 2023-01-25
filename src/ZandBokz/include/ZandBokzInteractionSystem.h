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

// struct Platform {
//   std::shared_ptr<zbe::Value<zbe::Vector3D>> position;
//   std::shared_ptr<zbe::Value<zbe::Vector3D>> e1;
//   std::shared_ptr<zbe::Value<zbe::Vector3D>> e2;
// };

const int PLATFORMPARAMS = 3;
using Platform = std::array<std::shared_ptr<zbe::Value<zbe::Vector3D>>, PLATFORMPARAMS>;

using ZBActor = zbe::Actor<zbe::CollisionData3D, Solid, Platform>;
using ZBReactor = zbe::Reactor<zbe::CollisionData3D, Solid, Platform>;
using Shapes = zbe::Shape<zbe::MovingSphere, zbe::MovingTriangle3D>;

using Iner = zbe::Interactioner<ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using Inator = zbe::Interactionator<ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InatorList = zbe::TicketedForwardList<Inator>;
using InerList = zbe::TicketedForwardList<Iner>;

using IEG = zbe::InteractionEventGenerator<PhysicsSelector, PhysicsOverloaded, zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

// zandbokz interaction types builders
// using ActorBldr = zbe::ActorBldr<zbe::CollisionData3D, Solid>;
// using ReactorBldr = zbe::ReactorBldr<zbe::CollisionData3D, Solid>;
//using ShapeBldr = zbe::ShapeBldr<zbe::MovingSphere, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InerBldr = zbe::InteractionerBldr<zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using InatorBldr = zbe::InteractionatorBldr<zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

// zandbokz interaction types builders factories
using ActorBldrFtry = zbe::ActorBldrFtry<zbe::CollisionData3D, Solid, Platform>;
using ReactorBldrFtry = zbe::ReactorBldrFtry<zbe::CollisionData3D, Solid, Platform>;
using ShapeMSphereBldrFtry = zbe::ShapeBldrFtry<zbe::MovingSphere, zbe::MovingSphere, zbe::MovingTriangle3D>;
using ShapeMTriangleBldrFtry = zbe::ShapeBldrFtry<zbe::MovingTriangle3D, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InatorBldrFtry = zbe::InteractionatorBldrFtry<zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using InerBldrFtry = zbe::InteractionerBldrFtry<zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

using IEGFtry = zbe::InteractionEventGeneratorFtry<PhysicsSelector, PhysicsOverloaded, zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;


class PlatformTrait : public zbe::Funct<void, zbe::Reactor<zbe::CollisionData3D, Platform>*, zbe::CollisionData3D> {
public:
  PlatformTrait(Platform p) : p(p) {}

  void operator()(zbe::Reactor<zbe::CollisionData3D, Platform>* reactor, zbe::CollisionData3D data) {
    reactor->react(data, p);
  }
private:
  Platform p;
};

class PlatformTraitBldr : public zbe::Funct<std::shared_ptr<zbe::Funct<void, zbe::Reactor<zbe::CollisionData3D, Platform>*, zbe::CollisionData3D>>, std::shared_ptr<zbe::Entity>> {
public:
  std::shared_ptr<zbe::Funct<void, zbe::Reactor<zbe::CollisionData3D, Platform>*, zbe::CollisionData3D>> operator()(std::shared_ptr<zbe::Entity> ent) {
    Platform p;
    for(int i = 0; i<PLATFORMPARAMS; i++) {
      p[i] = ent->getVector3D(idx[i]);
    }
    return std::make_shared<PlatformTrait>(p);
  }
  void setIdxArr(std::array<uint64_t, 3> idx) {
    this->idx = idx;
  }
private:
  std::array<uint64_t, 3> idx;
};

class PlatformTraitBldrFtry : public zbe::Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<PlatformTraitBldr> ptb = std::make_shared<PlatformTraitBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, ptb);
    specificRsrc.insert("PlatformTraitBldr."s + name, ptb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto ptb = specificRsrc.get("PlatformTraitBldr."s + name);

      std::optional<std::array<uint64_t, PLATFORMPARAMS>> arr = zbe::JSONFactory::loadLiteralArray<uint64_t, PLATFORMPARAMS>(uintDict, j["attribIndexes"], "attribIndexes", "PlatformTraitBldrFtry");
      if(!arr) {
        return;
      }
      ptb->setIdxArr(*arr);

    } else {
      zbe::SysError::setError("PlatformTraitBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = zbe::Funct<std::shared_ptr<zbe::Funct<void, zbe::Reactor<zbe::CollisionData3D, Platform>*, zbe::CollisionData3D>>, std::shared_ptr<zbe::Entity>>;

  zbe::RsrcDictionary<uint64_t>& uintDict         = zbe::RsrcDictionary<uint64_t>::getInstance();
  zbe::RsrcStore<nlohmann::json> &configRsrc      = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcStore<PlatformTraitBldr>& specificRsrc = zbe::RsrcStore<PlatformTraitBldr>::getInstance();
  zbe::RsrcStore<FunctionType>& mainRsrc          = zbe::RsrcStore<FunctionType>::getInstance();
};

}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZINTERACTIONSYSTEM_H_
