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
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zandbokz {


class KeepDistanceBhv : virtual public zbe::Behavior<double, zbe::Vector3D, zbe::Vector3D> {
  public:
  virtual ~KeepDistanceBhv() = default;
  void apply(std::shared_ptr<zbe::MAvatar<double, zbe::Vector3D, zbe::Vector3D> > avatar) {
    auto vtarget = avatar->get<1, zbe::Vector3D>();
    auto vposition = avatar->get<2, zbe::Vector3D>();
    auto vdistance = avatar->get<3, double>();

    zbe::Vector3D target = vtarget->get();
    zbe::Vector3D position = vposition->get();
    double distance = vdistance->get();

    zbe::Vector3D diff =  position - target;
    diff.setModule(distance);

    vposition->set(target + diff);
  }
};

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

class ProjectV3DOnPlaneBhv : virtual public zbe::Behavior<zbe::Vector2D, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D> {
  public:
  virtual ~ProjectV3DOnPlaneBhv() = default;
  void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector2D, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D> > avatar) {
    auto vE1 = avatar->get<1, zbe::Vector3D>();
    auto vE2    = avatar->get<2, zbe::Vector3D>();
    auto vSrc    = avatar->get<3, zbe::Vector3D>();

    zbe::Vector3D planeE1 = vE1->get();
    zbe::Vector3D planeE2 = vE2->get();
    zbe::Vector3D src = vSrc->get();

    zbe::Vector3D ax{1.0, 0.0, 0.0};
    zbe::Vector3D ay{0.0, 1.0, 0.0};
    zbe::Vector3D az{0.0, 0.0, 1.0};

    zbe::Vector3D bx = planeE1;
    zbe::Vector3D by = planeE2;
    zbe::Vector3D bz = zbe::cross(planeE1, planeE2).normalize();

    double x = src * zbe::Vector3D{bx.x, bx.y, bx.z};
    double y = src * zbe::Vector3D{by.x, by.y, by.z};
    double z = src * zbe::Vector3D{bz.x, bz.y, bz.z};

    zbe::Vector3D coordChange{x,y,z};

    zbe::Vector2D newOri2D{coordChange.x, coordChange.y};
    avatar->set<4, zbe::Vector2D>(newOri2D);
  }
};

class Vec3DAccumBhv : virtual public zbe::Behavior<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > {
  public:
  virtual ~Vec3DAccumBhv() = default;
  void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > > avatar) {
    
    auto vDest = avatar->get<1, zbe::Vector3D>();
    auto vA    = avatar->get<2, zbe::Vector3D>();
    auto vB    = avatar->get<3, zbe::Vector3D>();
    auto vC    = avatar->get<4, zbe::Vector3D>();

    zbe::Vector3D a = vA->get();
    zbe::Vector3D b = vB->get();
    zbe::Vector3D c = vC->get();
    zbe::Vector3D newvel = a + b + c;
    vDest->set(newvel);
  }
};

class CalculeOrientationBhv : virtual public zbe::Behavior<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D ,zbe::Vector3D> {
  public:
  virtual ~CalculeOrientationBhv() = default;

  void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D, zbe::Vector3D, zbe::Vector3D > > avatar) {
    // TODO esto no orienta como debe
    auto vDest  = avatar->get<1, zbe::Vector3D>();
    auto vA     = avatar->get<2, zbe::Vector3D>();
    auto vB     = avatar->get<3, zbe::Vector3D>();
    auto vNormal = avatar->get<4, zbe::Vector3D>();

    zbe::Vector3D a      = vA->get();
    zbe::Vector3D b      = vB->get();
    zbe::Vector3D normal = vNormal->get();
    zbe::Vector3D ori = a - b;
    
    //zbe::Vector3D normal = up;
    zbe::Vector3D proyection = ((ori * normal) / (normal * normal)) * normal;
    zbe::Vector3D orientPrima = ori - proyection;
    //ori.y = 0.0;
    //ori.normalize();

    orientPrima.normalize();
    vDest->set(orientPrima);
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

class OrientationRelative2DVelSetter : virtual public zbe::Behavior<double, double, zbe::Vector2D, zbe::Vector2D > {
  public:
  virtual ~OrientationRelative2DVelSetter() = default;
  void apply(std::shared_ptr<zbe::MAvatar<double, double, zbe::Vector2D, zbe::Vector2D > > avatar) {
    auto vOrientation = avatar->get<1, zbe::Vector2D>();
    auto vVelocity    = avatar->get<2, zbe::Vector2D>();
    auto vForward     = avatar->get<3, double>();
    auto vLateral     = avatar->get<4, double>();

    auto oldVel = vVelocity->get();

    zbe::Vector2D ori  = vOrientation->get().normalize();
    zbe::Vector2D norm{ori.y, -ori.x};
    double forw = vForward->get();
    double late = vLateral->get();
    zbe::Vector2D newvelF = (ori * forw);
    zbe::Vector2D newvelL = (norm *late);
    zbe::Vector2D newvel = newvelF + newvelL;
    
    zbe::Vector2D newVel2 = ori;
    newVel2.setModule(newvel.getModule());
    vVelocity->set(newVel2);

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

  void create(std::string name, uint64_t) {
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

  void create(std::string name, uint64_t) {
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


class NonRealGravityVelSetterBhv : virtual public zbe::Behavior<zbe::Vector3D, zbe::Vector3D> {
  public:
    using ListType = zbe::TicketedForwardList<zbe::SAvatar<zbe::Vector3D>>;
    virtual ~NonRealGravityVelSetterBhv() = default;

    void setRadius(double radius) {
      this->radius = radius;
    }

    void setRatio(double ratio) {
      this->ratio = ratio;
    }

    void setAttractorList(std::shared_ptr<ListType> attractors) {
      this->attractors = attractors;
    }

    void apply(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D > > avatar) {

      auto vpos = avatar->get<1, zbe::Vector3D>();
      auto vvel = avatar->get<2, zbe::Vector3D>();
      zbe::Vector3D pos = vpos->get(); 
      zbe::Vector3D fakeGrav{0.0,0.0,0.0};

      closest(pos, fakeGrav);
      //insideRadiusMean(pos, fakeGrav);
      vvel->set(fakeGrav);
    }

    void closest(zbe::Vector3D &pos, zbe::Vector3D &fakeGrav) {
      double bestDistance = INFINITY;
      for (auto attractor : *attractors) {
        auto v = attractor->get();
        zbe::Vector3D v3 = v->get();
        zbe::Vector3D direction = v3 - pos;
        double distance = direction.getModule();
        if (direction.getModule() < bestDistance) {
          fakeGrav = direction.setModule(ratio);
          bestDistance = distance;
        }
      }
    }

    void insideRadiusMean(zbe::Vector3D &pos, zbe::Vector3D &fakeGrav) {
      double x = 0.0;
      double y = 0.0;
      double z = 0.0;
      int amount = 0;

      for (auto attractor : *attractors) {
        auto v = attractor->get();
        zbe::Vector3D v3 = v->get();
        zbe::Vector3D dist = v3 - pos;
        if (dist.getModule() < radius) {
          x += v3.x;
          y += v3.y;
          z += v3.z;
          amount++;
        }
      }
      if (amount > 0) {
        printf("Attractors: %d\n", amount);
        fflush(stdout);
        x = x / amount;
        y = y / amount;
        z = z / amount;
      } else {
        printf("No attractors\n");
        fflush(stdout);
      }
      fakeGrav = zbe::Vector3D{x, y, z} - pos;
      fakeGrav = fakeGrav.setModule(ratio);
    }

  private:
    double radius;
    double ratio;
    std::shared_ptr<zbe::TicketedForwardList<zbe::SAvatar<zbe::Vector3D>>> attractors;
};

class NonRealGravityVelSetterBhvFtry : virtual public zbe::Factory {
public:

  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<NonRealGravityVelSetterBhv> nrgvs = std::shared_ptr<NonRealGravityVelSetterBhv>(new NonRealGravityVelSetterBhv);
    behaviorRsrc.insert("Behavior."s + name, nrgvs);
    specifcRsrc.insert("NonRealGravityVelSetterBhv."s + name, nrgvs);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
        auto j = *cfg;
        auto nrgvs = specifcRsrc.get("NonRealGravityVelSetterBhv."s + name);

        auto ratio = zbe::JSONFactory::loadParamCfgDict<double>(dStore, j, "ratio"s, "NonRealGravityVelSetterBhvFtry"s);
        if(!ratio) {
            return;
        }
        nrgvs->setRatio(*ratio);

        auto radius = zbe::JSONFactory::loadParamCfgDict<double>(dStore, j, "radius"s, "NonRealGravityVelSetterBhvFtry"s);
        if(!radius) {
            return;
        }
        nrgvs->setRadius(*radius);
        auto attractors = zbe::JSONFactory::loadParamCfgStoreP<NonRealGravityVelSetterBhv::ListType>(rsrclists, j, zbe::factories::listName, "list"s, "NonRealGravityVelSetterBhvFtry"s);
        if(!radius) {
            return;
        }

        nrgvs->setAttractorList(*attractors);
    } else {
        zbe::SysError::setError("NonRealGravityVelSetterBhvFtry config for "s + name + " not found."s);
    }
  }

private:

  zbe::RsrcStore<nlohmann::json>& configRsrc = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcDictionary<double>& dStore = zbe::RsrcDictionary<double>::getInstance();
  zbe::RsrcStore<zbe::Behavior<zbe::Vector3D, zbe::Vector3D> >& behaviorRsrc = zbe::RsrcStore<zbe::Behavior<zbe::Vector3D, zbe::Vector3D> >::getInstance();
  zbe::RsrcStore<NonRealGravityVelSetterBhv>& specifcRsrc = zbe::RsrcStore<NonRealGravityVelSetterBhv>::getInstance();
  zbe::RsrcStore<NonRealGravityVelSetterBhv::ListType>& rsrclists = zbe::RsrcStore<NonRealGravityVelSetterBhv::ListType>::getInstance();
};

} // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZBEHAVIORS_H_
