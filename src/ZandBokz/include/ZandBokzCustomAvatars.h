/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ZandBokzCustomAvatars.h
 * @since 2022-03-24
 * @date 2022-03-24
 * @author Ludo Degryll Batis
 * @brief DZandBokz Custom avatars, builders & factories.
 */


#ifndef ZANDBOKZ_ZANDBOKZCUSTOMAVATARS_H_
#define ZANDBOKZ_ZANDBOKZCUSTOMAVATARS_H_

#include <string>
#include <memory>

#include "ZBE/factories/Factory.h"
#include "ZBE/factories/genericFactoryConstants.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/system.h"

#include "ZandBokzInteractionSystem.h"

namespace zandbokz {

class MovingSphereAvt : public zbe::SAvatar<zbe::MovingSphere>, zbe::AvatarImp  {
public:
  void setupEntity(std::shared_ptr<zbe::Entity> entity, uint64_t centeridx, uint64_t radiusidx, uint64_t velocityidx) {
    zbe::AvatarImp::setupEntity(entity);
    _Avatar<1, zbe::MovingSphere>::setup(&getMovingSphere, &setMovingSphere, (void*)this);
    center = entity->getVector3D(centeridx);
    radius = entity->getDouble(radiusidx);
    velocity = entity->getVector3D(velocityidx);
  }

  static void setMovingSphere(void *instance, zbe::MovingSphere msphere) {
    ((MovingSphereAvt*)instance)->velocity->set(msphere.v);
    ((MovingSphereAvt*)instance)->center->set(zbe::Vector3D{msphere.c.x, msphere.c.y, msphere.c.z});
    ((MovingSphereAvt*)instance)->radius->set(msphere.r);
  }

  static std::shared_ptr<zbe::Value<zbe::MovingSphere>> getMovingSphere(void *instance) {
    return std::make_shared<zbe::SimpleValue<zbe::MovingSphere>>(zbe::MovingSphere{
      zbe::Sphere{
          ((MovingSphereAvt*)instance)->center->get().toPoint(),
          ((MovingSphereAvt*)instance)->radius->get()
        }, ((MovingSphereAvt*)instance)->velocity->get()
    }
    );
  }

  std::shared_ptr<zbe::Entity> getEntity() {
    assert(false);
  }

private:
  std::shared_ptr<zbe::Value<zbe::Vector3D> > velocity{};
  std::shared_ptr<zbe::Value<zbe::Vector3D> > center{};
  std::shared_ptr<zbe::Value<double> > radius{};
};

// class MovingSphereDerivedVelAvt : public zbe::SAvatar<zbe::MovingSphere>, zbe::AvatarImp  {
// public:
//   void setupEntity(std::shared_ptr<zbe::Entity> entity, uint64_t centeridx, uint64_t radiusidx, ... TODO indices para calculo de velocidad ...) {
//     zbe::AvatarImp::setupEntity(entity);
//     _Avatar<1, zbe::MovingSphere>::setup(&getMovingSphere, &setMovingSphere, (void*)this);
//     center = entity->getVector3D(centeridx);
//     radius = entity->getDouble(radiusidx);
//     cTime = entity->getContextTime();
//     //velocity = entity->getVector3D(velocityidx);
//     TODO calculo de velocidad
//   }
//
//   static void setMovingSphere(void *instance, zbe::MovingSphere msphere) {
//     //((MovingSphereAvt*)instance)->velocity->set(msphere.v);
//     TODO calculo de velocidad
//     ((MovingSphereAvt*)instance)->center->set(zbe::Vector3D{msphere.c.x, msphere.c.y, msphere.c.z});
//     ((MovingSphereAvt*)instance)->radius->set(msphere.r);
//   }
//
//   static std::shared_ptr<Value<Vector3D> > getVelocity(void *instance) {
//     auto ns = (MovingSphereDerivedVelAvt*)instance;
//     auto& position = dcv->position;
//     auto p = position->get();
//     auto time = dcv->cTime->getTotalTime();
//     float div = (time / (float)dcv->period) * TAU;
//     float cosine = cos(div);
//     float newVal = ((cosine + 1.0) / 2.0) * (dcv->max - dcv->min) + dcv->min;
//     Vector3D v{0.0, 0.0, 0.0};
//     v[dcv->component] = newVal / time;
//     auto r = std::make_shared<SimpleValue<Vector3D> >();
//     r->set(v);
//     return r;
//   }
//
//   static std::shared_ptr<zbe::Value<zbe::MovingSphere>> getMovingSphere(void *instance) {
//     return std::make_shared<zbe::SimpleValue<zbe::MovingSphere>>(zbe::MovingSphere{
//       zbe::Sphere{
//           ((MovingSphereAvt*)instance)->center->get().toPoint(),
//           ((MovingSphereAvt*)instance)->radius->get()
//         }, TODO calculo de velocidad//((MovingSphereAvt*)instance)->velocity->get()
//     }
//     );
//   }
//
//   std::shared_ptr<zbe::Entity> getEntity() {
//     assert(false);
//   }
//
// private:
//   std::shared_ptr<zbe::Value<zbe::Vector3D> > center;
//   std::shared_ptr<zbe::Value<double> > radius;
//   std::shared_ptr<ContextTime> cTime;
// };

class MovingSphereAvtBldr : public zbe::Funct<std::shared_ptr<zbe::SAvatar<zbe::MovingSphere>>, std::shared_ptr<zbe::Entity>> {
public:
  std::shared_ptr<zbe::SAvatar<zbe::MovingSphere>> operator()(std::shared_ptr<zbe::Entity> ent) {
    std::shared_ptr<MovingSphereAvt> avt = std::make_shared<MovingSphereAvt>();
    avt->setupEntity(ent, centeridx, radiusidx, velocityidx);
    return avt;
  }

  void setIdxs(uint64_t centeridx, uint64_t radiusidx, uint64_t velocityidx) {
    this->centeridx = centeridx;
    this->radiusidx = radiusidx;
    this->velocityidx = velocityidx;
  }

private:
  uint64_t centeridx {};
  uint64_t radiusidx {};
  uint64_t velocityidx {};
};
// TODO esto se está declarando en DOS sitios. Aquí y en custom avatars.
// Se está usando esta copia y no la de customs avatars. Resulta que funciona...
// así que habrá que ver diferencias con la de custom avatars, porque MovingTriangle3DAvt
// Está basada en aquella y, no en esta, y no funciona.
class MovingSphereAvtBldrFtry : public zbe::Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<MovingSphereAvtBldr> msvb = std::make_shared<MovingSphereAvtBldr>();
    mainRsrc.insert("Function."s + name, msvb);
    specificRsrc.insert("MovingSphereAvtBldr."s + name, msvb);
  }

  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto msvb = specificRsrc.get("MovingSphereAvtBldr."s + name);

      auto centeridx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "centerIdx"s, "MovingSphereAvtBldrFtry"s);
      if(!centeridx) {
        return;
      }

      auto radiusidx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "radiusidx"s, "MovingSphereAvtBldrFtry"s);
      if(!radiusidx) {
        return;
      }

      auto velocityidx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocityidx"s, "MovingSphereAvtBldrFtry"s);
      if(!velocityidx) {
        return;
      }

      msvb->setIdxs(*centeridx, *radiusidx, *velocityidx);

    } else {
      zbe::SysError::setError("MovingSphereAvtBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = zbe::Funct<std::shared_ptr<zbe::SAvatar<zbe::MovingSphere>>, std::shared_ptr<zbe::Entity>>;
  using ListType = zbe::TicketedForwardList<MovingSphereAvt>;
  zbe::NameRsrcDictionary &uintDict = zbe::NameRsrcDictionary::getInstance();
  zbe::RsrcStore<nlohmann::json> &configRsrc = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcStore<MovingSphereAvtBldr>& specificRsrc = zbe::RsrcStore<MovingSphereAvtBldr>::getInstance();
  zbe::RsrcStore<FunctionType>& mainRsrc = zbe::RsrcStore<FunctionType>::getInstance();
  zbe::RsrcStore<ListType>& listRsrc = zbe::RsrcStore<ListType>::getInstance();
};


}  // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZCUSTOMAVATARS_H_
