/**
 * Copyright 2011 Batis Degryll Ludo
 * @file builders.h
 * @since 2021-11-08
 * @date 2021-11-08
 * @author Batis Degryll Ludo
 * @brief A lot of builders.
 */

#ifndef ZBE_ENTITIES_BUILDERS_METABUILDER_H
#define ZBE_ENTITIES_BUILDERS_METABUILDER_H

#include "ZBE/core/entities/Entity.h"

#include "ZBE/core/system/system.h"

namespace zbe {

template<typename ...T>
class EntityBldr {
public:

  EntityBldr() = default;

  void operator()(std::shared_ptr<MAvatar<T...>> avt) {
    std::shared_ptr<Entity> ent = std::make_shared<Entity>();

    addValues<double>(ent, dCfgList, avt);
    addValues<float>(ent, fCfgList, avt);
    addValues<uint64_t>(ent, uCfgList, avt);
    addValues<int64_t>(ent, iCfgList, avt);
    addValues<bool>(ent, bCfgList, avt);
    addValues<Vector3D>(ent, v3CfgList, avt);
    addValues<Vector2D>(ent, v2CfgList, avt);
    addValues<String>(ent, sCfgList, avt);
    addValues<std::vector<std::string>>(ent, slCfgList, avt);

    for(auto& builder : builders) {
      builder(ent);
    }
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<double>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    dCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<float>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    fCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<uint64_t>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    uCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<int64_t>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    iCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<bool>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    bCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<Vector3D>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    v3CfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<Vector2D>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    v2CfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<std::string>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    sCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::function<std::shared_ptr<Value<std::vector<std:string>>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    slCfgList.push_front(cfg);
  }

  void addBldr(std::function<void(std::shared_ptr<Entity>)> builder) {
    builder.push_back(builder);
  }

private:

  template<typename U>
  void addValues(std::shared_ptr<Entity> ent, std::forward_list<std::pair<uint64_t, std::function<U(std::shared_ptr<MAvatar<T...>>)>>> cfgl, std::shared_ptr<MAvatar<T...>> avt) {
    for(auto& cfg : cfgl) {
      ent->set<U>(fcg.first, fcg.second(avt));
    }
  }

  std::forward_list<std::pair<uint64_t, std::function<Value<double>(std::shared_ptr<MAvatar<T...>>)>>> dCfgList;
  std::forward_list<std::pair<uint64_t, std::function<Value<float>(std::shared_ptr<MAvatar<T...>>)>>> fCfgList;
  std::forward_list<std::pair<uint64_t, std::function<Value<uint64_t>(std::shared_ptr<MAvatar<T...>>)>>> uCfgList;
  std::forward_list<std::pair<uint64_t, std::function<Value<int64_t>(std::shared_ptr<MAvatar<T...>>)>>> iCfgList;
  std::forward_list<std::pair<uint64_t, std::function<Value<bool>(std::shared_ptr<MAvatar<T...>>)>>> bCfgList;
  std::forward_list<std::pair<uint64_t, std::function<Value<Vector3D>(std::shared_ptr<MAvatar<T...>>)>>> v3CfgList;
  std::forward_list<std::pair<uint64_t, std::function<Value<Vector2D>(std::shared_ptr<MAvatar<T...>>)>>> v2CfgList;
  std::forward_list<std::pair<uint64_t, std::function<Value<std::string>(std::shared_ptr<MAvatar<T...>>)>>> sCfgList;
  std::forward_list<std::pair<uint64_t, std::function<Value<std::vector<std::string> >(std::shared_ptr<MAvatar<T...>>)>>> slCfgList;

  std::deque<std::function<void(std::shared_ptr<Entity>)>> builders;

};

template<typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionerBldr {
public:
  using Iner = zbe::Interactioner<ActorType, ReactorType, Shapes...>;
  void operator()(std::shared_ptr<Entity> ent) {
    ActorType actor = actorBuilder(ent);
    ReactorType reactor = reactorBuilder(ent);
    std::shared_ptr<Shape<Shapes...>> shape = shapeBuilder(ent);
    Iner iner(shape, actor, reactor);

    for(auto pair : inerLists) {
      auto ticket = pair.second->insert(iner);
      ent->addTicket(pair.first, ticket);
    }
  }

  void setActorBldr(std::function<ActorType(std::shared_ptr<Entity>)> actorBuilder) {
    this->actorBuilder = actorBuilder;
  }

  void setReactorBldr(std::function<ReactorType(std::shared_ptr<Entity>)> reactorBuilder) {
    this->reactorBuilder = reactorBuilder;
  }

  void setShapeBldr(std::function<std::shared_ptr<ShapeType>(std::shared_ptr<Entity>)> shapeBuilder) {
    this->shapeBuilder = shapeBuilder;
  }

  void addInerList(uint64_t idx, std::shared_ptr<zbe::TicketedForwardList<Iner>> list) {
    inerLists.push_front(std::pair<uint64_t, std::shared_ptr<zbe::TicketedForwardList<Iner>>>(idx, list));
  }

private:
  std::function<ActorType(std::shared_ptr<Entity>) > actorBuilder;
  std::function<ReactorType(std::shared_ptr<Entity>) > reactorBuilder;
  std::function<std::shared_ptr<Shape<Shapes...>>(std::shared_ptr<Entity>) > shapeBuilder;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<zbe::TicketedForwardList<Iner>>>> inerLists;
};

template<typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionatorBldr {
public:
  using Inator = zbe::Interactionator<ActorType, ReactorType, Shapes...>;
  using InatorList = std::shared_ptr<zbe::TicketedForwardList<Iner>>;
  using ActorTypeBldr = std::function<ActorType(std::shared_ptr<Entity>) >;
  using ReactorTypeBldr = std::function<ReactorType(std::shared_ptr<Entity>) >;
  using ShapeBldr = std::function<std::shared_ptr<Shape<Shapes...>>(std::shared_ptr<Entity>) >;

  void operator()(std::shared_ptr<Entity> ent) {
    ActorType actor = actorBuilder(ent);
    ReactorType reactor = reactorBuilder(ent);
    std::shared_ptr<Shape<Shapes...>> shape = shapeBuilder(ent);
    Inator inator(shape, actor, reactor);

    inator.setIners(internalInerList);

    for(auto pair : inerLists) {
      auto ticket = pair.second->insert(inator);
      ent->addTicket(pair.first, ticket);
    }
  }

  void setActorBldr(ActorTypeBldr actorBuilder) {
    this->actorBuilder = actorBuilder;
  }

  void setReactorBldr(ReactorTypeBldr reactorBuilder) {
    this->reactorBuilder = reactorBuilder;
  }

  void setShapeBldr(ShapeBldr shapeBuilder) {
    this->shapeBuilder = shapeBuilder;
  }

  void addInerList(uint64_t idx, InatorList list) {
    inerLists.push_front(std::pair<uint64_t, std::shared_ptr<zbe::TicketedForwardList<Iner>>>(idx, list));
  }

  void setInternalInerList(InatorList internalInerList) {
    this->internalInerList = internalInerList;
  }

private:
  ActorTypeBldr actorBuilder;
  ReactorTypeBldr reactorBuilder;
  ReactorTypeBldr shapeBuilder;
  std::forward_list<std::pair<uint64_t, InatorList>> inerLists;
  InatorList internalInerList;
};

template<typename IData, typename ...Traits>
class ActorBldr : ActorBldr<Traits...> {
  Actor<IData, Traits...> operator()(std::shared_ptr<Entity> ent) {
    Actor<IData, Traits...> actor;
    std::initializer_list<int>{(actor.setTrait<Traits>(buildFunct<Traits>(ent)) , 0)... };
  }

  template<typename U>
  std::function<void(Reactor<IData, U>*, IData)> buildFunct(std::shared_ptr<Entity> ent) {
    this->ActorBldr<IData, U>::buildFunct(ent);
  }
};

template<typename IData, typename Trait>
class ActorBldr<IData, Trait> {
public:
  using TraitFunct = std::function<void(Reactor<IData, Trait>*, IData)>;
  using SubBuild = std::function<TraitFunct(std::shared_ptr<Entity> ent)>;

  ActorBldr() : sb([](){return Actor<IData, Trait>::noAct;}) {}


  Actor<IData, Trait> operator() (std::shared_ptr<Entity> ent) {
    Actor<IData, Trait> actor;
    actor.setTrait(sb(ent));
  }

  TraitFunct buildFunct(std::shared_ptr<Entity> ent) {
    return sb(ent);
  }

  void setBuildFunct(SubBuild sb) {
    this->sb = sb;
  }
private:
  SubBuild sb;
};

template<typename IData, typename ...Traits>
class ReactorBldr : ReactorBldr<IData, Trait...> {
  Reactor<IData, Traits...> operator()(std::shared_ptr<Entity> ent) {
    Reactor<IData, Traits...> reactor;
    std::initializer_list<int>{(setReaction.setTrait<Traits>(buildFunct<Traits>(ent)) , 0)... };
  }

  template<typename U>
  std::function<void(IData, U)> buildFunct(std::shared_ptr<Entity> ent) {
    this->ReactorBldr<IData, U>::buildFunct(ent);
  }
};

template<typename IData, typename Trait>
class ReactorBldr<IData, Trait> {
public:
  using ReactFunct = std::function<void(IData, Trait)>;
  using SubBuild = std::function<ReactFunct(std::shared_ptr<Entity> ent)>;

  ReactorBldr() : sb([](){return Reactor<IData, Trait>::noReaction;}) {}


  Reactor<IData, Trait> operator() (std::shared_ptr<Entity> ent) {
    Reactor<IData, Trait> reactor;
    reactor.setReaction(sb(ent));
  }

  ReactFunct buildFunct(std::shared_ptr<Entity> ent) {
    return sb(ent);
  }

  void setBuildFunct(SubBuild sb) {
    this->sb = sb;
  }
private:
  SubBuild sb;
};

template<typename S, typename ...Shapes>
class ShapeBldr {
public:
  using SubBuild = std::function<std:shared_ptr<SAvatar<S>>(std::shared_ptr<Entity> ent)>;

  ShapeBldr() : sb([](){assert(false); return nullptr;});
  std::shared_ptr<Shape<Shapes...>> operator()(std::shared_ptr<Entity> ent) {
    std:shared_ptr<SAvatar<S>> avt = sb(ent);
    return std::make_shared<AvtShape<S, Shapes...>>(avt);
  }

  void setBuildFunct(SubBuild sb) {
    this->sb = sb;
  }

private:
  SubBuild sb;
};

// "cfg" :{
//   "double" : {
//     "idxLitName" : "cars.velBuilder",
//     "idxBlahName" : "cars.blahBuilder"
//   },
//   "uint" : true,
//   "Vector3D" : [
//     {"idxLitName" : "cars.velBuilder"}
//   ],
//   "builders": [
//     "maingame.wallnutInteractionerBuilder",
//     "maingame.wallnutGraphicsBuilder"
//   ]
// }

template<typename ...T>
class ZBEAPI EntityBldrFtry : public Factory {
public:

  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<EntityBldr<T...>> eb = std::make_shared<EntityBldr<T...>>();
    mainRsrc.insert("Function."s + name, eb);
    specificRsrc.insert("EntityBldr."s + name, eb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("EntityBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto eb = specificRsrc.get("EntityBldr."s + name);
    auto j = *cfg;

    if(!addList2Bldr<double>(j, eb)
    || !addList2Bldr<float>(j, eb)
    || !addList2Bldr<uint64_t>(j, eb)
    || !addList2Bldr<int64_t>(j, eb)
    || !addList2Bldr<bool>(j, eb)
    || !addList2Bldr<Vector3D>(j, eb)
    || !addList2Bldr<Vector2D>(j, eb)
    || !addList2Bldr<std::string>(j, eb)
    || !addList2Bldr<std::vector<std::string>>>(j, eb)) {
      return;
    };

    if (j["builders"].is_array()) {
      auto builders = j["builders"];
      for(auto it : builders) {
        auto name = it.get<std::string>();
        if(!extraBuilderStore.contains("Builders."s + name)) {
          SysError::setError("EntityBldrFtry builders config " + name + " inside Builders. is not an adecuate builder name."s);
          return;
        }
        eb->addBldr(extraBuilderStore.get("Builders."s + name));
      }
    } else if(j.contains("builders")) {
      SysError::setError("EntityBldrFtry config for builders, if present, must be a array."s);
    }
  }

private:

  template<VT>
  bool addList2Bldr(json& j, std::string type std::shared_ptr<EntityBldr<T...>> eb) {
    if (j[type].is_object()) {
      auto dcfg = j[type];
      for (auto item : dcfg.items()) {
        auto key = item.key();
        if(auto valueBuilder = JSONFactory::readFromStore<ValueBldr<double>>(doubleBuilderStore, dcfg, "Builders."s, key, "EntityBldrFtry"s)) {
          eb->addValueBldr(valueBuilder);
          return true;
        } else {
          SysError::setError("EntityBuilderFtry config for " + type + " " + key +" is not a " + type + " value builder name."s);
          return false;
        }
      }
    } else if(j.contains(type)) {
      SysError::setError("EntityBuilderFtry config for " + type + ", if present, must be a array."s);
      return false;
    }
    return true;
  }

  template<VT>
  using ValueBldr = std::function<Value<VT>(std::shared_ptr<MAvatar<T...>>)>;
  template<VT>
  using PairList = std::forward_list<std::pair<uint64_t, ValueBldr<VT>>>;
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<std::function<void(std::shared_ptr<MAvatar<T...>>)>>& mainRsrc = RsrcStore<std::function<void(std::shared_ptr<MAvatar<T...>>)>>::getInstance();
  RsrcStore<EntityBldr<T...>>& specificRsrc = RsrcStore<EntityBldr<T...>>::getInstance();

  RsrcStore<ValueBldr<double>> doubleBldrStore = RsrcStore<ValueBldr<double>>::getInstance();
  RsrcStore<ValueBldr<float>> floatBldrStore = RsrcStore<ValueBldr<float>>::getInstance();
  RsrcStore<ValueBldr<uint64_t>> uintBldrStore = RsrcStore<ValueBldr<uint64_t>>::getInstance();
  RsrcStore<ValueBldr<int64_t>> intBldrStore = RsrcStore<ValueBldr<int64_t>>::getInstance();
  RsrcStore<ValueBldr<bool>> boolBldrStore = RsrcStore<ValueBldr<bool>>::getInstance();
  RsrcStore<ValueBldr<Vector3D>> v3DBldrStore = RsrcStore<ValueBldr<Vector3D>>::getInstance();
  RsrcStore<ValueBldr<Vector2D>> v2DBldrStore = RsrcStore<ValueBldr<Vector2D>>::getInstance();
  RsrcStore<ValueBldr<std::string>> stringBldrStore = RsrcStore<ValueBldr<std::string>>::getInstance();
  RsrcStore<ValueBldr<std::vector<std::string>>> vStringBldrStore = RsrcStore<ValueBldr<std::vector<std::string>>>::getInstance();

  RsrcStore<std::function<void(std::shared_ptr<Entity>)>> extraBldrStore = RsrcStore<std::function<void(std::shared_ptr<Entity>)>>::getInstance();

  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();

  std::deque<std::function<void(std::shared_ptr<Entity>)>> builders;

};

template<typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionatorBldrFcry {
public:
    /* TODO borra esto
    using Inator = zbe::Interactionator<ActorType, ReactorType, Shapes...>;
    using InatorList = std::shared_ptr<zbe::TicketedForwardList<Iner>>;
    using ActorTypeBldr = std::function<ActorType(std::shared_ptr<Entity>) >;
    using ReactorTypeBldr = std::function<ReactorType(std::shared_ptr<Entity>) >;
    using ShapeBldr = std::function<std::shared_ptr<Shape<Shapes...>>(std::shared_ptr<Entity>) >;
    */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<InteractionatorBldr<IData, ActorType, ReactorType, Shapes...>> inatorb = std::make_shared<InteractionatorBldr<IData, ActorType, ReactorType, Shapes...>>();
    mainRsrc.insert("Function."s + name, eb);
    specificRsrc.insert("InteractionatorBldr."s + name, eb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("InteractionatorBldrFcry config for "s + name + " not found."s);
      return;
    }
    auto inatorb = specificRsrc.get("InteractionatorBldr."s + name);
    auto j = *cfg;
    auto actorBuilder = JSONFactory::readFromStore<InteractionatorBldr::ActorTypeBldr>(actorBldrRsrc, j, "actorbuilder"s, "InteractionatorBldr"s);
    if(!actorBuilder) {
      SysError::setError("InteractionatorBldrFcry config for actorbuilder is invalid"s);
      return;
    }
    auto reactorBuilder = JSONFactory::readFromStore<InteractionatorBldr::ReactorTypeBldr>(reactorBldrRsrc, j, "reactorbuilder"s, "InteractionatorBldr"s);
    if(!actorBuilder) {
      SysError::setError("InteractionatorBldrFcry config for reactorbuilder is invalid"s);
      return;
    }
    auto shapeBuilder = JSONFactory::readFromStore<InteractionatorBldr::ShapeBldr>(shapeRsrc, j, "shapebuilder"s, "InteractionatorBldr"s);
    if(!actorBuilder) {
      SysError::setError("InteractionatorBldrFcry config for shapebuilder is invalid"s);
      return;
    }
    auto list = JSONFactory::readFromStore<InteractionatorBldr::InatorList>(listRsrc, j, "interactioners"s, "InteractionatorBldr"s);
    if(!actorBuilder) {
      SysError::setError("InteractionatorBldrFcry config for shapebuilder is invalid"s);
      return;
    }

    inatorb->setActorBldr(actorBuilder);
    inatorb->setReactorBldr(reactorBuilder);
    inatorb->setShapeBldr(shapeBuilder);
    inatorb->setInternalInerList(list);

    JSONFactory::loadAllIdexed(listRsrc, j, "list"s, "InteractionatorBldr"s, [&](uint64_t idx, InatorList list) {
      inatorb->addInerList(idx, list);
    });

  }
private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<std::function<void(std::shared_ptr<MAvatar<T...>>)>>& mainRsrc = RsrcStore<std::function<void(std::shared_ptr<MAvatar<T...>>)>>::getInstance();
  RsrcStore<EntityBldr<T...>>& specificRsrc = RsrcStore<EntityBldr<T...>>::getInstance();

  RsrcStore<InatorList>& listRsrc = RsrcStore<EntityBldr<InatorList>::getInstance();
  RsrcStore<ActorTypeBldr>& actorBldrRsrc = RsrcStore<ActorTypeBldr>::getInstance();
  RsrcStore<ReactorTypeBldr>& reactorBldrRsrc = RsrcStore<ReactorTypeBldr>::getInstance();
  RsrcStore<ShapeBldr>& shapeBldrRsrc = RsrcStore<ShapeBldr>::getInstance();
};

TODO: InteractionerBldrFtry
TODO: Ftryses a saco de cada builder que hay aquí.
TODO: Construir Subuilders en ZandBokz.

}  // namespace zbe

#endif  // ZBE_ENTITIES_BUILDERS_METABUILDER_H
