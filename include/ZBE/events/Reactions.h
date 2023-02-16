/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ZandBokzReactions.h
 * @since 2022-06-14
 * @date 2022-06-14
 * @author Ludo Degryll Batis
 * @brief ZandBokz Reactions
 */

 #ifndef ZBE_EVENTS_REACTIONS_H_
 #define ZBE_EVENTS_REACTIONS_H_

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

namespace zbe {

template<typename IData, typename Trait>
class TicketActivatorRct : public Funct<void, IData, Trait> {
public:

  /** brief Empty constructor
   */
  TicketActivatorRct() = default;

  /** brief Parametrized constructor
   */
  TicketActivatorRct(std::shared_ptr<Avatar> avt) : avt(avt) {}

  /** brief Activate configured tickets
   *  param time not used
   */
  void operator()(IData, Trait) {
    for(auto& t : list ) {
      avt->setACTIVE(t);
    }
  }

  void setTicketList(std::forward_list<uint64_t> list) {
    this->list = list;
  }
private:
  std::shared_ptr<Avatar> avt;
  std::forward_list<uint64_t> list;
};

template<typename IData, typename Trait>
class TicketDeactivatorRct : public Funct<void, IData, Trait> {
public:

  /** brief Empty constructor
   */
  TicketDeactivatorRct() = default;

  /** brief Parametrized constructor
   */
  TicketDeactivatorRct(std::shared_ptr<Avatar> avt) : avt(avt) {}

  /** brief Deactivate configured tickets
   *  param time not used
   */
  void operator()(IData, Trait) {
    for(auto& t : list ) {
      avt->setINACTIVE(t);
    }
  }

  void setTicketList(std::forward_list<uint64_t> list) {
    this->list = list;
  }
private:
  std::shared_ptr<Avatar> avt;
  std::forward_list<uint64_t> list;
};


template<typename IData, typename ValueType, unsigned n>
class StoreValuesRct : public Funct<void, IData, std::array<std::shared_ptr<Value<ValueType>>, n>> {
public:
 /** brief Empty constructor
  */
 StoreValuesRct() = default;

  /** brief Parametrized constructor
  */
 StoreValuesRct(std::shared_ptr<AwareAvatar> avt) : avt(avt) {}

 void operator()(IData, std::array<std::shared_ptr<Value<ValueType>>, n> trait) {
   auto ent = avt->getEntity();
   for(int i =0; i< n; i++) {
     ent->override<ValueType>(dest[i], trait[i]);
   }
 }

 void setDestinyList(std::array<uint64_t, n> dest) {
   this->dest = dest;
 }

private:
 std::shared_ptr<AwareAvatar> avt;
 std::array<uint64_t, n> dest;
};

template<typename IData, typename Trait>
class TicketActivatorRctBldr : public Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>> {
public:
std::shared_ptr<Funct<void, IData, Trait>> operator()(std::shared_ptr<Entity> ent){
  auto avt = std::make_shared<BaseAvatar>(ent);
  auto tar = std::make_shared<TicketActivatorRct<IData, Trait>>(avt);
  tar->setTicketList(list);
  return tar;
}

 void setTicketList(std::forward_list<uint64_t> list) {
   this->list = list;
 }
private:
std::forward_list<uint64_t> list;
};

template<typename IData, typename Trait>
class TicketDeactivatorRctBldr : public Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>> {
public:
std::shared_ptr<Funct<void, IData, Trait>> operator()(std::shared_ptr<Entity> ent){
  auto avt = std::make_shared<BaseAvatar>(ent);
  auto tar = std::make_shared<TicketDeactivatorRct<IData, Trait>>(avt);
  tar->setTicketList(list);
  return tar;
}

 void setTicketList(std::forward_list<uint64_t> list) {
   this->list = list;
 }
private:
std::forward_list<uint64_t> list;
};

template<typename IData, typename ValueType, unsigned n>
//class StoreValuesRctBldr : public Funct<std::shared_ptr<Funct<Funct<std::shared_ptr<Funct<void, IData, std::array<std::shared_ptr<Value<ValueType>>, n>>>>,std::shared_ptr<Entity>>>> {

class StoreValuesRctBldr : public Funct<std::shared_ptr<Funct<void, IData, std::array<std::shared_ptr<Value<ValueType>>, n>>>, std::shared_ptr<Entity>> {
public:
std::shared_ptr<Funct<void, IData, std::array<std::shared_ptr<Value<ValueType>>, n>>> operator()(std::shared_ptr<Entity> ent){
  auto avt = std::make_shared<AwareAvatar>(ent);
  auto tar = std::make_shared<StoreValuesRct<IData, ValueType, n>>(avt);
  tar->setDestinyList(dest);
  return tar;
}

 void setDestinyList(std::array<uint64_t, n> dest) {
   this->dest = dest;
 }
private:
 std::array<uint64_t, n> dest;
};

template<typename IData, typename Trait>
class TicketActivatorRctBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<TicketActivatorRctBldr<IData, Trait>> tarb = std::make_shared<TicketActivatorRctBldr<IData, Trait>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, tarb);
    specificRsrc.insert("TicketActivatorRctBldr."s + name, tarb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto tarb = specificRsrc.get("TicketActivatorRctBldr."s + name);

      std::optional<std::forward_list<uint64_t>> list = JSONFactory::loadLiteralList<uint64_t>(uintDict, j["tickets"], "tickets", "TicketActivatorRctBldrFtry");
      if(!list) {
          return;
      }
      tarb->setTicketList(*list);

    } else {
      SysError::setError("TicketActivatorRctBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>>;

  RsrcDictionary<uint64_t>& uintDict                                  = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                               = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<TicketActivatorRctBldr<IData, Trait>>& specificRsrc = RsrcStore<TicketActivatorRctBldr<IData, Trait>>::getInstance();
  RsrcStore<FunctionType>& mainRsrc                                   = RsrcStore<FunctionType>::getInstance();
};

template<typename IData, typename Trait>
class TicketDeactivatorRctBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<TicketDeactivatorRctBldr<IData, Trait>> tarb = std::make_shared<TicketDeactivatorRctBldr<IData, Trait>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, tarb);
    specificRsrc.insert("TicketDeactivatorRctBldr."s + name, tarb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto tarb = specificRsrc.get("TicketDeactivatorRctBldr."s + name);

      std::optional<std::forward_list<uint64_t>> list = JSONFactory::loadLiteralList<uint64_t>(uintDict, j["tickets"], "tickets", "TicketDeactivatorRctBldrFtry");
      if(!list) {
          return;
      }
      tarb->setTicketList(*list);

    } else {
      SysError::setError("TicketDeactivatorRctBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>>;

  RsrcDictionary<uint64_t>& uintDict                                  = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                               = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<TicketDeactivatorRctBldr<IData, Trait>>& specificRsrc      = RsrcStore<TicketDeactivatorRctBldr<IData, Trait>>::getInstance();
  RsrcStore<FunctionType>& mainRsrc                                   = RsrcStore<FunctionType>::getInstance();
};

template<typename IData, typename ValueType, unsigned n>
class StoreValuesRctBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<StoreValuesRctBldr<IData, ValueType, n>> tarb = std::make_shared<StoreValuesRctBldr<IData, ValueType, n>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, tarb);
    specificRsrc.insert("StoreValuesRctBldr."s + name, tarb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto tarb = specificRsrc.get("StoreValuesRctBldr."s + name);

      std::optional<std::array<uint64_t, n>> arr = JSONFactory::loadLiteralArray<uint64_t, n>(uintDict, j["idxlist"], "idxlist", "StoreValuesRctBldrFtry");
      if(!arr) {
        return;
      }
      tarb->setDestinyList(*arr);

    } else {
      SysError::setError("StoreValuesRctBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<Funct<void, IData, std::array<std::shared_ptr<Value<ValueType>>, n>>>, std::shared_ptr<Entity>>;

  RsrcDictionary<uint64_t>& uintDict                        = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                     = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<StoreValuesRctBldr<IData, ValueType, n>>& specificRsrc = RsrcStore<StoreValuesRctBldr<IData, ValueType, n>>::getInstance();
  RsrcStore<FunctionType>& mainRsrc                         = RsrcStore<FunctionType>::getInstance();
};

template<typename IData, typename Trait>
class MultiRct : public Funct<void, IData, Trait> {
public:

  /** brief Empty constructor
   */
  MultiRct() = default;

  /** brief Activate configured tickets
   *  param time not used
   */
  void operator()(IData data, Trait trait) {
    for(auto& r : reactions ) {
      (*r)(data, trait);
    }
  }

  void addReaction(std::shared_ptr<Funct<void, IData, Trait>> rctn) {
    this->reactions.push_front(rctn);
  }

private:
  std::forward_list<std::shared_ptr<Funct<void, IData, Trait>>> reactions;
};

template<typename IData, typename Trait>
class MultiRctBldr : public Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>> {
public:
  std::shared_ptr<Funct<void, IData, Trait>> operator()(std::shared_ptr<Entity> ent){
  auto mr = std::make_shared<MultiRct<IData, Trait>>();
    for(auto builder : bldrs) {
      auto rct = (*builder)(ent);
      mr->addReaction(rct);
    }
    return mr;
  }

  void addBuilder(std::shared_ptr<Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>>> builder) {
    this->bldrs.push_front(builder);
  }

private:
  std::forward_list<std::shared_ptr<Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>>>> bldrs;
};


template<typename IData, typename Trait>
class MultiRctBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<MultiRctBldr<IData, Trait>> tarb = std::make_shared<MultiRctBldr<IData, Trait>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, tarb);
    specificRsrc.insert("MultiRctBldr."s + name, tarb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto tarb = specificRsrc.get("MultiRctBldr."s + name);

      JSONFactory::loadAll<FunctionType>(mainRsrc, j, zbe::factories::functionName, "reactionBuilders"s, "MultiRctBldrFtry"s,
        [&](std::shared_ptr<FunctionType> rctbldr) {
          tarb->addBuilder(rctbldr);
          return true;
        }
      );

    } else {
      SysError::setError("MultiRctBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<Funct<void, IData, Trait>>, std::shared_ptr<Entity>>;

  RsrcStore<nlohmann::json> &configRsrc               = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<MultiRctBldr<IData, Trait>>& specificRsrc = RsrcStore<MultiRctBldr<IData, Trait>>::getInstance();
  RsrcStore<FunctionType>& mainRsrc                   = RsrcStore<FunctionType>::getInstance();
};


} // namespace zbe

#endif  // ZBE_EVENTS_REACTIONS_H_

