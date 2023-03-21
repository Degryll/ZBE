/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ZandBokzReactions.h
 * @since 2022-06-14
 * @date 2022-06-14
 * @author Ludo Degryll Batis
 * @brief ZandBokz Reactions
 */

 #ifndef ZANDBOKZ_ZANDBOKZREACTIONS_H_
 #define ZANDBOKZ_ZANDBOKZREACTIONS_H_

#include <cstdint>
#include <memory>
#include <cstdio>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/tools.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zandbokz {

//template<typename IData, typename Trait>
class AttachRepositionReaction : public zbe::Funct<void, zbe::CollisionData3D, Platform> {
public:
  AttachRepositionReaction(const AttachRepositionReaction&) = delete; //!< Avoid copy.
  void operator=(const AttachRepositionReaction&) = delete; //!< Avoid copy.

  static const int AVTSIZE = 3;

  /** brief Parametrized constructor
  * param avt Avatar to use
  */
  AttachRepositionReaction(std::shared_ptr<zbe::MAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector3D>> avatar) : avatar(avatar) {}

  /** brief Reposition entity on plane.
  */
  void operator()(zbe::CollisionData3D cData, Platform platform) {

    auto vpos2D = avatar->get<2, zbe::Vector2D>();
    
    auto planeE1 = platform[2]->get();
    auto planeE2 = platform[1]->get();
    auto planePos = platform[0]->get();

    auto pos2D = vpos2D->get();

    auto diff = zbe::Vector3D{cData.point.x, cData.point.y, cData.point.z} - planePos;
    zbe::Vector3D ax{1.0, 0.0, 0.0};
    zbe::Vector3D ay{0.0, 1.0, 0.0};
    zbe::Vector3D az{0.0, 0.0, 1.0};

    zbe::Vector3D bx = planeE1;
    zbe::Vector3D by = planeE2;
    zbe::Vector3D bz = zbe::cross(planeE1, planeE2).normalize();

    double x = diff * zbe::Vector3D{bx.x, bx.y, bx.z};
    double y = diff * zbe::Vector3D{by.x, by.y, by.z};
    double z = diff * zbe::Vector3D{bz.x, bz.y, bz.z};

    zbe::Vector3D coordChange{x,y,z};

    zbe::Vector2D newPos2D{coordChange.x, coordChange.y};
    avatar->set<2, zbe::Vector2D>(newPos2D);
      
  }
private:
  std::shared_ptr<zbe::MAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector3D>> avatar;
};

class AttachRepositionReactionBldr : public zbe::Funct<std::shared_ptr<zbe::Funct<void, zbe::CollisionData3D, Platform>>, std::shared_ptr<zbe::Entity>> {
public:
  std::shared_ptr<zbe::Funct<void, zbe::CollisionData3D, Platform>> operator()(std::shared_ptr<zbe::Entity> ent){
    auto avt = std::make_shared<zbe::MBaseAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector3D>>();
    avt->setupEntity(ent, idxArr);
    return std::make_shared<AttachRepositionReaction>(avt);
  }

  void setIdx(std::array<uint64_t, AttachRepositionReaction::AVTSIZE> idxArr) {
    this->idxArr = idxArr;
  }
private:
  std::array<uint64_t, AttachRepositionReaction::AVTSIZE> idxArr;
};

class AttachRepositionReactionBldrFtry : public zbe::Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<AttachRepositionReactionBldr> arrb = std::make_shared<AttachRepositionReactionBldr>();
    mainRsrc.insert("Function."s + name, arrb);
    specificRsrc.insert("AttachRepositionReactionBldr."s + name, arrb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto arrb = specificRsrc.get("AttachRepositionReactionBldr."s + name);

      std::optional<std::array<uint64_t, AttachRepositionReaction::AVTSIZE>> arr = zbe::JSONFactory::loadLiteralArray<uint64_t, AttachRepositionReaction::AVTSIZE>(uintDict, j["idxlist"], "idxlist", "StoreValuesRctBldrFtry");
      if(!arr) {
        return;
      }

      arrb->setIdx(*arr);
    } else {
      zbe::SysError::setError("AttachRepositionReactionBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = zbe::Funct<std::shared_ptr<zbe::Funct<void, zbe::CollisionData3D, Platform>>, std::shared_ptr<zbe::Entity>>;

  zbe::RsrcDictionary<uint64_t>& uintDict                     = zbe::RsrcDictionary<uint64_t>::getInstance();
  zbe::RsrcStore<nlohmann::json> &configRsrc                  = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcStore<AttachRepositionReactionBldr>& specificRsrc  = zbe::RsrcStore<AttachRepositionReactionBldr>::getInstance();
  zbe::RsrcStore<FunctionType>& mainRsrc                      = zbe::RsrcStore<FunctionType>::getInstance();
};

template<typename IData, typename Trait>
class ReverseDirectionReaction : public zbe::Funct<void, IData, Trait> {
public:
 ReverseDirectionReaction(const ReverseDirectionReaction&) = delete; //!< Avoid copy.
 void operator=(const ReverseDirectionReaction&) = delete; //!< Avoid copy.

 /** brief Empty constructor
  */
 ReverseDirectionReaction() = default;

 /** brief Parametrized constructor
  * param entity Entity to be erased
  */
 ReverseDirectionReaction(std::shared_ptr<zbe::SAvatar<zbe::Vector3D>> avt) : avt(avt) {}

 /** brief Erases entity
  *  param time not used
  */
 void operator()(IData, Trait) {
     auto val = avt->get()->get();
     zbe::Vector3D newVal = -val;
     //avt->set(std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(newVal));
     avt->set(newVal);
 }
private:
 std::shared_ptr<zbe::SAvatar<zbe::Vector3D>> avt;
};

template<typename IData, typename Trait>
class ReverseDirectionReactionBldr : public zbe::Funct<std::shared_ptr<zbe::Funct<void, IData, Trait>>, std::shared_ptr<zbe::Entity>> {
public:
 std::shared_ptr<zbe::Funct<void, IData, Trait>> operator()(std::shared_ptr<zbe::Entity> ent){
   auto avt = std::make_shared<zbe::SBaseAvatar<zbe::Vector3D>>();
   avt->setupEntity(ent, idx);
   return std::make_shared<ReverseDirectionReaction<IData, Trait>>(avt);
 }

 void setIdx(uint64_t idx) {
   this->idx = idx;
 }
private:
 uint64_t idx;
};

template<typename IData, typename Trait>
class ReverseDirectionReactionBldrFtry : public zbe::Factory {
// This class where c&p from DerivedPosMovingSphereAvtBldrFtry removing list managment
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<ReverseDirectionReactionBldr<IData, Trait>> rdrb = std::make_shared<ReverseDirectionReactionBldr<IData, Trait>>();
    mainRsrc.insert("Function."s + name, rdrb);
    specificRsrc.insert("ReverseDirectionReactionBldr."s + name, rdrb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto msasb = specificRsrc.get("ReverseDirectionReactionBldr."s + name);

      auto vectorIdx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "vectorIdx"s, "ReverseDirectionReactionBldrFtry"s);
      if(!vectorIdx) {
        return;
      }

      msasb->setIdx(*vectorIdx);

    } else {
      zbe::SysError::setError("ReverseDirectionReactionBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = zbe::Funct<std::shared_ptr<zbe::Funct<void, IData, Trait>>, std::shared_ptr<zbe::Entity>>;

  zbe::RsrcDictionary<uint64_t>& uintDict                                  = zbe::RsrcDictionary<uint64_t>::getInstance();
  zbe::RsrcStore<nlohmann::json> &configRsrc                               = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcStore<ReverseDirectionReactionBldr<IData, Trait>>& specificRsrc = zbe::RsrcStore<ReverseDirectionReactionBldr<IData, Trait>>::getInstance();
  zbe::RsrcStore<FunctionType>& mainRsrc                                   = zbe::RsrcStore<FunctionType>::getInstance();
};

// -------- Bounce reaction

template<typename IData, typename Trait>
class BounceReaction : public zbe::Funct<void, IData, Trait> {
public:
 BounceReaction(const BounceReaction&) = delete; //!< Avoid copy.
 void operator=(const BounceReaction&) = delete; //!< Avoid copy.

 /** brief Empty constructor
  */
 BounceReaction() = default;

 /** brief Parametrized constructor
  * param entity Entity to be erased
  */
 BounceReaction(std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt) : avt(avt) {}

 /** brief Erases entity
  *  param time not used
  */
  void operator()(IData idata, Trait) {
    auto vval = avt->get<1, zbe::Vector3D>();
    auto uval = avt->get<2, zbe::Vector3D>();
    zbe::Vector3D newvVal = vval->get().reflect(idata.normal);
    zbe::Vector3D newuVal = uval->get().reflect(idata.normal);
    vval->set(newvVal);
    uval->set(-newuVal);
  }
private:
 std::shared_ptr<zbe::MAvatar<zbe::Vector3D, zbe::Vector3D>> avt;
};

template<typename IData, typename Trait>
class BounceReactionBldr : public zbe::Funct<std::shared_ptr<zbe::Funct<void, IData, Trait>>, std::shared_ptr<zbe::Entity>> {
public:
 std::shared_ptr<zbe::Funct<void, IData, Trait>> operator()(std::shared_ptr<zbe::Entity> ent){
   auto avt = std::make_shared<zbe::MBaseAvatar<zbe::Vector3D, zbe::Vector3D>>();
   avt->setupEntity(ent, {uidx, vidx});
   return std::make_shared<BounceReaction<IData, Trait>>(avt);
 }

 void setIdx(uint64_t uidx, uint64_t vidx) {
   this->vidx = vidx;
   this->uidx = uidx;
 }
private:
 uint64_t uidx;
 uint64_t vidx;
};

template<typename IData, typename Trait>
class BounceReactionBldrFtry : public zbe::Factory {
// This class where c&p from DerivedPosMovingSphereAvtBldrFtry removing list managment
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<BounceReactionBldr<IData, Trait>> rdrb = std::make_shared<BounceReactionBldr<IData, Trait>>();
    mainRsrc.insert("Function."s + name, rdrb);
    specificRsrc.insert("BounceReactionBldr."s + name, rdrb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto msasb = specificRsrc.get("BounceReactionBldr."s + name);

      auto vectorIdx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "vectorIdx"s, "BounceReactionBldrFtry"s);
      if(!vectorIdx) {
        return;
      }

      auto upwardsIdx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "upwardsIdx"s, "BounceReactionBldrFtry"s);
      if(!upwardsIdx) {
        return;
      }

      msasb->setIdx(*upwardsIdx, *vectorIdx);

    } else {
      zbe::SysError::setError("BounceReactionBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = zbe::Funct<std::shared_ptr<zbe::Funct<void, IData, Trait>>, std::shared_ptr<zbe::Entity>>;

  zbe::RsrcDictionary<uint64_t>& uintDict                                  = zbe::RsrcDictionary<uint64_t>::getInstance();
  zbe::RsrcStore<nlohmann::json> &configRsrc                               = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcStore<BounceReactionBldr<IData, Trait>>& specificRsrc = zbe::RsrcStore<BounceReactionBldr<IData, Trait>>::getInstance();
  zbe::RsrcStore<FunctionType>& mainRsrc                                   = zbe::RsrcStore<FunctionType>::getInstance();
};


} // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZREACTIONS_H_
