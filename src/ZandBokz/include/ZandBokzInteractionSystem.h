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

// zandbokz 3d fake gravity interaction system ------------------------------------
struct FGravityData {
  uint64_t time{};
  zbe::Point3D point{};
};

struct Attractor {};

zbe::Point3D calculateNormal(const zbe::Point3D& p1, const zbe::Point3D& p2, const zbe::Point3D& p3) {
    // Calcula el vector normal al plano
    zbe::Point3D v1 = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
    zbe::Point3D v2 = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};

    zbe::Point3D normal;
    normal.x = v1.y * v2.z - v1.z * v2.y;
    normal.y = v1.z * v2.x - v1.x * v2.z;
    normal.z = v1.x * v2.y - v1.y * v2.x;

    return normal;
}

zbe::Point3D projectPointOnPlane(const zbe::Point3D* point, const zbe::Triangle3D* triangle) {
    // Calcula el vector normal al plano
    auto normal = calculateNormal(triangle->a, triangle->b, triangle->c);

    // Calcula el numerador de la fórmula
    double numerator = normal.x * (point->x - triangle->a.x) + normal.y * (point->y - triangle->a.y) + normal.z * (point->z - triangle->a.z);

    // Calcula el denominador de la fórmula
    double denominator = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;

    // Calcula la proyección del punto sobre el plano
    zbe::Point3D projection;
    projection.x = point->x - (numerator / denominator) * normal.x;
    projection.y = point->y - (numerator / denominator) * normal.y;
    projection.z = point->z - (numerator / denominator) * normal.z;

    return projection;
}

bool gravityCenterMovingPointMovingTriangle(std::shared_ptr<zbe::MovingPoint3D> mpoint, std::shared_ptr<zbe::MovingTriangle3D> mtriangle, uint64_t time, FGravityData& gdata) {
  zbe::Point3D proyection = projectPointOnPlane(mpoint->getShape(), mtriangle->getShape());
  gdata.point = proyection;
  gdata.time = time;
  return true;
}

class GravityCenterMovingPointMovingTriangleFunctor {
public:
  bool operator()(std::shared_ptr<zbe::MovingPoint3D> arg1, std::shared_ptr<zbe::MovingTriangle3D> arg2, uint64_t time, FGravityData &data){
    return gravityCenterMovingPointMovingTriangle(arg1, arg2, time, data);
  }
};

template<typename a, typename b>
bool notGravity(std::shared_ptr<a>, std::shared_ptr<b>, uint64_t time, FGravityData &data) {
  data.time = time;
  return false;
}

template<typename a, typename b>
class NotFGravityFunctor {
public:
  bool operator()(std::shared_ptr<a> arg1, std::shared_ptr<b> arg2, uint64_t time, FGravityData &data){
    return notGravity<a, b>(arg1, arg2, time, data);
  }
};

using FGravity3DOverloaded = zbe::overloaded<NotFGravityFunctor<zbe::MovingPoint3D,zbe::MovingPoint3D>, GravityCenterMovingPointMovingTriangleFunctor, NotFGravityFunctor<zbe::MovingTriangle3D,zbe::MovingPoint3D>, NotFGravityFunctor<zbe::MovingTriangle3D, zbe::MovingTriangle3D>>;

class FGravity3DSelector : public zbe::InteractionSelector<FGravityData, FGravity3DOverloaded, zbe::MovingPoint3D, zbe::MovingTriangle3D> {
public:
  virtual ~FGravity3DSelector() = default;
protected:
  virtual FGravity3DOverloaded getOverloaded() {
    return FGravity3DOverloaded {NotFGravityFunctor<zbe::MovingPoint3D,zbe::MovingPoint3D>{}, GravityCenterMovingPointMovingTriangleFunctor{}, NotFGravityFunctor<zbe::MovingTriangle3D,zbe::MovingPoint3D>{}, NotFGravityFunctor<zbe::MovingTriangle3D, zbe::MovingTriangle3D>{}};
  }
};


using FGActor = zbe::Actor<FGravityData, Attractor>;
using FGReactor = zbe::Reactor<FGravityData, Attractor>;
using FGShapes = zbe::Shape<zbe::MovingPoint3D, zbe::MovingTriangle3D>;

using FGIner = zbe::Interactioner<FGActor, FGReactor, zbe::MovingPoint3D, zbe::MovingTriangle3D>;
using FGInator = zbe::Interactionator<FGActor, FGReactor, zbe::MovingPoint3D, zbe::MovingTriangle3D>;

using FGInatorList = zbe::TicketedForwardList<FGInator>;
using FGInerList = zbe::TicketedForwardList<FGIner>;

using IEGFG = zbe::InteractionEventGenerator<FGravity3DSelector, FGravity3DOverloaded, FGravityData, ZBActor, ZBReactor, zbe::MovingPoint3D, zbe::MovingTriangle3D>;

using FGInerBldr = zbe::InteractionerBldr<FGravityData, FGActor, FGReactor, zbe::MovingPoint3D, zbe::MovingTriangle3D>;
using FGInatorBldr = zbe::InteractionatorBldr<FGravityData, FGActor, FGReactor, zbe::MovingPoint3D, zbe::MovingTriangle3D>;

// zandbokz interaction types builders factories
using FGActorBldrFtry = zbe::ActorBldrFtry<FGravityData, Attractor>;
using FGReactorBldrFtry = zbe::ReactorBldrFtry<FGravityData, Attractor>;
using FGShapeMPointBldrFtry   = zbe::ShapeBldrFtry<zbe::MovingPoint3D,     zbe::MovingPoint3D, zbe::MovingTriangle3D>;
using FGShapeMTriangleBldrFtry = zbe::ShapeBldrFtry<zbe::MovingTriangle3D, zbe::MovingPoint3D, zbe::MovingTriangle3D>;

using FGInatorBldrFtry = zbe::InteractionatorBldrFtry<FGravityData, FGActor, FGReactor, zbe::MovingPoint3D, zbe::MovingTriangle3D>;
using FGInerBldrFtry = zbe::InteractionerBldrFtry<FGravityData, FGActor, FGReactor, zbe::MovingPoint3D, zbe::MovingTriangle3D>;

using IEGFGFtry = zbe::InteractionEventGeneratorFtry<FGravity3DSelector, FGravity3DOverloaded, FGravityData, FGActor, FGReactor, zbe::MovingPoint3D, zbe::MovingTriangle3D>;




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
  void create(std::string name, uint64_t) {
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
