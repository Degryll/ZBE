/**
 * Copyright 2022 Batis Degryll Ludo
 * @file ZandBokzReactions.h
 * @since 2022-12-06
 * @date 2022-12-06
 * @author Ludo Degryll Batis
 * @brief ZandBokz Behaviors
 */

 #ifndef ZANDBOKZ_ZANDBOKZBEHAVIORS_H_
 #define ZANDBOKZ_ZANDBOKZBEHAVIORS_H_

#include <cstdio>
#include <cstdint>
#include <memory>

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/tools.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zandbokz {


class CopyV3DIfNotZeroBhv : virtual public zbe::Behavior<zbe::Vector3D, zbe::Vector3D> {
  public:
  virtual ~CopyV3DIfNotZeroBhv() = default;
  void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D> > avatar) {
    auto va = avatar->get<1, zbe::Vector3D>();
    auto vb = avatar->get<2, zbe::Vector3D>();
    zbe::Vector3D a = va->get();
    zbe::Vector3D b = vb->get();
    if(!isZero(a)) {
      vb->set(a);
      b = vb->get();
    } 
  }
};

class Vec3DAccumBhv : virtual public zbe::Behavior<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > {
  public:
  virtual ~Vec3DAccumBhv() = default;
  void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > > avatar) {
    //printf("Accum\n");fflush(stdout);
    auto vDest = avatar->get<1, zbe::Vector3D>();
    auto vA    = avatar->get<2, zbe::Vector3D>();
    auto vB    = avatar->get<3, zbe::Vector3D>();

    zbe::Vector3D a = vA->get();
    zbe::Vector3D b = vB->get();
    zbe::Vector3D newvel = a + b;
    vDest->set(newvel);
  }
};

class CalculeOrientationBhv : virtual public zbe::Behavior<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > {
  public:
  virtual ~CalculeOrientationBhv() = default;

  void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > > avatar) {
    auto vDest = avatar->get<1, zbe::Vector3D>();
    auto vA    = avatar->get<2, zbe::Vector3D>();
    auto vB    = avatar->get<3, zbe::Vector3D>();

    zbe::Vector3D a = vA->get();
    zbe::Vector3D b = vB->get();
    zbe::Vector3D ori = a - b;
    ori.y = 0.0;
    ori.normalize();
    
    vDest->set(ori);
  }
};

class OrientationRelativeVelSetter : virtual public zbe::Behavior<double, double, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > {
  public:
  virtual ~OrientationRelativeVelSetter() = default;
  void apply(std::shared_ptr<zbe::MAvatar<double, double, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > > avatar) {
    auto vOrientation = avatar->get<1, zbe::Vector3D>();
    auto vUpwards     = avatar->get<2, zbe::Vector3D>();
    auto vVelocity    = avatar->get<3, zbe::Vector3D>();
    auto vForward    = avatar->get<4, double>();
    auto vLateral    = avatar->get<5, double>();

    zbe::Vector3D ori = vOrientation->get().normalize();
    zbe::Vector3D upw = vUpwards->get();
    zbe::Vector3D norm = cross(ori, upw);
    double forw = vForward->get();
    double late = vLateral->get();
    
    zbe::Vector3D newvel = (ori * forw) + (norm *late);
    vVelocity->set(newvel);
  }
};

class GravityMotion3D : virtual public zbe::Behavior<zbe::Vector3D, zbe::Vector3D > {
  public:
    virtual ~GravityMotion3D() = default;

    void setGravity(zbe::Vector3D g) {
      this->g = g;
    }

    void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D > > avatar) {
        auto vpos = avatar->get<1, zbe::Vector3D>();
        auto vvel = avatar->get<2, zbe::Vector3D>();

        zbe::Vector3D pos = vpos->get();
        zbe::Vector3D vel = vvel->get();
        auto contextTime = avatar->getContextTime();

        double t = contextTime->getCurrentTime() * zbe::INVERSE_SECOND;
        zbe::Vector3D newvel = vel + (g * t);
        zbe::Vector3D newpos = pos + vel*t + (g/2)*(t * t);

        if(newpos.y<=0.0) {
            newpos.y = 0.0;
            newvel.y = 0.0;
        }
        vpos->set(newpos);
        vvel->set(newvel);
    }

  private:
    zbe::Vector3D g;
};

class GravityMotion3DFtry : virtual public zbe::Factory {
public:

  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<GravityMotion3D> gm3d = std::shared_ptr<GravityMotion3D>(new GravityMotion3D);
    behaviorRsrc.insert("Behavior."s + name, gm3d);
    gm3dRsrc.insert("GravityMotion3D."s + name, gm3d);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
        auto j = *cfg;
        auto g = zbe::JSONFactory::loadParamCfgDict<zbe::Vector3D>(vecStore, j, "gravity"s, "GravityMotion3DFtry"s);
        if(!g) {
            return;
        }

        auto gm3d = gm3dRsrc.get("GravityMotion3D."s + name);
        gm3d->setGravity(*g);
    } else {
        zbe::SysError::setError("GravityMotion3DFtry config for "s + name + " not found."s);
    }
  }

private:

  zbe::RsrcStore<nlohmann::json>& configRsrc = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcDictionary<zbe::Vector3D>& vecStore = zbe::RsrcDictionary<zbe::Vector3D>::getInstance();
  zbe::RsrcStore<zbe::Value<zbe::Vector3D> > &vv3Rsrc = zbe::RsrcStore<zbe::Value<zbe::Vector3D> >::getInstance();
  zbe::RsrcStore<zbe::Behavior<zbe::Vector3D, zbe::Vector3D> >& behaviorRsrc = zbe::RsrcStore<zbe::Behavior<zbe::Vector3D, zbe::Vector3D> >::getInstance();
  zbe::RsrcStore<GravityMotion3D>& gm3dRsrc = zbe::RsrcStore<GravityMotion3D>::getInstance();
};

class FollowTargetBvr : virtual public zbe::Behavior<zbe::Vector3D, zbe::Vector3D > {
  public:
    virtual ~FollowTargetBvr() = default;

    void setGravity(zbe::Vector3D g) {
      this->g = g;
    }

    void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D > > avatar) {
        auto vpos = avatar->get<1, zbe::Vector3D>();
        auto vvel = avatar->get<2, zbe::Vector3D>();

        zbe::Vector3D pos = vpos->get();
        zbe::Vector3D vel = vvel->get();
        auto contextTime = avatar->getContextTime();

        double t = contextTime->getCurrentTime() * zbe::INVERSE_SECOND;
        zbe::Vector3D newvel = vel + (g * t);
        zbe::Vector3D newpos = pos + vel*t + (g/2)*(t * t);

        if(newpos.y<=0.0) {
            newpos.y = 0.0;
            newvel.y = 0.0;
        }
        vpos->set(newpos);
        vvel->set(newvel);
    }

  private:
    zbe::Vector3D g;
};

class FollowTargetBvrFtry : virtual public zbe::Factory {
public:

  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<GravityMotion3D> gm3d = std::shared_ptr<GravityMotion3D>(new GravityMotion3D);
    behaviorRsrc.insert("Behavior."s + name, gm3d);
    gm3dRsrc.insert("GravityMotion3D."s + name, gm3d);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
        auto j = *cfg;
        auto g = zbe::JSONFactory::loadParamCfgDict<zbe::Vector3D>(vecStore, j, "gravity"s, "GravityMotion3DFtry"s);
        if(!g) {
            return;
        }

        auto gm3d = gm3dRsrc.get("GravityMotion3D."s + name);
        gm3d->setGravity(*g);
    } else {
        zbe::SysError::setError("GravityMotion3DFtry config for "s + name + " not found."s);
    }
  }

private:

  zbe::RsrcStore<nlohmann::json>& configRsrc = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcDictionary<zbe::Vector3D>& vecStore = zbe::RsrcDictionary<zbe::Vector3D>::getInstance();
  zbe::RsrcStore<zbe::Value<zbe::Vector3D> > &vv3Rsrc = zbe::RsrcStore<zbe::Value<zbe::Vector3D> >::getInstance();
  zbe::RsrcStore<zbe::Behavior<zbe::Vector3D, zbe::Vector3D> >& behaviorRsrc = zbe::RsrcStore<zbe::Behavior<zbe::Vector3D, zbe::Vector3D> >::getInstance();
  zbe::RsrcStore<GravityMotion3D>& gm3dRsrc = zbe::RsrcStore<GravityMotion3D>::getInstance();
};

} // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZBEHAVIORS_H_
