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

// zandbokz 3d physics interaction system ------------------------------------
using Physics3DOverloaded = zbe::overloaded<zbe::MovingSphereFunctor, zbe::MovingSphereMovingTriangle3DFunctor, zbe::MovingTriangle3DMovingSphereFunctor, zbe::NotIntersectFunctor<zbe::Triangle<3>, zbe::Triangle<3>, 3>>;

class Physics3DSelector : public zbe::InteractionSelector<zbe::CollisionData3D, Physics3DOverloaded, zbe::MovingSphere, zbe::MovingTriangle3D> {
public:
  virtual ~Physics3DSelector() = default;
protected:
  virtual Physics3DOverloaded getOverloaded() {
    return Physics3DOverloaded {zbe::MovingSphereFunctor{}, zbe::MovingSphereMovingTriangle3DFunctor{}, zbe::MovingTriangle3DMovingSphereFunctor{}, zbe::NotIntersectFunctor<zbe::Triangle<3>, zbe::Triangle<3>, 3>{}};
  }
};

struct Solid {};

const int PLATFORMPARAMS = 3;
using Platform = std::array<std::shared_ptr<zbe::Value<zbe::Vector3D>>, PLATFORMPARAMS>;

using ZBActor = zbe::Actor<zbe::CollisionData3D, Solid, Platform>;
using ZBReactor = zbe::Reactor<zbe::CollisionData3D, Solid, Platform>;
using Shapes = zbe::Shape<zbe::MovingSphere, zbe::MovingTriangle3D>;

using Iner = zbe::Interactioner<ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using Inator = zbe::Interactionator<ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InatorList = zbe::TicketedForwardList<Inator>;
using InerList = zbe::TicketedForwardList<Iner>;

using IEG3D = zbe::InteractionEventGenerator<Physics3DSelector, Physics3DOverloaded, zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InerBldr = zbe::InteractionerBldr<zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using InatorBldr = zbe::InteractionatorBldr<zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

// zandbokz interaction types builders factories
using ActorBldrFtry = zbe::ActorBldrFtry<zbe::CollisionData3D, Solid, Platform>;
using ReactorBldrFtry = zbe::ReactorBldrFtry<zbe::CollisionData3D, Solid, Platform>;
using ShapeMSphereBldrFtry   = zbe::ShapeBldrFtry<zbe::MovingSphere,     zbe::MovingSphere, zbe::MovingTriangle3D>;
using ShapeMTriangleBldrFtry = zbe::ShapeBldrFtry<zbe::MovingTriangle3D, zbe::MovingSphere, zbe::MovingTriangle3D>;

using InatorBldrFtry = zbe::InteractionatorBldrFtry<zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;
using InerBldrFtry = zbe::InteractionerBldrFtry<zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

using IEG3DFtry = zbe::InteractionEventGeneratorFtry<Physics3DSelector, Physics3DOverloaded, zbe::CollisionData3D, ZBActor, ZBReactor, zbe::MovingSphere, zbe::MovingTriangle3D>;

// zandbokz 2d physics interaction system ------------------------------------
using Physics2DOverloaded = zbe::overloaded<zbe::NotIntersectFunctor<zbe::MovingPoint2D, zbe::MovingPoint2D, 2>, zbe::MovingPoint2DTriangle2DFunctor, zbe::NotIntersectFunctor<zbe::Triangle2D, zbe::MovingPoint2D, 2>, zbe::NotIntersectFunctor<zbe::Triangle2D, zbe::Triangle2D, 2>>;

class Physics2DSelector : public zbe::InteractionSelector<zbe::CollisionData2D, Physics2DOverloaded, zbe::MovingPoint2D, zbe::Triangle2D> {
public:
  virtual ~Physics2DSelector() = default;
protected:
  virtual Physics2DOverloaded getOverloaded() {
    return Physics2DOverloaded {zbe::NotIntersectFunctor<zbe::MovingPoint2D, zbe::MovingPoint2D, 2>{}, zbe::MovingPoint2DTriangle2DFunctor{}, zbe::NotIntersectFunctor<zbe::Triangle2D, zbe::MovingPoint2D, 2>{}, zbe::NotIntersectFunctor<zbe::Triangle2D, zbe::Triangle2D, 2>{}};
  }
};

using ZB2DActor = zbe::Actor<zbe::CollisionData2D, Solid>;
using ZB2DReactor = zbe::Reactor<zbe::CollisionData2D, Solid>;
using Shapes2D = zbe::Shape<zbe::MovingPoint2D, zbe::Triangle2D>;

using Iner2D = zbe::Interactioner<ZB2DActor, ZB2DReactor, zbe::MovingPoint2D, zbe::Triangle2D>;
using Inator2D = zbe::Interactionator<ZB2DActor, ZB2DReactor, zbe::MovingPoint2D, zbe::Triangle2D>;

using Inator2DList = zbe::TicketedForwardList<Inator2D>;
using Iner2DList = zbe::TicketedForwardList<Iner2D>;


using IEG2D = zbe::InteractionEventGenerator<Physics2DSelector, Physics2DOverloaded, zbe::CollisionData2D, ZBActor, ZBReactor, zbe::MovingPoint2D, zbe::Triangle2D>;

using Iner2DBldr = zbe::InteractionerBldr<zbe::CollisionData2D, ZB2DActor, ZB2DReactor, zbe::MovingPoint2D, zbe::Triangle2D>;
using Inator2DBldr = zbe::InteractionatorBldr<zbe::CollisionData2D, ZB2DActor, ZB2DReactor, zbe::MovingPoint2D, zbe::Triangle2D>;

// zandbokz interaction types builders factories
using Actor2DBldrFtry = zbe::ActorBldrFtry<zbe::CollisionData2D, Solid>;
using Reactor2DBldrFtry = zbe::ReactorBldrFtry<zbe::CollisionData2D, Solid>;
using ShapeMPoint2DBldrFtry   = zbe::ShapeBldrFtry<zbe::MovingPoint2D, zbe::MovingPoint2D, zbe::Triangle2D>;
using ShapeTriangle2DBldrFtry = zbe::ShapeBldrFtry<zbe::Triangle2D,    zbe::MovingPoint2D, zbe::Triangle2D>;

using Inator2DBldrFtry = zbe::InteractionatorBldrFtry<zbe::CollisionData2D, ZB2DActor, ZB2DReactor, zbe::MovingPoint2D, zbe::Triangle2D>;
using Iner2DBldrFtry   = zbe::InteractionerBldrFtry<  zbe::CollisionData2D, ZB2DActor, ZB2DReactor, zbe::MovingPoint2D, zbe::Triangle2D>;

using IEG2DFtry = zbe::InteractionEventGeneratorFtry<Physics2DSelector, Physics2DOverloaded, zbe::CollisionData2D, ZB2DActor, ZB2DReactor, zbe::MovingPoint2D, zbe::Triangle2D>;


// -----------

class PlatformTrait : public zbe::Funct<void, zbe::Reactor<zbe::CollisionData3D, Platform>*, zbe::CollisionData3D> {
public:
  PlatformTrait(Platform p) : p(p) {}

  void operator()(zbe::Reactor<zbe::CollisionData3D, Platform>* reactor, zbe::CollisionData3D data) {
    auto a = (*p[0]).get();
    auto b = (*p[1]).get();
    auto c = (*p[2]).get();
    reactor->react(data, p);
  }
private:
  Platform p;
};

class PlatformTraitBldr : public zbe::Funct<std::shared_ptr<zbe::Funct<void, zbe::Reactor<zbe::CollisionData3D, Platform>*, zbe::CollisionData3D>>, std::shared_ptr<zbe::Entity>> {
public:
  std::shared_ptr<zbe::Funct<void, zbe::Reactor<zbe::CollisionData3D, Platform>*, zbe::CollisionData3D>> operator()(std::shared_ptr<zbe::Entity> ent) {
    // TODO deshaz esta barbarie
    Platform* p = new Platform{};
    for(int i = 0; i<PLATFORMPARAMS; i++) {
      (*p)[i] = ent->getVector3D(idx[i]);
    }
    
    auto out = std::make_shared<PlatformTrait>(*p);
    delete p;
    return out;
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
