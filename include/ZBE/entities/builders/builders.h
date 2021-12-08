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
class EntityBuilder {
public:

  EntityBuilder() = default;

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

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<double>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    dCfgList.push_front(cfg);
  }

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<float>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    fCfgList.push_front(cfg);
  }

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<uint64_t>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    uCfgList.push_front(cfg);
  }

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<int64_t>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    iCfgList.push_front(cfg);
  }

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<bool>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    bCfgList.push_front(cfg);
  }

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<Vector3D>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    v3CfgList.push_front(cfg);
  }

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<Vector2D>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    v2CfgList.push_front(cfg);
  }

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<std::string>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    sCfgList.push_front(cfg);
  }

  void addCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<std::vector<std:string>>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    slCfgList.push_front(cfg);
  }

  void addBuilder(std::function<void(std::shared_ptr<Entity>)> builder) {
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
class InteractionerBuilder {
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

  void setActorBuilder(std::function<ActorType(std::shared_ptr<Entity>)> actorBuilder) {
    this->actorBuilder = actorBuilder;
  }

  void setReactorBuilder(std::function<ReactorType(std::shared_ptr<Entity>)> reactorBuilder) {
    this->reactorBuilder = reactorBuilder;
  }

  void setShapeBuilder(std::function<std::shared_ptr<ShapeType>(std::shared_ptr<Entity>)> shapeBuilder) {
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
class InteractionatorBuilder {
public:
  using Inator = zbe::Interactionator<ActorType, ReactorType, Shapes...>;
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

  void setActorBuilder(std::function<ActorType(std::shared_ptr<Entity>)> actorBuilder) {
    this->actorBuilder = actorBuilder;
  }

  void setReactorBuilder(std::function<ReactorType(std::shared_ptr<Entity>)> reactorBuilder) {
    this->reactorBuilder = reactorBuilder;
  }

  void setShapeBuilder(std::function<std::shared_ptr<ShapeType>(std::shared_ptr<Entity>)> shapeBuilder) {
    this->shapeBuilder = shapeBuilder;
  }

  void addInerList(uint64_t idx, std::shared_ptr<zbe::TicketedForwardList<Iner>> list) {
    inerLists.push_front(std::pair<uint64_t, std::shared_ptr<zbe::TicketedForwardList<Iner>>>(idx, list));
  }

  void setInternalInerList(std::shared_ptr<zbe::TicketedForwardList<Iner>> internalInerList) {
    this->internalInerList = internalInerList;
  }

private:
  std::function<ActorType(std::shared_ptr<Entity>) > actorBuilder;
  std::function<ReactorType(std::shared_ptr<Entity>) > reactorBuilder;
  std::function<std::shared_ptr<Shape<Shapes...>>(std::shared_ptr<Entity>) > shapeBuilder;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<zbe::TicketedForwardList<Iner>>>> inerLists;
  std::shared_ptr<zbe::TicketedForwardList<Iner>>> internalInerList;
};

template<typename IData, typename ...Traits>
class ActorBuilder : ActorBuilder<Traits...> {
  Actor<IData, Traits...> operator()(std::shared_ptr<Entity> ent) {
    Actor<IData, Traits...> actor;
    std::initializer_list<int>{(actor.setTrait<Traits>(buildFunct<Traits>(ent)) , 0)... };
  }

  template<typename U>
  std::function<void(Reactor<IData, U>*, IData)> buildFunct(std::shared_ptr<Entity> ent) {
    this->ActorBuilder<IData, U>::buildFunct(ent);
  }
};

template<typename IData, typename Trait>
class ActorBuilder<IData, Trait> {
public:
  using TraitFunct = std::function<void(Reactor<IData, Trait>*, IData)>;
  using SubBuild = std::function<TraitFunct(std::shared_ptr<Entity> ent)>;

  ActorBuilder() : sb([](){return Actor<IData, Trait>::noAct;}) {}


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
class ReactorBuilder : ReactorBuilder<IData, Trait...> {
  Reactor<IData, Traits...> operator()(std::shared_ptr<Entity> ent) {
    Reactor<IData, Traits...> reactor;
    std::initializer_list<int>{(setReaction.setTrait<Traits>(buildFunct<Traits>(ent)) , 0)... };
  }

  template<typename U>
  std::function<void(IData, U)> buildFunct(std::shared_ptr<Entity> ent) {
    this->ReactorBuilder<IData, U>::buildFunct(ent);
  }
};

template<typename IData, typename Trait>
class ReactorBuilder<IData, Trait> {
public:
  using ReactFunct = std::function<void(IData, Trait)>;
  using SubBuild = std::function<ReactFunct(std::shared_ptr<Entity> ent)>;

  ReactorBuilder() : sb([](){return Reactor<IData, Trait>::noReaction;}) {}


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
class ShapeBuilder {
public:
  using SubBuild = std::function<std:shared_ptr<SAvatar<S>>(std::shared_ptr<Entity> ent)>;

  ShapeBuilder() : sb([](){assert(false); return nullptr;});
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

template<typename ...T>
class ZBEAPI EntityBuilderFtry : public Factory {
public:

  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<EntityBuilder<T...>> eb = std::make_shared<EntityBuilder<T...>>();
    mainRsrc.insert("Function."s + name, eb);
    specificRsrc.insert("EntityBuilder."s + name, eb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("EntityBuilderFtry config for "s + name + " not found."s);
      return;
    }
    auto eb = specificRsrc.get("EntityBuilder."s + name);
    auto j = *cfg;

    if(!addCfgList<double>()
    || !addCfgList<float>()
    || !addCfgList<uint64_t>()
    || !addCfgList<int64_t>()
    || !addCfgList<bool>()ç
    || !addCfgList<Vector3D>()
    || !addCfgList<Vector2D>()
    || !addCfgList<std::string>())
    || !addCfgList<std::vector<std::string>>>()) {
      return;
    };

    if (j["builders"].is_array()) {
      TODO : leer y poner builders.
    } else if(j.contains("builders")) {
      SysError::setError("EntityBuilderFtry config for builders, if present, must be a array."s);
    }
  }

private:

  template<VT>
  bool addCfgList(json& j, std::string type std::shared_ptr<EntityBuilder<T...>> eb) {
    if ( j[type].is_array()) {
      auto dcfg = j[type];
      for (auto item : dcfg.items()) {
        auto key = item.key();
        if(auto valueBuilder = JSONFactory::readFromStore<ValueBuilder<double>>(doubleBuilderStore, dcfg, key, "EntityBuilderFtry"s)) {
          eb->addDoubleCfg(valueBuilder);
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
  using ValueBuilder = std::function<Value<VT>(std::shared_ptr<MAvatar<T...>>)>;
  template<VT>
  using PairList = std::forward_list<std::pair<uint64_t, ValueBuilder<VT>>>;
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<std::function<void(std::shared_ptr<MAvatar<T...>>)>>& mainRsrc = RsrcStore<std::function<void(std::shared_ptr<MAvatar<T...>>)>>::getInstance();
  RsrcStore<EntityBuilder<T...>>& specificRsrc = RsrcStore<EntityBuilder<T...>>::getInstance();

  RsrcStore<ValueBuilder<double>> doubleBuilderStore = RsrcStore<ValueBuilder<double>>::getInstance();
  RsrcStore<ValueBuilder<float>> floatBuilderStore = RsrcStore<ValueBuilder<float>>::getInstance();
  RsrcStore<ValueBuilder<uint64_t>> uintBuilderStore = RsrcStore<ValueBuilder<uint64_t>>::getInstance();
  RsrcStore<ValueBuilder<int64_t>> intBuilderStore = RsrcStore<ValueBuilder<int64_t>>::getInstance();
  RsrcStore<ValueBuilder<bool>> boolBuilderStore = RsrcStore<ValueBuilder<bool>>::getInstance();
  RsrcStore<ValueBuilder<Vector3D>> v3DBuilderStore = RsrcStore<ValueBuilder<Vector3D>>::getInstance();
  RsrcStore<ValueBuilder<Vector2D>> v2DBuilderStore = RsrcStore<ValueBuilder<Vector2D>>::getInstance();
  RsrcStore<ValueBuilder<std::string>> stringBuilderStore = RsrcStore<ValueBuilder<std::string>>::getInstance();
  RsrcStore<ValueBuilder<std::vector<std::string>>> vStringBuilderStore = RsrcStore<ValueBuilder<std::vector<std::string>>>::getInstance();

  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();

  std::deque<std::function<void(std::shared_ptr<Entity>)>> builders;

};


TODO: InteractionerBuilderFtry
TODO: MetaBuilderFtry
TODO: Ftryses a saco de cada builder que hay aquí.
TODO: Construir Subuilders en ZandBokz.

}  // namespace zbe

#endif  // ZBE_ENTITIES_BUILDERS_METABUILDER_H
