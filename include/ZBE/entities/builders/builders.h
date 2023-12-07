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

#include <cstdio>
#include <deque>
#include <memory>
#include <string>
#include <initializer_list>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/events/interactionSystem.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/tools/tools.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/JSON/JSONFactory.h"

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

namespace zbe {


class EntityBldr : public Funct<void> {
public:
  void operator()() {
    std::shared_ptr<Entity> ent = std::make_shared<Entity>();
    ent->setContextTime(contextTime);
    for(auto& builder : builders) {
      (*builder)(ent);
    }
  }

  void addBldr(std::shared_ptr<Funct<void, std::shared_ptr<Entity>>> builder) {
    builders.push_back(builder);
  }

  void setContextTime(std::shared_ptr<ContextTime> contextTime) {
    this->contextTime = contextTime;
  }

private:
  std::deque<std::shared_ptr<Funct<void, std::shared_ptr<Entity>>>> builders;
  std::shared_ptr<ContextTime> contextTime;
};



template<typename T, typename ...Ts>
class BehaviorEntityBldr : public Funct<void, std::shared_ptr<MAvatar<T, Ts...>>> {
public:

  void operator()(std::shared_ptr<MAvatar<T, Ts...>> avt) {
    std::shared_ptr<Entity> ent = std::make_shared<Entity>();
    ent->setContextTime(contextTime);

    addValues<double>(ent, dCfgList, avt);
    addValues<float>(ent, fCfgList, avt);
    addValues<uint64_t>(ent, uCfgList, avt);
    addValues<int64_t>(ent, iCfgList, avt);
    addValues<bool>(ent, bCfgList, avt);
    addValues<Vector3D>(ent, v3CfgList, avt);
    addValues<Vector2D>(ent, v2CfgList, avt);
    addValues<std::string>(ent, sCfgList, avt);
    addValues<std::vector<std::string>>(ent, slCfgList, avt);

    for(auto& builder : builders) {
      (*builder)(ent);
    }
  }
  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<double>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    dCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<float>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    fCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<uint64_t>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    uCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<int64_t>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    iCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<bool>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    bCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    v3CfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<Vector2D>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    v2CfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<std::string>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    sCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<std::vector<std::string>>>, std::shared_ptr<MAvatar<T, Ts...>>>>> cfg) {
    slCfgList.push_front(cfg);
  }

  void addBldr(std::shared_ptr<Funct<void, std::shared_ptr<Entity>>> builder) {
    builders.push_back(builder);
  }

  void setContextTime(std::shared_ptr<ContextTime> contextTime) {
    this->contextTime = contextTime;
  }

private:

  template<typename U>
  void addValues(std::shared_ptr<Entity> ent, std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<U>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> cfgl, std::shared_ptr<MAvatar<T, Ts...>> avt) {
    for(auto& cfg : cfgl) {
      std::shared_ptr<Funct<std::shared_ptr<Value<U>>, std::shared_ptr<MAvatar<T, Ts...>>>> second = cfg.second;
      ent->set<U>(cfg.first, (*second)(avt)); //*(cfg.second)
    }
  }

  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<double>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> dCfgList{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<float>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> fCfgList{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<uint64_t>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> uCfgList{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<int64_t>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> iCfgList{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<bool>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> bCfgList{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> v3CfgList{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<Vector2D>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> v2CfgList{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<std::string>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> sCfgList{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<std::vector<std::string>>>, std::shared_ptr<MAvatar<T, Ts...>>>>>> slCfgList{};

  std::deque<std::shared_ptr<Funct<void, std::shared_ptr<Entity>>>> builders{};
  std::shared_ptr<ContextTime> contextTime{};

};

template<typename T>
class BehaviorEntityBldr<T> : public Funct<void, std::shared_ptr<SAvatar<T>>> {
public:

  BehaviorEntityBldr() = default;

  void operator()(std::shared_ptr<SAvatar<T>> avt) {
    std::shared_ptr<Entity> ent = std::make_shared<Entity>();

    addValues<double>(ent, dCfgList, avt);
    addValues<float>(ent, fCfgList, avt);
    addValues<uint64_t>(ent, uCfgList, avt);
    addValues<int64_t>(ent, iCfgList, avt);
    addValues<bool>(ent, bCfgList, avt);
    addValues<Vector3D>(ent, v3CfgList, avt);
    addValues<Vector2D>(ent, v2CfgList, avt);
    addValues<std::string>(ent, sCfgList, avt);
    addValues<std::vector<std::string>>(ent, slCfgList, avt);

    for(auto& builder : builders) {
      (*builder)(ent);
    }
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<double>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    dCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<float>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    fCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<uint64_t>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    uCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<int64_t>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    iCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<bool>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    bCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    v3CfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<Vector2D>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    v2CfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<std::string>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    sCfgList.push_front(cfg);
  }

  void addValueBldr(std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<std::vector<std::string>>>, std::shared_ptr<SAvatar<T>>>>> cfg) {
    slCfgList.push_front(cfg);
  }

  void addBldr(std::shared_ptr<Funct<void, std::shared_ptr<Entity>>> builder) {
    builders.push_back(builder);
  }

private:

  template<typename U>
  void addValues(std::shared_ptr<Entity> ent, std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<U>>, std::shared_ptr<SAvatar<T>>>>>> cfgl, std::shared_ptr<SAvatar<T>> avt) {
    for(auto& cfg : cfgl) {
      ent->set<U>(cfg.first, cfg.second(avt));
    }
  }

  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<double>>, std::shared_ptr<SAvatar<T>>>>>> dCfgList;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<float>>, std::shared_ptr<SAvatar<T>>>>>> fCfgList;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<uint64_t>>, std::shared_ptr<SAvatar<T>>>>>> uCfgList;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<int64_t>>, std::shared_ptr<SAvatar<T>>>>>> iCfgList;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<bool>>, std::shared_ptr<SAvatar<T>>>>>> bCfgList;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<SAvatar<T>>>>>> v3CfgList;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<Vector2D>>, std::shared_ptr<SAvatar<T>>>>>> v2CfgList;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<std::string>>, std::shared_ptr<SAvatar<T>>>>>> sCfgList;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Funct<std::shared_ptr<Value<std::vector<std::string>>>, std::shared_ptr<SAvatar<T>>>>>> slCfgList;

  std::deque<std::shared_ptr<Funct<void, std::shared_ptr<Entity>>>> builders;

};

class EntitySetter : public Funct<void, std::shared_ptr<Entity>> {
public:
  void operator()(std::shared_ptr<Entity> ent) {
    addValues<double>(ent, newDoubleValues, sharedDoubleValues);
    addValues<float>(ent, newFloatValues, sharedFloatValues);
    addValues<uint64_t>(ent, newUintValues, sharedUintValues);
    addValues<int64_t>(ent, newIntValues, sharedIntValues);
    addValues<bool>(ent, newBoolValues, sharedBoolValues);
    addValues<Vector3D>(ent, newVector3DValues, sharedVector3DValues);
    addValues<Vector2D>(ent, newVector2DValues, sharedVector2DValues);
    addValues<std::string>(ent, newStringValues, sharedStringValues);
    addValues<std::vector<std::string>>(ent, newVStringValues, sharedVStringValues);
  }


  void setNewDoubleValue(uint64_t index, double val ) {
    newDoubleValues.push_front(std::pair(index, val));
  }

  void setSharedDoubleValue(uint64_t index, std::shared_ptr<Value<double>> val ) {
    sharedDoubleValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<double, T>::value, void>::type
  setNewValue(uint64_t index, double val) {setNewDoubleValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<double, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<double>> val) {setSharedDoubleValue(index, val);}

  void setNewFloatValue(uint64_t index, float val ) {
    newFloatValues.push_front(std::pair(index, val));
  }

  void setSharedFloatValue(uint64_t index, std::shared_ptr<Value<float>> val ) {
    sharedFloatValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<float, T>::value, void>::type
  setNewValue(uint64_t index, float val) {setNewFloatValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<float, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<float>> val) {setSharedFloatValue(index, val);}

  void setNewUintValue(uint64_t index, uint64_t val ) {
    newUintValues.push_front(std::pair(index, val));
  }

  void setSharedUintValue(uint64_t index, std::shared_ptr<Value<uint64_t>> val ) {
    sharedUintValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<uint64_t, T>::value, void>::type
  setNewValue(uint64_t index, uint64_t val) {setNewUintValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<uint64_t, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<uint64_t>> val) {setSharedUintValue(index, val);}

  void setNewIntValue(uint64_t index, int64_t val ) {
    newIntValues.push_front(std::pair(index, val));
  }

  void setSharedIntValue(uint64_t index, std::shared_ptr<Value<int64_t>> val ) {
    sharedIntValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<int64_t, T>::value, void>::type
  setNewValue(uint64_t index, double val) {setNewIntValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<int64_t, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<int64_t>> val) {setSharedIntValue(index, val);}

  void setNewBoolValue(uint64_t index, bool val ) {
    newBoolValues.push_front(std::pair(index, val));
  }

  void setSharedBoolValue(uint64_t index, std::shared_ptr<Value<bool>> val ) {
    sharedBoolValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<bool, T>::value, void>::type
  setNewValue(uint64_t index, bool val) {setNewBoolValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<bool, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<bool>> val) {setSharedBoolValue(index, val);}

  void setNewVector3DValue(uint64_t index, Vector3D val ) {
    newVector3DValues.push_front(std::pair(index, val));
  }

  void setSharedVector3DValue(uint64_t index, std::shared_ptr<Value<Vector3D>> val ) {
    sharedVector3DValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<Vector3D, T>::value, void>::type
  setNewValue(uint64_t index, Vector3D val) {setNewVector3DValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<Vector3D, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<Vector3D>> val) {setSharedVector3DValue(index, val);}

  void setNewVector2DValue(uint64_t index, Vector2D val ) {
    newVector2DValues.push_front(std::pair(index, val));
  }

  void setSharedVector2DValue(uint64_t index, std::shared_ptr<Value<Vector2D>> val ) {
    sharedVector2DValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<Vector2D, T>::value, void>::type
  setNewValue(uint64_t index, Vector2D val) {setNewVector2DValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<Vector2D, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<Vector2D>> val) {setSharedVector2DValue(index, val);}

  void setNewStringValue(uint64_t index, std::string val ) {
    newStringValues.push_front(std::pair(index, val));
  }

  void setSharedStringValue(uint64_t index, std::shared_ptr<Value<std::string>> val ) {
    sharedStringValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<std::string, T>::value, void>::type
  setNewValue(uint64_t index, std::string val) {setNewStringValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<std::string, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<std::string>> val) {setSharedStringValue(index, val);}

  void setNewVStringValue(uint64_t index, std::vector<std::string> val ) {
    newVStringValues.push_front(std::pair(index, val));
  }

  void setSharedVStringValue(uint64_t index, std::shared_ptr<Value<std::vector<std::string>>> val ) {
    sharedVStringValues.push_front(std::pair(index, val));
  }

  template<typename T>
  typename std::enable_if<std::is_same<std::vector<std::string>, T>::value, void>::type
  setNewValue(uint64_t index, std::vector<std::string> val) {setNewVStringValue(index, val);}

  template<typename T>
  typename std::enable_if<std::is_same<std::vector<std::string>, T>::value, void>::type
  setSharedValue(uint64_t index, std::shared_ptr<Value<std::vector<std::string>>> val) {setSharedVStringValue(index, val);}

private:

  template<typename U>
  void addValues(std::shared_ptr<Entity> ent, std::forward_list<std::pair<uint64_t, U>>& newValues, std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<U>>>>& sharedValues) {
    for(auto& nv : newValues) {
      ent->set<U>(nv.first, std::make_shared<SimpleValue<U>>(nv.second));
    }
    for(auto& sv : sharedValues) {
      ent->set<U>(sv.first, sv.second);
    }
  }

  std::forward_list<std::pair<uint64_t, double>> newDoubleValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<double>>>> sharedDoubleValues;
  std::forward_list<std::pair<uint64_t, float>> newFloatValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<float>>>> sharedFloatValues;
  std::forward_list<std::pair<uint64_t, uint64_t>> newUintValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<uint64_t>>>> sharedUintValues;
  std::forward_list<std::pair<uint64_t, int64_t>> newIntValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<int64_t>>>> sharedIntValues;
  std::forward_list<std::pair<uint64_t, bool>> newBoolValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<bool>>>> sharedBoolValues;
  std::forward_list<std::pair<uint64_t, Vector3D>> newVector3DValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<Vector3D>>>> sharedVector3DValues;
  std::forward_list<std::pair<uint64_t, Vector2D>> newVector2DValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<Vector2D>>>> sharedVector2DValues;
  std::forward_list<std::pair<uint64_t, std::string>> newStringValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<std::string>>>> sharedStringValues;
  std::forward_list<std::pair<uint64_t, std::vector<std::string>>> newVStringValues;
  std::forward_list<std::pair<uint64_t, std::shared_ptr<Value<std::vector<std::string>>>>> sharedVStringValues;
};

template<template<typename T, typename ...Ts> class AVT, typename T, typename ...Ts>
class AvatarBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  static const int expectedIndexes = sizeof...(Ts) + 1;
  using AvtBaseType = MAvatar<T, Ts...>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<AvtImplType> avt = std::make_shared<AvtImplType>();
    avt->setupEntity(ent, idxArr);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
    for(auto indexNList : deactivatedIndexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
      // TODO crear metodo addTicket que permita pasar un bool indicando si es activo o no.
      ent->setINACTIVE(indexNList.first);
    }
  }

  void setIdxArr(std::array<uint64_t, expectedIndexes> idxArr) {
    this->idxArr = idxArr;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

  void addDeactivatedIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    deactivatedIndexNLists.push_back({index, list});
  }

private:
  using AvtImplType = AVT<T, Ts...>;
  std::array<uint64_t, expectedIndexes> idxArr{};
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists{};
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> deactivatedIndexNLists{};

};

template<template<typename T> class AVT, typename T>
class AvatarBldr<AVT, T> : public Funct<void, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = SAvatar<T>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<AvtImplType> avt = std::make_shared<AvtImplType>();
    avt->setupEntity(ent, idx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
    for(auto indexNList : deactivatedIndexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
      // TODO crear metodo addTicket que permita pasar un bool indicando si es activo o no.
      ent->setINACTIVE(indexNList.first);
    }
  }

  void setIdx(uint64_t idx) {
    this->idx = idx;
  }

  void setIdxArr(std::array<uint64_t, 1> idxArr) {
    this->idx = idxArr[0];
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

  void addDeactivatedIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    deactivatedIndexNLists.push_back({index, list});
  }

private:
  using AvtImplType = AVT<T>;
  uint64_t idx;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> deactivatedIndexNLists;

};

template<typename T>
class AvtVoid {
  T t;
};

template<>
class AvatarBldr<AvtVoid, void> : public Funct<void, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = Avatar;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<AvtImplType> avt = std::make_shared<AvtImplType>(ent);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
    for(auto indexNList : deactivatedIndexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
      // TODO crear metodo addTicket que permita pasar un bool indicando si es activo o no.
      ent->setINACTIVE(indexNList.first);
    }
  }

  void setIdx(uint64_t idx) {
    this->idx = idx;
  }

  void setIdxArr(std::array<uint64_t, 1> idxArr) {
    this->idx = idxArr[0];
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

  void addDeactivatedIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    deactivatedIndexNLists.push_back({index, list});
  }

private:
  using AvtImplType = BaseAvatar;
  uint64_t idx;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> deactivatedIndexNLists;

};

template<template<typename ...Ts> class AVT, typename... Ts>
class _AvatarBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<AvatarBldr<AVT, Ts...>> ab = std::make_shared<AvatarBldr<AVT, Ts...>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, ab);
    specificRsrc.insert("AvatarBldr."s + name, ab);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("AvatarBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto ab = specificRsrc.get("AvatarBldr."s + name);
    auto j = *cfg;

    std::optional<std::array<uint64_t, expectedIndexes>> arr = JSONFactory::loadLiteralArray<uint64_t, expectedIndexes>(uintDict, j["attribIndexes"], "attribIndexes", "AvatarBldrFtry");
    if(!arr) {
      return;
    }
    ab->setIdxArr(*arr);

    JSONFactory::loadAllIndexed<TicketedForwardList<typename AvatarBldr<AVT, Ts...>::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "AvatarBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<ListType> list) {
          ab->addIndexNlist(idx, list);
          return true;
        }
    );

    JSONFactory::loadAllIndexed<TicketedForwardList<typename AvatarBldr<AVT, Ts...>::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "deactivatedlists"s, "AvatarBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<ListType> list) {
          ab->addDeactivatedIndexNlist(idx, list);
          return true;
        }
    );
  }

private:
  static const int expectedIndexes = sizeof...(Ts);
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<typename AvatarBldr<AVT, Ts...>::AvtBaseType>;
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<AvatarBldr<AVT, Ts...>>& specificRsrc = RsrcStore<AvatarBldr<AVT, Ts...>>::getInstance();
  RsrcStore<ListType>& listRsrc = RsrcStore<ListType>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
};

template<typename ...Ts>
using MAvatarBldrFtry = _AvatarBldrFtry<MBaseAvatar, Ts...>;

template<typename T>
using SAvatarBldrFtry = _AvatarBldrFtry<SBaseAvatar, T>;

template<typename T, typename ...Ts>
using MDynamicAvatarBldrFtry = _AvatarBldrFtry<MDynamicAvatar, T, Ts...>;

template<typename T>
using SDynamicAvatarBldrFtry = _AvatarBldrFtry<SDynamicAvatar, T>;


class AvatarBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<AvatarBldr<AvtVoid, void>> ab = std::make_shared<AvatarBldr<AvtVoid, void>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, ab);
    specificRsrc.insert("AvatarBldr."s + name, ab);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("AvatarBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto ab = specificRsrc.get("AvatarBldr."s + name);
    auto j = *cfg;

    JSONFactory::loadAllIndexed<TicketedForwardList<typename AvatarBldr<AvtVoid, void>::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "AvatarBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<ListType> list) {
          ab->addIndexNlist(idx, list);
          return true;
        }
    );

    JSONFactory::loadAllIndexed<TicketedForwardList<typename AvatarBldr<AvtVoid, void>::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "deactivatedlists"s, "AvatarBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<ListType> list) {
          ab->addDeactivatedIndexNlist(idx, list);
          return true;
        }
    );
  }

private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<typename AvatarBldr<AvtVoid, void>::AvtBaseType>;
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<AvatarBldr<AvtVoid, void>>& specificRsrc = RsrcStore<AvatarBldr<AvtVoid, void>>::getInstance();
  RsrcStore<ListType>& listRsrc = RsrcStore<ListType>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
};


template<typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionerBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  using Iner = Interactioner<ActorType, ReactorType, Shapes...>;
  using InerList = TicketedForwardList<Iner>;
  using ActorTypeBldr = Funct<ActorType, std::shared_ptr<Entity>>;
  using ReactorTypeBldr = Funct<ReactorType, std::shared_ptr<Entity>>;
  using ShapeBldr = Funct<std::shared_ptr<Shape<Shapes...>>, std::shared_ptr<Entity>>;
  void operator()(std::shared_ptr<Entity> ent) {
    ActorType actor = (*actorBuilder)(ent);
    ReactorType reactor = (*reactorBuilder)(ent);
    std::shared_ptr<Shape<Shapes...>> shape = (*shapeBuilder)(ent);
    auto iner = std::make_shared<Iner>(shape, actor, reactor);
    for(auto pair : inerLists) {
      auto ticket = pair.second->push_front(iner);
      ent->addTicket(pair.first, ticket);
    }
    for(auto pair : deactivatedInerLists) {
      auto ticket = pair.second->push_front(iner);
      ent->addTicket(pair.first, ticket);
      ent->setINACTIVE(pair.first);
    }
  }

  void setActorBldr(std::shared_ptr<ActorTypeBldr> actorBuilder) {
    this->actorBuilder = actorBuilder;
  }

  void setReactorBldr(std::shared_ptr<ReactorTypeBldr> reactorBuilder) {
    this->reactorBuilder = reactorBuilder;
  }

  void setShapeBldr(std::shared_ptr<ShapeBldr> shapeBuilder) {
    this->shapeBuilder = shapeBuilder;
  }

  void addInerList(uint64_t idx, std::shared_ptr<InerList> list) {
    inerLists.push_front(std::pair<uint64_t, std::shared_ptr<TicketedForwardList<Iner>>>(idx, list));
  }

  void addDeactivatedInerList(uint64_t idx, std::shared_ptr<InerList> list) {
    deactivatedInerLists.push_front(std::pair<uint64_t, std::shared_ptr<TicketedForwardList<Iner>>>(idx, list));
  }

private:
  std::shared_ptr<ActorTypeBldr> actorBuilder{};
  std::shared_ptr<ReactorTypeBldr> reactorBuilder{};
  std::shared_ptr<ShapeBldr> shapeBuilder{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<InerList>>> inerLists{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<InerList>>> deactivatedInerLists{};
};

template<typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionatorBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  using Inator = Interactionator<ActorType, ReactorType, Shapes...>;
  using Iner = Interactioner<ActorType, ReactorType, Shapes...>;
  using InerList = TicketedForwardList<Iner>;
  using InatorList = TicketedForwardList<Inator>;
  using ActorTypeBldr = Funct<ActorType, std::shared_ptr<Entity>>;
  using ReactorTypeBldr = Funct<ReactorType, std::shared_ptr<Entity>>;
  using ShapeBldr = Funct<std::shared_ptr<Shape<Shapes...>>, std::shared_ptr<Entity>>;

  void operator()(std::shared_ptr<Entity> ent) {
    ActorType actor = (*actorBuilder)(ent);
    ReactorType reactor = (*reactorBuilder)(ent);
    std::shared_ptr<Shape<Shapes...>> shape = (*shapeBuilder)(ent);
    auto inator = std::make_shared<Inator>(shape, actor, reactor);

    inator->setIners(internalInerList);

    for(auto pair : inerLists) {
      auto ticket = pair.second->push_front(inator);
      ent->addTicket(pair.first, ticket);
    }

    for(auto pair : inatorLists) {
      auto ticket = pair.second->push_front(inator);
      ent->addTicket(pair.first, ticket);
    }

    for(auto pair : deactivatedInerLists) {
      auto ticket = pair.second->push_front(inator);
      ent->addTicket(pair.first, ticket);
      ent->setINACTIVE(pair.first);
    }

    for(auto pair : deactivatedInatorLists) {
      auto ticket = pair.second->push_front(inator);
      ent->addTicket(pair.first, ticket);
      ent->setINACTIVE(pair.first);
    }
  }

  void setActorBldr(std::shared_ptr<ActorTypeBldr> actorBuilder) {
    this->actorBuilder = actorBuilder;
  }

  void setReactorBldr(std::shared_ptr<ReactorTypeBldr> reactorBuilder) {
    this->reactorBuilder = reactorBuilder;
  }

  void setShapeBldr(std::shared_ptr<ShapeBldr> shapeBuilder) {
    this->shapeBuilder = shapeBuilder;
  }

  void addInerList(uint64_t idx, std::shared_ptr<InerList> list) {
    inerLists.push_front(std::pair<uint64_t, std::shared_ptr<TicketedForwardList<Iner>>>(idx, list));
  }

  void addInatorList(uint64_t idx, std::shared_ptr<InatorList> list) {
    inatorLists.push_front(std::pair<uint64_t, std::shared_ptr<TicketedForwardList<Inator>>>(idx, list));
  }

  void addDeactivatedInerList(uint64_t idx, std::shared_ptr<InerList> list) {
    deactivatedInerLists.push_front(std::pair<uint64_t, std::shared_ptr<TicketedForwardList<Iner>>>(idx, list));
  }

  void addDeactivatedInatorList(uint64_t idx, std::shared_ptr<InatorList> list) {
    deactivatedInatorLists.push_front(std::pair<uint64_t, std::shared_ptr<TicketedForwardList<Inator>>>(idx, list));
  }

  void setInternalInerList(std::shared_ptr<InerList> internalInerList) {
    this->internalInerList = internalInerList;
  }

private:
  std::shared_ptr<ActorTypeBldr> actorBuilder{};
  std::shared_ptr<ReactorTypeBldr> reactorBuilder{};
  std::shared_ptr<ShapeBldr> shapeBuilder{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<InerList>>> inerLists{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<InatorList>>> inatorLists{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<InerList>>> deactivatedInerLists{};
  std::forward_list<std::pair<uint64_t, std::shared_ptr<InatorList>>> deactivatedInatorLists{};
  std::shared_ptr<InerList> internalInerList{};
};

template<typename IData, typename Trait>
class _ActorBldr {
public:
  using TraitFunct = Funct<void, Reactor<IData, Trait>*, IData>;
  using SubBuild = Funct<std::shared_ptr<TraitFunct>, std::shared_ptr<Entity>>;

  _ActorBldr() : sb(std::make_shared<WrapperFunct<std::shared_ptr<TraitFunct>,std::shared_ptr<Entity>>>([](std::shared_ptr<Entity>){
                    return std::make_shared<WrapperFunct<void, Reactor<IData, Trait>*, IData>>(Actor<IData, Trait>::noAct);
                })) {

  }

  virtual ~_ActorBldr() = default;

  std::shared_ptr<TraitFunct> buildFunct(std::shared_ptr<Entity> ent) {
    return (*sb)(ent);
  }

  void setTraitBuildr(std::shared_ptr<SubBuild> sb) {
    this->sb = sb;
  }
private:
  std::shared_ptr<SubBuild> sb;
};

template<typename IData, typename Trait, typename ...Traits>
class ActorBldr : public Funct<Actor<IData, Trait, Traits...>, std::shared_ptr<Entity>>, public _ActorBldr<IData, Trait>, public _ActorBldr<IData, Traits>... {
public:
  virtual ~ActorBldr() = default;
  Actor<IData, Trait, Traits...> operator()(std::shared_ptr<Entity> ent) {
    Actor<IData, Trait, Traits...> actor;
    actor.setTrait(buildFunct<Trait>(ent));
    std::initializer_list<int>{(actor.setTrait(buildFunct<Traits>(ent)) , 0)... };
    return actor;
  }

  template<typename U>
  std::shared_ptr<Funct<void, Reactor<IData, U>*, IData>> buildFunct(std::shared_ptr<Entity> ent) {
    return this->_ActorBldr<IData, U>::buildFunct(ent);
  }

  template<typename U>
  void setTraitBuildr(std::shared_ptr<typename _ActorBldr<IData, U>::SubBuild> sb) {
    this->_ActorBldr<IData, U>::setTraitBuildr(sb);
  }
};

template<typename IData, typename Trait>
class ActorBldr<IData, Trait> : public Funct<Actor<IData, Trait>, std::shared_ptr<Entity>>, public _ActorBldr<IData, Trait> {
public:
  Actor<IData, Trait> operator() (std::shared_ptr<Entity> ent) {
    Actor<IData, Trait> actor;
    actor.setTrait(_ActorBldr<IData, Trait>::buildFunct(ent));
    return actor;
  }
};

template<typename IData, typename Trait>
class EnabledEmptyTraitBldr : public Funct<std::shared_ptr<Funct<void, Reactor<IData, Trait>*, IData>>, std::shared_ptr<Entity>> {
public:
  EnabledEmptyTraitBldr() : emptyTrait(std::make_shared<EnabledEmptyTrait<IData, Trait>>()) {}

  std::shared_ptr<Funct<void, Reactor<IData, Trait>*, IData>> operator()(std::shared_ptr<Entity>) {
    //return std::make_shared<EnabledEmptyTrait<IData, Trait>>();
    return emptyTrait;
  }
private:
  std::shared_ptr<Funct<void, Reactor<IData, Trait>*, IData>> emptyTrait;
};

// Use SimpleGenericFtry for this EnabledEmptyTraitBldr

// TODO: NO necesitamos heredar de ReactorBldr dado que no necesitamos usar su operator
// Podemos hacer una clase de utilidad que haga las funciones actuales de ReactorBldr (EJ: ReactorBldr_)
// Esas funciones son buildFunct y setReactionBuilder
// De esta forma ReactorBldr de uno hereda de ese una vez y ReactorBldr de muchos herada de esa para cada tipo pero NO del funct de cada tipo.

template<typename IData, typename Trait>
class _ReactorBldr {
public:
  using ReactFunct = Funct<void, IData, Trait>;
  using SubBuild = Funct<std::shared_ptr<ReactFunct>, std::shared_ptr<Entity>>;

  //_ReactorBldr() : sb(std::make_shared<WrapperFunct<std::shared_ptr<ReactFunct>, std::shared_ptr<Entity>>>(noReactionSubBuild)) {}
  _ReactorBldr() : sb() {}

  virtual ~_ReactorBldr() = default;

  std::shared_ptr<ReactFunct> buildFunct(std::shared_ptr<Entity> ent) {
    return (*sb)(ent);
  }

  void setReactionBuilder(std::shared_ptr<SubBuild> sb) {
    this->sb = sb;
  }

  static std::shared_ptr<ReactFunct> noReactionSubBuild(std::shared_ptr<Entity>) {
    return Reactor<IData, Trait>::noReaction;
  }
protected:
  std::shared_ptr<SubBuild> sb;
};

template<typename IData, typename Trait, typename ...Traits>
class ReactorBldr : public Funct<Reactor<IData, Trait, Traits...>, std::shared_ptr<Entity>>, public _ReactorBldr<IData, Trait>, public _ReactorBldr<IData, Traits>... {
public:
  Reactor<IData, Trait, Traits...> operator()(std::shared_ptr<Entity> ent) {
    Reactor<IData, Trait, Traits...> reactor;
    reactor.Reactor<IData, Trait>::setReaction(buildFunct<Trait>(ent));
    std::initializer_list<int>{(reactor.Reactor<IData, Traits>::setReaction(buildFunct<Traits>(ent)) , 0)... };
    return reactor;
  }

  template<typename U>
  std::shared_ptr<Funct<void, IData, U>> buildFunct(std::shared_ptr<Entity> ent) {
    return this->_ReactorBldr<IData, U>::buildFunct(ent);
  }

  template<typename U>
  void setReactionBuilder(std::shared_ptr<typename _ReactorBldr<IData, U>::SubBuild> sb) {
    this->_ReactorBldr<IData, U>::setReactionBuilder(sb);
  }
};

template<typename IData, typename Trait>
class ReactorBldr<IData, Trait> : public Funct<Reactor<IData, Trait>, std::shared_ptr<Entity>>, public _ReactorBldr<IData, Trait> {
public:
  using ReactFunct = Funct<void, IData, Trait>;
  using SubBuild = Funct<std::shared_ptr<ReactFunct>, std::shared_ptr<Entity>>;

  Reactor<IData, Trait> operator() (std::shared_ptr<Entity> ent) {
    Reactor<IData, Trait> reactor;
    //reactor.setReaction((*sb)(ent));
    reactor.setReaction(_ReactorBldr<IData, Trait>::buildFunct(ent));
    return reactor;
  }

//   std::shared_ptr<ReactFunct> buildFunct(std::shared_ptr<Entity> ent) {
//     return (*sb)(ent);
//   }

//   void setReactionBuilder(std::shared_ptr<SubBuild> sb) {
//     this->sb = sb;
//   }
// private:
//   static std::shared_ptr<ReactFunct> noReactionSubBuild(std::shared_ptr<Entity>) {
//     return Reactor<IData, Trait>::noReaction;
//   }
//   std::shared_ptr<SubBuild> sb;
};

template<typename S, typename ...Shapes>
class ShapeBldr : public Funct<std::shared_ptr<Shape<Shapes...>>, std::shared_ptr<Entity>> {
public:
  using SubBuild = Funct<std::shared_ptr<SAvatar<S>>, std::shared_ptr<Entity>>;

  ShapeBldr() : sb(std::make_shared<WrapperFunct<std::shared_ptr<SAvatar<S>>, std::shared_ptr<Entity>>>([](std::shared_ptr<Entity>){assert(false); return nullptr;})) {}
  ~ShapeBldr() = default;

  std::shared_ptr<Shape<Shapes...>> operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<SAvatar<S>> avt = (*sb)(ent);
    return std::make_shared<AvtShape<S, Shapes...>>(avt);
  }

  void setBuildFunct(std::shared_ptr<SubBuild> sb) {
    this->sb = sb;
  }

private:
  std::shared_ptr<SubBuild> sb;
};

template<typename IData, typename ...Traits>
class ActorBldrFtry : public Factory {
public:
  ActorBldrFtry(std::initializer_list<std::string> names) :traitCfgNames(names)  {}

  template<typename U>
  void addTraitBuilder(std::string traitCfgName, nlohmann::json cfg, std::shared_ptr<ActorBldr<IData, Traits...>> actorBldr, bool& failed) {
    using namespace std::string_literals;
    auto& builderStore = RsrcStore<typename _ActorBldr<IData, U>::SubBuild>::getInstance();
    if(failed) {return;}
    if(!cfg.contains(traitCfgName)) {
      return;
    }
    if(!cfg[traitCfgName].is_string()) {
      SysError::setError("ActorBldrFtry config for "s + traitCfgName + " must be an string"s);
      failed = true;
      return;
    }
    std::string builderName = cfg[traitCfgName].get<std::string>();
    if(!builderName.compare("ENABLED"s)) {
        actorBldr->_ActorBldr<IData, U>::setTraitBuildr(std::make_shared<EnabledEmptyTraitBldr<IData, U>>());
    } else {
      if(!builderStore.contains(zbe::factories::functionName_ + builderName)) {
        SysError::setError("ActorBldrFtry config for "s + traitCfgName + " is not a builder name");
        failed = true;
        return;
      }
      auto bldr = builderStore.get(zbe::factories::functionName_ + builderName);
      actorBldr->_ActorBldr<IData, U>::setTraitBuildr(bldr);
    }
  }

  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<ActorBldr<IData, Traits...>> ab = std::make_shared<ActorBldr<IData, Traits...>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, ab);
    specificRsrc.insert("ActorBldr."s + name, ab);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("ActorBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto ab = specificRsrc.get("ActorBldr."s + name);
    auto j = *cfg;
    int i = 0;
    bool failed = false;
    std::initializer_list<int>({(addTraitBuilder<Traits>(traitCfgNames[i++], j, ab, failed), 0)...});
  }

private:
  std::vector<std::string> traitCfgNames;
  using ActorType = Actor<IData, Traits...>;
  using FunctionType= Funct<ActorType, std::shared_ptr<Entity>>;
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<ActorBldr<IData, Traits...>>& specificRsrc = RsrcStore<ActorBldr<IData, Traits...>>::getInstance();
};

template<typename IData, typename ...Traits>
class ReactorBldrFtry : public Factory {
public:
  template<typename U>
  void addReactionBuilder(std::string traitCfgName, nlohmann::json cfg, std::shared_ptr<ReactorBldr<IData, Traits...>> reactorBldr, bool& failed) {
    using namespace std::string_literals;
    auto& builderStore = RsrcStore<typename ReactorBldr<IData, U>::SubBuild>::getInstance();
    if(failed) {
      return;
    }
    if(!cfg.contains(traitCfgName)) {
      reactorBldr->_ReactorBldr<IData, U>::setReactionBuilder(std::make_shared<WrapperFunct<std::shared_ptr<Funct<void, IData, U>>, std::shared_ptr<Entity>>>(_ReactorBldr<IData, U>::noReactionSubBuild));
      return;
    }
    if(!cfg[traitCfgName].is_string()) {
      SysError::setError("ReactorBldrFtry config for "s + traitCfgName + " must be an string but is " + cfg[traitCfgName].dump());
      failed = true;
      return;
    }
    std::string builderName = cfg[traitCfgName].get<std::string>();
    auto storedName = zbe::factories::functionName + zbe::factories::separator + builderName;
    if(!builderStore.contains(storedName )) {
      SysError::setError("ReactorBldrFtry config for "s + traitCfgName + " is not a builder name");
      failed = true;
      return;
    }
    auto bldr = builderStore.get(storedName );
    reactorBldr->_ReactorBldr<IData, U>::setReactionBuilder(bldr);
  }

  ReactorBldrFtry(std::initializer_list<std::string> names) : traitCfgNames(names)  {}

  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<ReactorBldr<IData, Traits...>> ab = std::make_shared<ReactorBldr<IData, Traits...>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, ab);
    specificRsrc.insert("ReactorBldr."s + name, ab);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("ReactorBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto ab = specificRsrc.get("ReactorBldr."s + name);
    auto j = *cfg;
    int i = 0;
    bool failed = false;
    std::initializer_list<int>({(addReactionBuilder<Traits>(traitCfgNames[i++], j, ab, failed), 0)...});
  }

private:
  std::vector<std::string> traitCfgNames;
  using ReactorType = Reactor<IData, Traits...>;
  using FunctionType = Funct<ReactorType, std::shared_ptr<Entity>>;
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<ReactorBldr<IData, Traits...>>& specificRsrc = RsrcStore<ReactorBldr<IData, Traits...>>::getInstance();
};

template<typename S, typename ...Shapes>
class ShapeBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<ShapeBldr<S, Shapes...>> sb = std::make_shared<ShapeBldr<S, Shapes...>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, sb);
    specificRsrc.insert("ShapeBldr."s + name, sb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("ShapeBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto sb = specificRsrc.get("ShapeBldr."s + name);
    auto j = *cfg;
    if(auto shapeBuilderFunct = JSONFactory::loadParamCfgStoreP<typename ShapeBldr<S, Shapes...>::SubBuild>(shapeBuilderFunctStore, j, zbe::factories::functionName, "shapetype", "ShapeBldrFtry"s)) {
      sb->setBuildFunct(*shapeBuilderFunct);
      return;
    } else {
      SysError::setError("ShapeBldrFtry config for shapetype is not a shape builder function name."s);
      return;
    }
  }
private:
  using ShapeType = Shape<Shapes...>;
  using FunctionType = Funct<std::shared_ptr<ShapeType>, std::shared_ptr<Entity>>;
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<typename ShapeBldr<S, Shapes...>::SubBuild>& shapeBuilderFunctStore = RsrcStore<typename ShapeBldr<S, Shapes...>::SubBuild>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<ShapeBldr<S, Shapes...>>& specificRsrc = RsrcStore<ShapeBldr<S, Shapes...>>::getInstance();
};

class EntityBldrFtry : public Factory {
public:

  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<EntityBldr> eb = std::make_shared<EntityBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, eb);
    specificRsrc.insert("EntityBldr."s + name, eb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("EntityBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto eb = specificRsrc.get("EntityBldr."s + name);
    auto j = *cfg;

    if (j["builders"].is_array()) {
      auto builders = j["builders"];
      for(auto it : builders) {
        auto name = it.get<std::string>();
        auto storedName = zbe::factories::functionName + zbe::factories::separator + name;
        if(!extraBldrStore.contains(storedName)) {
          SysError::setError("EntityBldrFtry builders config " + name + " (" + storedName + "). is not an adecuate builder name."s);
          return;
        }
        eb->addBldr(extraBldrStore.get(storedName));
      }
    } else if(j.contains("builders")) {
      SysError::setError("EntityBldrFtry config for builders, if present, must be a array."s);
    }

    auto contextTime = JSONFactory::loadParamCfgStoreP<ContextTime>(cTimeRsrc, j, zbe::factories::contextimeName, "contextTime"s, "EntityBldrFtry"s);
    if(!contextTime) {
      SysError::setError("EntityBldrFtry config for contextTime is invalid"s);
      return;
    }
    eb->setContextTime(*contextTime);
  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<void>>& mainRsrc = RsrcStore<Funct<void>>::getInstance();
  RsrcStore<EntityBldr>& specificRsrc = RsrcStore<EntityBldr>::getInstance();
  RsrcStore<Funct<void, std::shared_ptr<Entity>>>& extraBldrStore = RsrcStore<Funct<void, std::shared_ptr<Entity>>>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();

};

class EntitySetterFtry : virtual public Factory {
public:

  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<EntitySetter> e = std::make_shared<EntitySetter>();
    mainRsrc.insert(factories::functionName + factories::separator  + name, e);
    specificRsrc.insert("EntitySetter."s + name, e);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);
    if(cfg) {
      auto j = *cfg;
      auto es = specificRsrc.get("EntitySetter."s + name);
      if (j.find("double") != j.end())  { parse(j["double"],  valueDRsrc, doubleStore, es); }
      if (j.find("float") != j.end())   { parse(j["float"],   valueFRsrc, floatStore, es); }
      if (j.find("uint") != j.end())    { parse(j["uint"],    valueURsrc, uintStore, es); }
      if (j.find("int") != j.end())     { parse(j["int"],     valueIRsrc, intStore, es); }
      if (j.find("bool") != j.end())    { parse(j["bool"],    valueBRsrc, boolStore, es); }
      if (j.find("V2D") != j.end())     { parseV2D(j["V2D"],              es); }
      if (j.find("V3D") != j.end())     { parseV3D(j["V3D"],              es); }
      if (j.find("String") != j.end())  { parse(j["String"],  valueSRsrc, stringStore, es); }
      if (j.find("VString") != j.end()) { parseVString(j["VString"],      es); }
    } else {
      SysError::setError("EntitySetter config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();

  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  RsrcDictionary<double>& doubleStore = RsrcDictionary<double>::getInstance();
  RsrcDictionary<float>& floatStore = RsrcDictionary<float>::getInstance();
  RsrcDictionary<bool>& boolStore = RsrcDictionary<bool>::getInstance();
  RsrcDictionary<std::string>& stringStore = RsrcDictionary<std::string>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();

  RsrcStore<Funct<void, std::shared_ptr<Entity>>>& mainRsrc = RsrcStore<Funct<void, std::shared_ptr<Entity>>>::getInstance();
  RsrcStore<EntitySetter>& specificRsrc = RsrcStore<EntitySetter>::getInstance();

  RsrcStore<Funct<void, std::shared_ptr<Entity>>>& extraBldrStore = RsrcStore<Funct<void, std::shared_ptr<Entity>>>::getInstance();

  RsrcStore<Value<double> > &valueDRsrc = RsrcStore<Value<double> >::getInstance();
  RsrcStore<Value<float> > &valueFRsrc = RsrcStore<Value<float> >::getInstance();
  RsrcStore<Value<uint64_t> > &valueURsrc = RsrcStore<Value<uint64_t> >::getInstance();
  RsrcStore<Value<int64_t> > &valueIRsrc = RsrcStore<Value<int64_t> >::getInstance();
  RsrcStore<Value<bool> > &valueBRsrc = RsrcStore<Value<bool> >::getInstance();
  RsrcStore<Value<Vector2D> > &valueV2Rsrc = RsrcStore<Value<Vector2D> >::getInstance();
  RsrcStore<Value<Vector3D> > &valueV3Rsrc = RsrcStore<Value<Vector3D> >::getInstance();
  RsrcStore<Value<std::string> > &valueSRsrc = RsrcStore<Value<std::string> >::getInstance();
  RsrcStore<Value<std::vector<std::string> > > &valueVSRsrc = RsrcStore<Value<std::vector<std::string> > >::getInstance();
  RsrcDictionary<Vector2D> &literalStoreV2D = RsrcDictionary<Vector2D>::getInstance();
  RsrcDictionary<Vector3D> &literalStoreV3D = RsrcDictionary<Vector3D>::getInstance();

  template <typename T>
  T parseArrayElement(nlohmann::json value, RsrcDictionary<T> &literalStore) {
    using namespace std::string_literals;
    if (value.is_string()) {
        //auto s = value.get<std::string>();
        //auto sp = valueRsrc.get(s);
        //auto sr = sp->get();
        //return sr;
      return literalStore.get(value.get<std::string>());
    } else if(value.is_array() && (value.size() == 1)
           && ((std::is_floating_point<T>::value && value.at(0).is_number_float())
              ||(std::is_integral<T>::value && value.at(0).is_number_integer())
              ||(std::is_same<T, bool>::value && value.at(0).is_boolean())
              ||(std::is_same<T, std::string>::value && value.at(0).is_string()))) {
      return value.at(0).get<T>();
    } else if((std::is_floating_point<T>::value && value.is_number_float())
           ||(std::is_integral<T>::value && value.is_number_integer())
           ||(std::is_same<T, bool>::value && value.is_boolean())) {
      return value.get<T>();
    } else {
        SysError::setError("EntitySetter parseArrayElement error: "s + value.get<std::string>() + " has invalid type."s);
        return T();
    }
  }

  template <typename T>
  inline void parse(nlohmann::json cfg, RsrcStore<Value<T> > &valueRsrc, RsrcDictionary<T> &literalStore, std::shared_ptr<EntitySetter> es) {
    using namespace std::string_literals;
    for (auto item : cfg.items()) {
      auto id = uintStore.get(item.key());
      //es->set<T>(id, parseSingleValue(item.value(), valueRsrc, literalStore));
      auto cfgValue = item.value();
      if (cfgValue.is_string()) {
        es->setSharedValue<T>(id, valueRsrc.get(cfgValue.get<std::string>()));
      } else if(cfgValue.is_array() && (cfgValue.size() == 1)
           &&(std::is_same_v<T, std::string> == false) && (cfgValue.at(0).is_string())) {
        es->setNewValue<T>(id, literalStore.get(cfgValue.at(0).get<std::string>()));
      } else if(cfgValue.is_array() && (cfgValue.size() == 1)
        && ((std::is_floating_point<T>::value && cfgValue.at(0).is_number_float())
           ||(std::is_integral<T>::value && cfgValue.at(0).is_number_integer())
           ||(std::is_same<T, bool>::value && cfgValue.at(0).is_boolean())
           ||(std::is_same<T, std::string>::value && cfgValue.at(0).is_string()))){
        es->setNewValue<T>(id, cfgValue.at(0).get<T>());
      } else if((std::is_floating_point<T>::value && cfgValue.is_number_float())
           ||(std::is_integral<T>::value && cfgValue.is_number_integer())
           ||(std::is_same<T, bool>::value && cfgValue.is_boolean())) {
        es->setNewValue<T>(id, cfgValue.get<T>());
      } else {
        SysError::setError("EntitySetter parseValue error: "s + item.key() + " is invalid."s);
      }
    }
  }

  inline void parseV3D(nlohmann::json cfg, std::shared_ptr<EntitySetter> es) {
    for (auto item : cfg.items()) {
      auto cfgValue = item.value();
      auto id = uintStore.get(item.key());
      std::shared_ptr<zbe::Value<Vector3D> > val = std::make_shared<zbe::SimpleValue<Vector3D> >();
      if (cfgValue.is_string()) {
        es->setSharedValue<Vector3D>(id, valueV3Rsrc.get(cfgValue.get<std::string>()));
      } else if(cfgValue.is_array() && (cfgValue.size() == 1)
             && (cfgValue.at(0).is_string())) {
        es->setNewValue<Vector3D>(id, literalStoreV3D.get(cfgValue.at(0).get<std::string>()));
      } else if (cfgValue.is_array() && (cfgValue.size() == 3)) {
        auto c = 0;
        Vector3D val;
        for (auto item : cfgValue.items()) {
          val[c++] = parseArrayElement(item.value(), doubleStore);
        }
        es->setNewValue<Vector3D>(id, val);
      }
    }
  }

  inline void parseV2D(nlohmann::json cfg, std::shared_ptr<EntitySetter> es) {
    for (auto item : cfg.items()) {
      auto cfgValue = item.value();
      auto id = uintStore.get(item.key());
      std::shared_ptr<zbe::Value<Vector2D> > val = std::make_shared<zbe::SimpleValue<Vector2D> >();
      if (cfgValue.is_string()) {
        es->setSharedValue<Vector2D>(id, valueV2Rsrc.get(cfgValue.get<std::string>()));
      } else if(cfgValue.is_array() && (cfgValue.size() == 1)
             && (cfgValue.at(0).is_string())) {
        es->setNewValue<Vector2D>(id, literalStoreV2D.get(cfgValue.at(0).get<std::string>()));
      } else if (cfgValue.is_array() && (cfgValue.size() == 2)) {
        auto c = 0;
        Vector2D val;
        for (auto item : cfgValue.items()) {
          val[c++] = parseArrayElement(item.value(), doubleStore);
        }
        es->setNewValue<Vector2D>(id, val);
      }
    }
  }

  inline void parseVString(nlohmann::json cfg, std::shared_ptr<EntitySetter> es) {
    for (auto item : cfg.items()) {
      auto cfgValue = item.value();
      auto id = uintStore.get(item.key());
      if (cfgValue.is_string()) {
        es->setSharedValue<std::vector<std::string>>(id, valueVSRsrc.get(cfgValue.get<std::string>()));
      } else if (cfgValue.is_array()) {
        std::vector<std::string> val;
        for (auto item : cfgValue.items()) {
          val.emplace_back(parseArrayElement<std::string>(item.value(), stringStore));
        }
        es->setNewValue<std::vector<std::string>>(id, val);
      }
    }
  }
};

// template<typename VT, typename T, typename ...Ts>
// std::shared_ptr<Funct<std::shared_ptr<Value<VT>>, std::shared_ptr<MAvatar<T, Ts...>>>> buildValueBldr(nlohmann::json cfg) {
//   if(cfg["copy"] es numero) {
//       //return BuildCopyValueBldr<VT, T, TS...>(cfg["copy"]);
//   }
// }

// Necesitamos llamar a los get del avatar según un indice en tiempo de ejecución y no de compilación como tenemos ahora.
// Ñapa:
// Operador coma simulando un cadena de "or" con un valor que se arrastra a la siguiente llamada y
// esta solo se ejecuta si la anterior no ha encontrado nada....
// O algo mejor. por dió que se nos ocurra algo mejor.
//
// Si no encontramos una forma genérica lo hacemos manualmente. No nos engorilemos con esto.

template<typename VT, unsigned n, typename T, typename ...Ts>
struct BuildCopyValueBldr : public Funct<std::shared_ptr<Value<VT>>, std::shared_ptr<MAvatar<T, Ts...>>> {
  std::shared_ptr<Value<VT>> operator()(std::shared_ptr<MAvatar<T, Ts...>> avt) {
    auto val = AvtUtil::get<n, VT>(avt)->get();
    return std::make_shared<SimpleValue<VT>>(val);
  }
};

template<unsigned n, typename T, typename ...Ts>
class BuildCopyVectModuleBldr : public Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<MAvatar<T, Ts...>>> {
public:
  std::shared_ptr<Value<Vector3D>> operator()(std::shared_ptr<MAvatar<T, Ts...>> avt) {
    auto val = AvtUtil::get<n, Vector3D>(avt)->get();
    return std::make_shared<SimpleValue<Vector3D>>(val.normalize()*module);
  }
  void setVectorModule(double module) {
    this->module = module;
  }
private:
  double module{};
};


void combineRotations(glm::vec3 originDirection, glm::vec3 originUp, glm::vec3 destinationDirection, glm::vec3 destinationUp, glm::vec3& rotationAxis, double& rotationAngle);

template<typename T, typename ...Ts>
struct BuildUpDirToOriBldr : public Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<MAvatar<T, Ts...>>> {
  std::shared_ptr<Value<Vector3D>> operator()(std::shared_ptr<MAvatar<T, Ts...>> avt) {
    // ["upwardsIdx", "orientationIdx", "positionIdx"],
    Vector3D ori = AvtUtil::get<2, Vector3D>(avt)->get();
    Vector3D upwards = AvtUtil::get<3, Vector3D>(avt)->get();

    glm::vec3 gori{ori.x, ori.y, ori.z};
    glm::vec3 gupwards{upwards.x, upwards.y, upwards.z};

    glm::vec3 rotationAxis;
    double rotationAngle;
    combineRotations(baseOri, baseUpw, gupwards, gori, rotationAxis, rotationAngle);
    Vector3D out{rotationAxis.x, rotationAxis.y, rotationAxis.z};
    return std::make_shared<SimpleValue<Vector3D>>(out);
  }

  void setBaseOrientation(Vector3D baseOri) {
    this->baseOri = {baseOri.x, baseOri.y, baseOri.z};
  }

  void setBaseUpwards(Vector3D baseUpw) {
    this->baseUpw = {baseUpw.x, baseUpw.y, baseUpw.z};
  }

private:
  glm::vec3 baseOri{0.0, 1.0, 0.0};
  glm::vec3 baseUpw{1.0, 0.0, 0.0};
};

template<typename T, typename ...Ts>
struct BuildUpDirToRadsBldr : public Funct<std::shared_ptr<Value<double>>, std::shared_ptr<MAvatar<T, Ts...>>> {
  std::shared_ptr<Value<double>> operator()(std::shared_ptr<MAvatar<T, Ts...>> avt) {
    // ["upwardsIdx", "orientationIdx", "positionIdx"],
    Vector3D ori = AvtUtil::get<2, Vector3D>(avt)->get();
    Vector3D upwards = AvtUtil::get<3, Vector3D>(avt)->get();
    printf("oirentacion %lf, %lf, %lf\n", ori.x, ori.y, ori.z);fflush(stdout);
    printf("upwards %lf, %lf, %lf\n", upwards.x, upwards.y, upwards.z);fflush(stdout);

    glm::vec3 gori{ori.x, ori.y, ori.z};
    glm::vec3 gupwards{upwards.x, upwards.y, upwards.z};

    glm::vec3 rotationAxis;
    double rotationAngle;
    combineRotations(baseOri, baseUpw, gupwards, gori, rotationAxis, rotationAngle);
    printf("rotationAxis %lf, %lf, %lf\n", rotationAxis.x, rotationAxis.y, rotationAxis.z);fflush(stdout);
    printf("rotationAngle %lf\n", rotationAngle);fflush(stdout);
    return std::make_shared<SimpleValue<double>>(rotationAngle);
  }

  void setBaseOrientation(Vector3D baseOri) {
    this->baseOri = {baseOri.x, baseOri.y, baseOri.z};
  }

  void setBaseUpwards(Vector3D baseUpw) {
    this->baseUpw = {baseUpw.x, baseUpw.y, baseUpw.z};
  }

private:
  glm::vec3 baseOri{0.0, 1.0, 0.0};
  glm::vec3 baseUpw{1.0, 0.0, 0.0};
};

template<typename T, typename ...Ts>
class BuildUpDirToOriBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<BuildUpDirToOriBldr<T, Ts...>> budtob = std::make_shared<BuildUpDirToOriBldr<T, Ts...>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, budtob);
    specificRsrc.insert("BuildUpDirToOriBldr."s + name, budtob);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("BuildUpDirToOriBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto budtob = specificRsrc.get("BuildUpDirToOriBldr."s + name);
    auto j = *cfg;

    if(j.contains("baseupwards")) { 
      budtob->setBaseUpwards(JSONFactory::parseV3DFromCfg(j["baseupwards"], "baseupwards"s, "BuildUpDirToOriBldrFtry"s));
    }

    if(j.contains("baseorientation")) {
      budtob->setBaseOrientation(JSONFactory::parseV3DFromCfg(j["baseorientation"], "baseorientation"s, "BuildUpDirToOriBldrFtry"s));
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<MAvatar<T, Ts...>>>>& mainRsrc = RsrcStore<Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<MAvatar<T, Ts...>>>>::getInstance();
  RsrcStore<BuildUpDirToOriBldr<T, Ts...>>& specificRsrc = RsrcStore<BuildUpDirToOriBldr<T, Ts...>>::getInstance();
  RsrcDictionary<double>& doubleDict = RsrcDictionary<double>::getInstance();
};

template<typename T, typename ...Ts>
class BuildUpDirToRadsBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<BuildUpDirToRadsBldr<T, Ts...>> budtrb = std::make_shared<BuildUpDirToRadsBldr<T, Ts...>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, budtrb);
    specificRsrc.insert("BuildUpDirToRadsBldr."s + name, budtrb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("BuildUpDirToRadsBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto budtrb = specificRsrc.get("BuildUpDirToRadsBldr."s + name);
    auto j = *cfg;

    if(j.contains("baseupwards")) {
      budtrb->setBaseUpwards(JSONFactory::parseV3DFromCfg(j["baseupwards"], "baseupwards"s, "BuildUpDirToRadsBldrFtry"s));
    }

    if(j.contains("baseorientation")) {
      budtrb->setBaseOrientation(JSONFactory::parseV3DFromCfg(j["baseorientation"], "baseorientation"s, "BuildUpDirToRadsBldrFtry"s));
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<std::shared_ptr<Value<double>>, std::shared_ptr<MAvatar<T, Ts...>>>>& mainRsrc = RsrcStore<Funct<std::shared_ptr<Value<double>>, std::shared_ptr<MAvatar<T, Ts...>>>>::getInstance();
  RsrcStore<BuildUpDirToRadsBldr<T, Ts...>>& specificRsrc = RsrcStore<BuildUpDirToRadsBldr<T, Ts...>>::getInstance();
  RsrcDictionary<double>& doubleDict = RsrcDictionary<double>::getInstance();
};

template<unsigned n, typename T, typename ...Ts>
class BuildCopyVectModuleBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<BuildCopyVectModuleBldr<n, T, Ts...>> bcvmb = std::make_shared<BuildCopyVectModuleBldr<n, T, Ts...>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, bcvmb);
    specificRsrc.insert("BuildCopyVectModuleBldr."s + name, bcvmb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("BehaviorEntityBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto bcvmb = specificRsrc.get("BuildCopyVectModuleBldr."s + name);
    auto j = *cfg;
    auto module = JSONFactory::loadParamCfgDict<double>(doubleDict, j, "module"s, "BuildCopyVectModuleBldrFtry"s);
    if(!module) {
      SysError::setError("BuildCopyVectModuleBldrFtry config for module is invalid"s);
      return;
    }
    bcvmb->setVectorModule(*module);
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<MAvatar<T, Ts...>>>>& mainRsrc = RsrcStore<Funct<std::shared_ptr<Value<Vector3D>>, std::shared_ptr<MAvatar<T, Ts...>>>>::getInstance();
  RsrcStore<BuildCopyVectModuleBldr<n, T, Ts...>>& specificRsrc = RsrcStore<BuildCopyVectModuleBldr<n, T, Ts...>>::getInstance();
  RsrcDictionary<double>& doubleDict = RsrcDictionary<double>::getInstance();
};


template<typename T, typename ...Ts>
class BehaviorEntityBldrFtry : public Factory {
public:

  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<BehaviorEntityBldr<T, Ts...>> eb = std::make_shared<BehaviorEntityBldr<T, Ts...>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, eb);
    specificRsrc.insert("BehaviorEntityBldr."s + name, eb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("BehaviorEntityBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto eb = specificRsrc.get("BehaviorEntityBldr."s + name);
    auto j = *cfg;

    if(!addList2Bldr<double>(j, "double"s, eb)
    || !addList2Bldr<float>(j, "float"s, eb)
    || !addList2Bldr<uint64_t>(j, "uint64_t"s, eb)
    || !addList2Bldr<int64_t>(j, "int64_t"s, eb)
    || !addList2Bldr<bool>(j, "bool"s, eb)
    || !addList2Bldr<Vector3D>(j, "Vector3D"s, eb)
    || !addList2Bldr<Vector2D>(j, "Vector2D"s, eb)
    || !addList2Bldr<std::string>(j, "String"s, eb)
    || !addList2Bldr<std::vector<std::string>>(j, "VString"s, eb)) {
      return;
    }
    auto contextTime = JSONFactory::loadParamCfgStoreP<ContextTime>(cTimeRsrc, j, zbe::factories::contextimeName, "contextTime"s, "BehaviorEntityBldrFtry"s);
    if(!contextTime) {
      SysError::setError("BehaviorEntityBldrFtry config for contextTime is invalid"s);
      return;
    }
    eb->setContextTime(*contextTime);

    if (j["builders"].is_array()) {
      auto builders = j["builders"];
      for(auto it : builders) {
        auto name = it.get<std::string>();
        auto storedName = zbe::factories::functionName + zbe::factories::separator + name;
        if(!extraBldrStore.contains(storedName)) {
          SysError::setError("BehaviorEntityBldrFtry builders config " + name + " (" + storedName + "). is not an adecuate builder name."s);
          return;
        }
        eb->addBldr(extraBldrStore.get(storedName));
      }
    } else if(j.contains("builders")) {
      SysError::setError("BehaviorEntityBldrFtry config for builders, if present, must be a array."s);
    }
  }

private:

  template<typename VT>
  bool addList2Bldr(nlohmann::json& j, std::string type, std::shared_ptr<BehaviorEntityBldr<T, Ts...>> eb) {
    using namespace std::string_literals;
    if(!j.contains(type)) {
      return true;
    }
    if (j[type].is_object()) {
      auto dcfg = j[type];
      for (auto item : dcfg.items()) {
        auto key = item.key();
        auto idx = JSONFactory::loadParamStrDict<uint64_t>(uintDict, key, "BehaviorEntityBldrFtry"s);
        if(!idx) {
          SysError::setError("BehaviorEntityBldrFtry config for " + type + " " + key +" is not an uint name."s);
          return false;
        }
        // auto valueCfg = item.value();
        // if(auto valueCfg.is_object()) {
        //   auto valueBuilder = buildValueBldr<VT>(valueCfg);
        //   eb->addValueBldr({*idx, valueBuilder});
        // } else {
          auto valueBuilder = JSONFactory::loadParamCfgStoreP<ValueBldr<VT>>(RsrcStore<ValueBldr<VT>>::getInstance(), dcfg, zbe::factories::functionName, key, "BehaviorEntityBldrFtry"s);
          if(valueBuilder) {
            eb->addValueBldr({*idx, *valueBuilder});
          } else {
            SysError::setError("BehaviorEntityBldrFtry config for " + type + " contains invalida values name."s);
            return false;
          }
        // }
      }
    } else {
      SysError::setError("BehaviorEntityBldrFtry config for " + type + ", if present, must be an object."s);
      return false;
    }
    return true;
  }

  template<typename VT>
  using ValueBldr = Funct<std::shared_ptr<Value<VT>>, std::shared_ptr<MAvatar<T, Ts...>>>;
  template<typename VT>
  using PairList = std::forward_list<std::pair<uint64_t, ValueBldr<VT>>>;
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<void, std::shared_ptr<MAvatar<T, Ts...>>>>& mainRsrc = RsrcStore<Funct<void, std::shared_ptr<MAvatar<T, Ts...>>>>::getInstance();
  RsrcStore<BehaviorEntityBldr<T, Ts...>>& specificRsrc = RsrcStore<BehaviorEntityBldr<T, Ts...>>::getInstance();

  RsrcStore<Funct<void, std::shared_ptr<Entity>>>& extraBldrStore = RsrcStore<Funct<void, std::shared_ptr<Entity>>>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();

};

template<typename T>
class BehaviorEntityBldrFtry<T> : public Factory {
public:

  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<BehaviorEntityBldr<T>> eb = std::make_shared<BehaviorEntityBldr<T>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, eb);
    specificRsrc.insert("BehaviorEntityBldr."s + name, eb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("BehaviorEntityBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto eb = specificRsrc.get("BehaviorEntityBldr."s + name);
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
        auto storedName = zbe::factories::functionName + zbe::factories::separator + name;
        if(!extraBldrStore.contains(storedName)) {
          SysError::setError("BehaviorEntityBldrFtry builders config " + name + " (" + storedName + "). is not an adecuate builder name."s);
          return;
        }
        eb->addBldr(extraBldrStore.get(storedName));
      }
    } else if(j.contains("builders")) {
      SysError::setError("BehaviorEntityBldrFtry config for builders, if present, must be a array."s);
    }
  }

private:

  template<typename VT>
  bool addList2Bldr(nlohmann::json& j, std::string type, std::shared_ptr<BehaviorEntityBldr<VT>> eb) {
    using namespace std::string_literals;
    if (j[type].is_object()) {
      auto dcfg = j[type];
      for (auto item : dcfg.items()) {
        auto key = item.key();
        if(auto valueBuilder = JSONFactory::loadParamCfgStoreP<ValueBldr<double>>(doubleBldrStore, dcfg, zbe::factories::functionName, key, "BehaviorEntityBldrFtry"s)) {
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

  template<typename VT>
  using ValueBldr = Funct<std::shared_ptr<Value<VT>>, std::shared_ptr<SAvatar<T>>>;
  template<typename VT>
  using PairList = std::forward_list<std::pair<uint64_t, ValueBldr<VT>>>;
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<void, std::shared_ptr<SAvatar<T>>>>& mainRsrc = RsrcStore<Funct<void, std::shared_ptr<SAvatar<T>>>>::getInstance();
  RsrcStore<BehaviorEntityBldr<T>>& specificRsrc = RsrcStore<BehaviorEntityBldr<T>>::getInstance();

  RsrcStore<ValueBldr<double>>& doubleBldrStore = RsrcStore<ValueBldr<double>>::getInstance();
  RsrcStore<ValueBldr<float>>& floatBldrStore = RsrcStore<ValueBldr<float>>::getInstance();
  RsrcStore<ValueBldr<uint64_t>>& uintBldrStore = RsrcStore<ValueBldr<uint64_t>>::getInstance();
  RsrcStore<ValueBldr<int64_t>>& intBldrStore = RsrcStore<ValueBldr<int64_t>>::getInstance();
  RsrcStore<ValueBldr<bool>>& boolBldrStore = RsrcStore<ValueBldr<bool>>::getInstance();
  RsrcStore<ValueBldr<Vector3D>>& v3DBldrStore = RsrcStore<ValueBldr<Vector3D>>::getInstance();
  RsrcStore<ValueBldr<Vector2D>>& v2DBldrStore = RsrcStore<ValueBldr<Vector2D>>::getInstance();
  RsrcStore<ValueBldr<std::string>>& stringBldrStore = RsrcStore<ValueBldr<std::string>>::getInstance();
  RsrcStore<ValueBldr<std::vector<std::string>>>& vStringBldrStore = RsrcStore<ValueBldr<std::vector<std::string>>>::getInstance();

  RsrcStore<Funct<void, std::shared_ptr<Entity>>>& extraBldrStore = RsrcStore<Funct<void, std::shared_ptr<Entity>>>::getInstance();

  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();

  //std::deque<Funct<void, std::shared_ptr<Entity>>> builders;

};

template<typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionatorBldrFtry : public Factory {
public:
  using InatorBldr = InteractionatorBldr<IData, ActorType, ReactorType, Shapes...>;
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<InatorBldr> inatorb = std::make_shared<InatorBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, inatorb);
    specificRsrc.insert("InteractionatorBldr."s + name, inatorb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("InteractionatorBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto inatorb = specificRsrc.get("InteractionatorBldr."s + name);
    auto j = *cfg;
    auto actorBuilder = JSONFactory::loadParamCfgStoreP<typename InatorBldr::ActorTypeBldr>(actorBldrRsrc, j, zbe::factories::functionName, "actorbuilder"s, "InteractionatorBldrFtry"s);
    if(!actorBuilder) {
      SysError::setError("InteractionatorBldrFtry config for actorbuilder is invalid"s);
      return;
    }
    auto reactorBuilder = JSONFactory::loadParamCfgStoreP<typename InatorBldr::ReactorTypeBldr>(reactorBldrRsrc, j, zbe::factories::functionName, "reactorbuilder"s, "InteractionatorBldrFtry"s);
    if(!reactorBuilder) {
      SysError::setError("InteractionatorBldrFtry config for reactorbuilder is invalid"s);
      return;
    }

    auto shapeBuilder = JSONFactory::loadParamCfgStoreP<typename InatorBldr::ShapeBldr>(shapeBldrRsrc, j, zbe::factories::functionName, "shapebuilder"s, "InteractionatorBldrFtry"s);
    if(!shapeBuilder) {
      SysError::setError("InteractionatorBldrFtry config for shapebuilder is invalid"s);
      return;
    }
    auto list = JSONFactory::loadParamCfgStoreP<typename InatorBldr::InerList>(listInerRsrc, j, zbe::factories::listName, "interactioners"s, "InteractionatorBldrFtry"s);
    if(!list) {
      SysError::setError("InteractionatorBldrFtry config for shapebuilder is invalid"s);
      return;
    }

    inatorb->setActorBldr(*actorBuilder);
    inatorb->setReactorBldr(*reactorBuilder);
    inatorb->setShapeBldr(*shapeBuilder);
    inatorb->setInternalInerList(*list);

    JSONFactory::loadAllIndexed<typename InatorBldr::InerList>(listInerRsrc, uintDict, j, zbe::factories::listName, "inerlists"s, "InteractionatorBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<typename InatorBldr::InerList> list) {
          inatorb->addInerList(idx, list);
          return true;
        }
    );

    JSONFactory::loadAllIndexed<typename InatorBldr::InatorList>(listAtorRsrc, uintDict, j, zbe::factories::listName, "inatorlists"s, "InteractionatorBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<typename InatorBldr::InatorList> list) {
          inatorb->addInatorList(idx, list);
          return true;
        }
    );

    JSONFactory::loadAllIndexed<typename InatorBldr::InerList>(listInerRsrc, uintDict, j, zbe::factories::listName, "deactivatedinerlists"s, "InteractionatorBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<typename InatorBldr::InerList> list) {
          inatorb->addDeactivatedInerList(idx, list);
          return true;
        }
    );

    JSONFactory::loadAllIndexed<typename InatorBldr::InatorList>(listAtorRsrc, uintDict, j, zbe::factories::listName, "deactivatedinatorlists"s, "InteractionatorBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<typename InatorBldr::InatorList> list) {
          inatorb->addDeactivatedInatorList(idx, list);
          return true;
        }
    );
  }
private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<void, std::shared_ptr<Entity>>>& mainRsrc = RsrcStore<Funct<void, std::shared_ptr<Entity>>>::getInstance();
  RsrcStore<InteractionatorBldr<IData, ActorType, ReactorType, Shapes...>>& specificRsrc = RsrcStore<InteractionatorBldr<IData, ActorType, ReactorType, Shapes...>>::getInstance();
//void(std::shared_ptr<Entity>)
  RsrcStore<TicketedForwardList<typename InatorBldr::Inator>>& listAtorRsrc = RsrcStore<TicketedForwardList<typename InatorBldr::Inator>>::getInstance();
  RsrcStore<typename InatorBldr::InerList>& listInerRsrc = RsrcStore<typename InatorBldr::InerList>::getInstance();
  RsrcStore<typename InatorBldr::ActorTypeBldr>& actorBldrRsrc = RsrcStore<typename InatorBldr::ActorTypeBldr>::getInstance();
  RsrcStore<typename InatorBldr::ReactorTypeBldr>& reactorBldrRsrc = RsrcStore<typename InatorBldr::ReactorTypeBldr>::getInstance();
  RsrcStore<typename InatorBldr::ShapeBldr>& shapeBldrRsrc = RsrcStore<typename InatorBldr::ShapeBldr>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
};



template<typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
class InteractionerBldrFtry : public Factory {
public:
  using InerBldr = InteractionerBldr<IData, ActorType, ReactorType, Shapes...>;
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<InerBldr> inerb = std::make_shared<InerBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, inerb);
    specificRsrc.insert("InteractionerBldr."s + name, inerb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);
    if(!cfg) {
      SysError::setError("InteractionerBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto inerb = specificRsrc.get("InteractionerBldr."s + name);
    auto j = *cfg;
    auto actorBuilder = JSONFactory::loadParamCfgStoreP<typename InerBldr::ActorTypeBldr>(actorBldrRsrc, j, zbe::factories::functionName, "actorbuilder"s, "InteractionerBldr"s);
    if(!actorBuilder) {
      SysError::setError("InteractionerBldrFtry config for actorbuilder is invalid"s);
      return;
    }

    auto reactorBuilder = JSONFactory::loadParamCfgStoreP<typename InerBldr::ReactorTypeBldr>(reactorBldrRsrc, j, zbe::factories::functionName, "reactorbuilder"s, "InteractionerBldr"s);
    if(!reactorBuilder) {
      SysError::setError("InteractionerBldrFtry config for reactorbuilder is invalid"s);
      return;
    }
    auto shapeBuilder = JSONFactory::loadParamCfgStoreP<typename InerBldr::ShapeBldr>(shapeBldrRsrc, j, zbe::factories::functionName, "shapebuilder"s, "InteractionerBldr"s);
    if(!shapeBuilder) {
      SysError::setError("InteractionerBldrFtry config for shapebuilder is invalid"s);
      return;
    }
    inerb->setActorBldr(*actorBuilder);
    inerb->setReactorBldr(*reactorBuilder);
    inerb->setShapeBldr(*shapeBuilder);
    JSONFactory::loadAllIndexed<typename InerBldr::InerList>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "InteractionerBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<typename InerBldr::InerList> list) {
          inerb->addInerList(idx, list);
          return true;
        }
    );

    JSONFactory::loadAllIndexed<typename InerBldr::InerList>(listRsrc, uintDict, j, zbe::factories::listName, "deactivatedlists"s, "InteractionerBldrFtry"s,
        [&](uint64_t idx, std::shared_ptr<typename InerBldr::InerList> list) {
          inerb->addDeactivatedInerList(idx, list);
          return true;
        }
    );
  }
private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<void, std::shared_ptr<Entity>>>& mainRsrc = RsrcStore<Funct<void, std::shared_ptr<Entity>>>::getInstance();
  RsrcStore<InerBldr>& specificRsrc = RsrcStore<InerBldr>::getInstance();

  RsrcStore<typename InerBldr::InerList>& listRsrc = RsrcStore<typename InerBldr::InerList>::getInstance();
  //RsrcStore<TicketedForwardList<typename InerBldr::Iner>>& listRsrc = RsrcStore<TicketedForwardList<typename InerBldr::Iner>>::getInstance();
  RsrcStore<typename InerBldr::ActorTypeBldr>& actorBldrRsrc = RsrcStore<typename InerBldr::ActorTypeBldr>::getInstance();
  RsrcStore<typename InerBldr::ReactorTypeBldr>& reactorBldrRsrc = RsrcStore<typename InerBldr::ReactorTypeBldr>::getInstance();
  RsrcStore<typename InerBldr::ShapeBldr>& shapeBldrRsrc = RsrcStore<typename InerBldr::ShapeBldr>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
};

class EntityTimerBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  void operator()(std::shared_ptr<Entity> ent) {
    auto ticket = teg->addRelativeTimer((*handlerBuilder)(ent), time);
    ent->addTicket(ticketId, ticket);
  }

  void setHandlerBuilder(std::shared_ptr<Funct<std::shared_ptr<TimeHandler>, std::shared_ptr<Entity>>> handlerBuilder) {
    this->handlerBuilder = handlerBuilder;
  }

  void setTeg(std::shared_ptr<TimeEventGenerator> teg, uint64_t time, uint64_t ticketId) {
    this->teg = teg;
    this->time = time;
    this->ticketId = ticketId;
  }

private:
  std::shared_ptr<Funct<std::shared_ptr<TimeHandler>, std::shared_ptr<Entity>>> handlerBuilder;
  std::shared_ptr<TimeEventGenerator> teg;
  uint64_t time;
  uint64_t ticketId;
};

class EntityTimerBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<EntityTimerBldr> etb = std::make_shared<EntityTimerBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, etb);
    specificRsrc.insert("EntityTimerBldr."s + name, etb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("EntityTimerBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto etb = specificRsrc.get("EntityTimerBldr."s + name);
    auto j = *cfg;

    auto handlerBldr = JSONFactory::loadParamCfgStoreP<HandlerBldrType>(handlerBldrRsrc, j, zbe::factories::functionName, "handlerbuilder"s, "EntityTimerBldrFtry"s);
    if(!handlerBldr) {
      SysError::setError("EntityTimerBldrFtry config for handlerbuilder is invalid"s);
      return;
    }
    etb->setHandlerBuilder(*handlerBldr);

    auto contextTime = JSONFactory::loadParamCfgStoreP<ContextTime>(cTimeRsrc, j, zbe::factories::contextimeName, "contextTime"s, "EntityTimerBldrFtry"s);
    if(!contextTime) {
      SysError::setError("EntityTimerBldrFtry config for contextTime is invalid"s);
      return;
    }

    auto teg = JSONFactory::loadParamCfgStoreP<TimeEventGenerator>(tegRsrc, j, "TimeEventGenerator"s, "teg"s, "EntityTimerBldrFtry"s);
    if(!teg) {
      SysError::setError("EntityTimerBldrFtry config for teg is invalid"s);
      return;
    }

    auto time = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "time"s, "EntityTimerBldrFtry"s);
    if(!time) {
      SysError::setError("EntityTimerBldrFtry config for time is invalid"s);
      return;
    }

    auto ticketId = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "ticketId"s, "EntityTimerBldrFtry"s);
    if(!ticketId) {
      SysError::setError("EntityTimerBldrFtry config for time is invalid"s);
      return;
    }
    etb->setTeg(*teg, *time, *ticketId);
  }

private:
  using HandlerBldrType = Funct<std::shared_ptr<TimeHandler>, std::shared_ptr<Entity>>;
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Funct<void, std::shared_ptr<Entity>>>& mainRsrc = RsrcStore<Funct<void, std::shared_ptr<Entity>>>::getInstance();
  RsrcStore<EntityTimerBldr>& specificRsrc = RsrcStore<EntityTimerBldr>::getInstance();

  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcStore<TimeEventGenerator>& tegRsrc = RsrcStore<TimeEventGenerator>::getInstance();
  RsrcStore<HandlerBldrType>& handlerBldrRsrc = RsrcStore<HandlerBldrType>::getInstance();
  RsrcDictionary<uint64_t> &uintDict = RsrcDictionary<uint64_t>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_BUILDERS_METABUILDER_H
