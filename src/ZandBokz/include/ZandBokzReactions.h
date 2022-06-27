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

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/tools.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zandbokz {

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
 BounceReaction(std::shared_ptr<zbe::SAvatar<zbe::Vector3D>> avt) : avt(avt) {}

 /** brief Erases entity
  *  param time not used
  */
 void operator()(IData idata, Trait) {
     auto val = avt->get()->get();
     zbe::Vector3D newVal = val.reflect(idata.normal);
     //avt->set(std::make_shared<zbe::SimpleValue<zbe::Vector3D>>(newVal));
     avt->set(newVal);
 }
private:
 std::shared_ptr<zbe::SAvatar<zbe::Vector3D>> avt;
};

template<typename IData, typename Trait>
class BounceReactionBldr : public zbe::Funct<std::shared_ptr<zbe::Funct<void, IData, Trait>>, std::shared_ptr<zbe::Entity>> {
public:
 std::shared_ptr<zbe::Funct<void, IData, Trait>> operator()(std::shared_ptr<zbe::Entity> ent){
   auto avt = std::make_shared<zbe::SBaseAvatar<zbe::Vector3D>>();
   avt->setupEntity(ent, idx);
   return std::make_shared<BounceReaction<IData, Trait>>(avt);
 }

 void setIdx(uint64_t idx) {
   this->idx = idx;
 }
private:
 uint64_t idx;
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

      msasb->setIdx(*vectorIdx);

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
