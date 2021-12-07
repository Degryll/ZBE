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

  void addDoubleCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<double>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    dCfgList.push_front(cfg);
  }

  void addFloatCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<float>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    fCfgList.push_front(cfg);
  }

  void addUintCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<uint64_t>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    uCfgList.push_front(cfg);
  }

  void addIntCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<int64_t>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    iCfgList.push_front(cfg);
  }

  void addBoolCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<bool>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    bCfgList.push_front(cfg);
  }

  void addVector3DCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<Vector3D>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    v3CfgList.push_front(cfg);
  }

  void addVector2DCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<Vector2D>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    v2CfgList.push_front(cfg);
  }

  void addStringCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<std::string>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
    sCfgList.push_front(cfg);
  }

  void addStringListCfg(std::pair<uint64_t, std::function<std::shared_ptr<Value<std::vector<std:string>>>(std::shared_ptr<MAvatar<T...>>)> cfg) {
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

  /** \brief Builds a EntityBuilder.
   *  \param name Name for the created EntityBuilder.
   *  \param cfgId EntityBuilder's configuration id.
   */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<EntityBuilder<T...>> eb = std::make_shared<EntityBuilder<T...>>();
    mainRsrc.insert("Function."s + name, eb);
    iegRsrc.insert("EntityBuilder."s + name, eb);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("EntityBuilderFtry config for "s + name + " not found."s);
      return;
    }
    auto j = *cfg;
    if ( j["double"].is_array()) {
      auto dcfg = j["double"];
      for (auto item : dcfg.items()) {
        auto key = item.key();
        auto valBuilder = JSONFactory::readFromStore(RsrcStore<T> store, json cfg, std::string parameter, std::string factoryName); TODO: falta corregir estos parámetros
        TODO: Y lo que salga del store se mete en el builder con ddDoubleCfg.
      }
    } else if(JSONFactory::contains("double")) {
      SysError::setError("EntityBuilderFtry config for double, if present, must be a array."s);
      return;
    }

    // auto j = *cfg;
    // if (!j["eventId"].is_string()) {
    //   SysError::setError("InputEventGeneratorFtry config for eventId: "s + j["eventId"].get<std::string>() + ": must be a unsigned integer literal."s);
    //   return;
    // }
    //
    // if (!j["contextTime"].is_string()) {
    //   SysError::setError("InputEventGeneratorFtry config for contextTime: "s + j["contextTime"].get<std::string>() + ": must be an context time name."s);
    //   return;
    // }
    //
    // if (!j["inputBuffer"].is_string()) {
    //   SysError::setError("InputEventGeneratorFtry config for inputBuffer: "s + j["inputBuffer"].get<std::string>() + ": must be an inputBuffer name."s);
    //   return;
    // }
    //
    // if (!j["inputTextBuffer"].is_string()) {
    //   SysError::setError("InputEventGeneratorFtry config for inputTextBuffer: "s + j["inputTextBuffer"].get<std::string>() + ": must be an inputTextBuffer."s);
    //   return;
    // }
    //
    // std::string eventIdName = j["eventId"].get<std::string>();
    // if(!uintStore.contains(eventIdName)) {
    //   SysError::setError("InputEventGeneratorFtry config for eventId: "s + eventIdName + " does not exits."s);
    //   return;
    // }
    //
    // std::string contextTimeName = j["contextTime"].get<std::string>();
    // if(!cTimeRsrc.contains("ContextTime."s + contextTimeName)) {
    //   SysError::setError("InputEventGeneratorFtry config for contextTime: "s + contextTimeName + " does not exits."s);
    //   return;
    // }
    //
    // std::string inputBufferName = j["inputBuffer"].get<std::string>();
    // if(!ibuffRsrc.contains(inputBufferName)) {
    //   SysError::setError("InputEventGeneratorFtry config for inputBuffer: "s + inputBufferName + " does not exits."s);
    //   return;
    // }
    //
    // std::string inputTextBufferName = j["inputTextBuffer"].get<std::string>();
    // if(!itBuffRsrc.contains(inputTextBufferName)) {
    //   SysError::setError("InputEventGeneratorFtry config for : "s + inputTextBufferName + " does not exits."s);
    //   return;
    // }
    //
    // uint64_t eventId = uintStore.get(eventIdName);
    // auto cTime = cTimeRsrc.get("ContextTime."s + contextTimeName);
    // auto inputBuffer = ibuffRsrc.get(inputBufferName);
    // auto inputTextBuffer = itBuffRsrc.get(inputTextBufferName);
    // auto ieg = iegRsrc.get("InputEventGenerator."s + name);


    if (auto val = JSONFactory::readFromStore<double>()) {
        std::cout << "create2(true) returned " << *val << '\n';
    }

    ieg->setEventID(eventId);
    ieg->setInputBuffer(inputBuffer);
    ieg->setInputTextBuffer(inputTextBuffer);
    ieg->setContextTime(cTime);
  }

private:
  template<LT>
  using PairList = std::forward_list<std::pair<uint64_t, std::function<Value<LT>(std::shared_ptr<MAvatar<T...>>)>>>;
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<std::function<void(std::shared_ptr<MAvatar<T...>>)>>& mainRsrc = RsrcStore<std::function<void(std::shared_ptr<MAvatar<T...>>)>>::getInstance();
  RsrcStore<EntityBuilder<T...>>& specificRsrc = RsrcStore<EntityBuilder<T...>>::getInstance();
  // TODO potencialmente caca.
  RsrcStore<PairList<double>> dCfgListRsrc;
  RsrcStore<PairList<float>> fCfgListRsrc;
  RsrcStore<PairList<uint64_t>> uCfgListRsrc;
  RsrcStore<PairList<int64_t>> iCfgListRsrc;
  RsrcStore<PairList<bool>> bCfgListRsrc;
  RsrcStore<PairList<Vector3D>> v3CfgListRsrc;
  RsrcStore<PairList<Vector2D>> v2CfgListRsrc;
  RsrcStore<PairList<std::string>> sCfgListRsrc;
  RsrcStore<PairList<std::vector<std::string>>> slCfgListRsrc;
  // TODO potencialmente caca fin.

  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();

  std::deque<std::function<void(std::shared_ptr<Entity>)>> builders;

};


TODO: InteractionerBuilderFtry
TODO: MetaBuilderFtry
TODO: Ftryses a saco de cada builder que hay aquí.
TODO: Construir Subuilders en ZandBokz.

}  // namespace zbe

#endif  // ZBE_ENTITIES_BUILDERS_METABUILDER_H
