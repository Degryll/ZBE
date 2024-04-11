/**
 * Copyright 2012 Batis Degryll Ludo
 * @file JSONFactory.h
 * @since 2018-09-03
 * @date 2018-09-03
 * @author Ludo Degryll Batis
 * @brief Define the interface of a Factory.
 */

#ifndef ZBE_FACTORIES_JSONFACTORY_H_
#define ZBE_FACTORIES_JSONFACTORY_H_

#include <string>
#include <optional>

#include "ZBE/factories/genericFactoryConstants.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include <nlohmann/json.hpp>

namespace zbe {

namespace JSONFactory {
using namespace nlohmann;

template<typename T, typename Store>
std::optional<typename Store::StoredType> loadParamStrP(Store& store, std::string prefix, std::string parameter, std::string factoryName) {
  using namespace std::string_literals;
  std::string paramName = prefix + zbe::factories::separator + parameter;
  if(!store.contains(paramName)) {
    SysError::setError(factoryName + " config for " + parameter + " inside " + prefix + " does not exist."s);
    return std::nullopt;
  }

  return store.get(paramName);
}

template<typename T, typename Store>
std::optional<typename Store::StoredType> loadParamCfgP(Store& store, json cfg, std::string prefix, std::string parameter, std::string factoryName) {
  using namespace std::string_literals;
  if (!cfg[parameter].is_string()) {
    SysError::setError(factoryName + " config for "s + parameter + " must be a string."s);
    return std::nullopt;
  }
  return loadParamStrP<T, Store>(store, prefix, cfg[parameter].get<std::string>(), factoryName);
}

template<typename T, typename Store>
std::optional<typename Store::StoredType> loadParamStr(Store& store, std::string parameter, std::string factoryName) {
  using namespace std::string_literals;
  if(!store.contains(parameter)) {
    SysError::setError(factoryName + " config for " + parameter + " does not exist."s);
    return std::nullopt;
  }

  return store.get(parameter);
}

template<typename T, typename Store>
std::optional<typename Store::StoredType> loadParamCfg(Store& store, json cfg, std::string parameter, std::string factoryName) {
  using namespace std::string_literals;
  if (!cfg[parameter].is_string()) {
    SysError::setError(factoryName + " config for "s + parameter + " must be a string."s);
    return std::nullopt;
  }
  return loadParamStr<T, Store>(store, cfg[parameter].get<std::string>(), factoryName);
}

template<typename T>
const auto loadParamCfgStore = loadParamCfg<T, RsrcStore<T>>;

template<typename T>
const auto loadParamCfgDict = loadParamCfg<T, RsrcDictionary<T>>;

template<typename T>
const auto loadParamStrStore = loadParamStr<T, RsrcStore<T>>;

template<typename T>
const auto loadParamStrDict = loadParamStr<T, RsrcDictionary<T>>;

template<typename T>
const auto loadParamCfgStoreP = loadParamCfgP<T, RsrcStore<T>>;

template<typename T>
const auto loadParamCfgDictP = loadParamCfgP<T, RsrcDictionary<T>>;

template<typename T>
const auto loadParamStrStoreP = loadParamStrP<T, RsrcStore<T>>;

template<typename T>
const auto loadParamStrDictP = loadParamStrP<T, RsrcDictionary<T>>;


// template<typename T>
// std::optional<std::shared_ptr<T>> readFromStore(RsrcStore<T>& store, json cfg, std::string parameter, std::string factoryName) {
//   using namespace std::string_literals;
//   if (!cfg[parameter].is_string()) {
//     SysError::setError(factoryName + " config for "s + parameter + " must be a string."s);
//     return std::nullopt;
//   }
//
//   std::string paramName = cfg[parameter].get<std::string>();
//   if(!store.contains(paramName)) {
//     SysError::setError(factoryName + " config for " + parameter + ": "s + paramName + " does not exist."s);
//     return std::nullopt;
//   }
//
//   return store.get(paramName);
// }
//
// template<typename T>
// std::optional<std::shared_ptr<T>> readFromDcit(RsrcDictionary<T>& dict, json cfg, std::string prefix, std::string parameter, std::string factoryName) {
//   using namespace std::string_literals;
//   if (!cfg[parameter].is_string()) {
//     SysError::setError(factoryName + " config for "s + parameter + ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
//     return std::nullopt;
//   }
//
//   std::string paramName = cfg[parameter].get<std::string>();
//   if(!dict.contains(prefix + paramName)) {
//     SysError::setError(factoryName + " config for " + parameter + ": "s + paramName + "inside " + prefix + " does not exist."s);
//     return std::nullopt;
//   }
//
//   return dict.get(prefix+paramName);
// }


template<typename T>
bool loadAllIndexed(RsrcStore<T>& store, RsrcDictionary<uint64_t>& uintDict, json cfg, std::string prefix, std::string parameter, std::string factoryName, std::function<bool(uint64_t, std::shared_ptr<T>)> callback) {
  using namespace std::string_literals;
  if (cfg[parameter].is_object()) {
    auto arrayCfg = cfg[parameter];
    for (auto item : arrayCfg.items()) { //+ zbe::factories::separator
      auto key = item.key();

      auto element = loadParamStrStoreP<T>(store, prefix, key, factoryName);
      if(!element) {
        SysError::setError(factoryName + " config for "s + parameter + " contains a non valid element name:"s + key);
        return false;
      }

      if (!item.value().is_string()) {
        SysError::setError(factoryName + " config for "s + key + " must be a string."s);
        return false;
      }

      auto idxName = item.value().get<std::string>();

      if(!uintDict.contains(idxName)) {
        SysError::setError(factoryName + " config for "s + parameter + " contains a non valid index name:"s + idxName);
        return false;
      }

      uint64_t idx = uintDict.get(idxName);
      if(!callback(idx, *element)) {
        return false;
      }
    }
  } else if(cfg.contains(parameter)) {
    return false;
  }
  return true;
}

template<typename T>
bool loadAllIndexedRev(RsrcStore<T>& store, RsrcDictionary<uint64_t>& uintDict, json cfg, std::string prefix, std::string parameter, std::string factoryName, std::function<bool(uint64_t, std::shared_ptr<T>)> callback) {
  using namespace std::string_literals;
  if (cfg[parameter].is_object()) {
    auto arrayCfg = cfg[parameter];
    for (auto item : arrayCfg.items()) { //+ zbe::factories::separator
      auto key = item.key();
      if(!uintDict.contains(key)) {
        SysError::setError(factoryName + " config for "s + parameter + " contains a non valid element name:"s + key);
        return false;
      }
      uint64_t idx = uintDict.get(key);

      if (!item.value().is_string()) {
        SysError::setError(factoryName + " config for "s + key + " must be a string."s);
        return false;
      }
      
      auto elementName = item.value().get<std::string>();
      auto element = loadParamStrStoreP<T>(store, prefix, elementName, factoryName);
      if(!element) {
        SysError::setError(factoryName + " config for "s + parameter + " contains a non valid element name:"s + elementName);
        return false;
      }

      if(!callback(idx, *element)) {
        return false;
      }
    }
  } else if(cfg.contains(parameter)) {
    return false;
  }
  return true;
}

template<typename T>
bool loadAllP(RsrcStore<T>& store, json cfg, std::string prefix, std::string parameter, std::string factoryName, std::function<bool(std::shared_ptr<T>)> callback) {
  using namespace std::string_literals;
  if (cfg[parameter].is_array()) {
    auto arrayCfg = cfg[parameter];
    for (auto& item : arrayCfg.items()) {
      auto& jvalue = item.value();
      if (!jvalue.is_string()) {
        SysError::setError(factoryName + " elementos on "s + parameter + " must be strings."s);
        return false;
      }
      auto value = jvalue.get<std::string>();
      auto element = loadParamStrStoreP<T>(store, prefix, value, factoryName);
      if(!element) {
        SysError::setError(factoryName + " config for "s + parameter + " contains a non valid element name:"s + value);
        return false;
      }

      if(!callback(*element)) {
        return false;
      }
    }
  } else if(cfg.contains(parameter)) {
    SysError::setError(factoryName + " config for " + parameter + " must be an array."s);
    return false;
  }
  return true;
}

template<typename T>
bool loadAll(RsrcStore<T>& store, json cfg, std::string parameter, std::string factoryName, std::function<bool(std::shared_ptr<T>)> callback) {
  using namespace std::string_literals;
  if (cfg[parameter].is_array()) {
    auto arrayCfg = cfg[parameter];
    for (auto& item : arrayCfg.items()) {
      auto& jvalue = item.value();
      if (!jvalue.is_string()) {
        SysError::setError(factoryName + " elementos on "s + parameter + " must be strings."s);
        return false;
      }
      auto value = jvalue.get<std::string>();
      auto element = loadParamStrStore<T>(store, value, factoryName);
      if(!element) {
        SysError::setError(factoryName + " config for "s + parameter + " contains a non valid element name:"s + value);
        return false;
      }

      if(!callback(*element)) {
        return false;
      }
    }
  } else if(cfg.contains(parameter)) {
    SysError::setError(factoryName + " config for " + parameter + " must be an array."s);
    return false;
  }
  return true;
}

template<typename T, unsigned n>
std::optional<std::array<T, n>> loadLiteralArray(RsrcDictionary<T>& dict, json cfg, std::string paramName, std::string factoryName) {
  using namespace std::string_literals;
  if (!cfg.is_array()) {
    SysError::setError(factoryName + " config for " + paramName + " must be an array."s);
    return std::nullopt;
  }

  if(cfg.size() != n) {
    SysError::setError(factoryName + " config for " + paramName + " must have "s + std::to_string(n) + " elements");
    return std::nullopt;
  }

  std::array<T, n> arr;
  int i = 0;
  for (auto& name : cfg.items()) {
    arr[i] = dict.get(name.value().get<std::string>());
    i++;
  }
  return arr;
}

template<typename T>
std::optional<std::forward_list<T>> loadLiteralList(RsrcDictionary<T>& dict, json cfg, std::string paramName, std::string factoryName, uint64_t min = 0, uint64_t max = 0) {
  using namespace std::string_literals;
  if (!cfg.is_array()) {
    SysError::setError(factoryName + " config for " + paramName + " must be an array."s);
    return std::nullopt;
  }

  if(cfg.size() < min) {
    SysError::setError(factoryName + " config for " + paramName + " must have at least "s + std::to_string(min) + " elements");
    return std::nullopt;
  }

  if(max>0 && cfg.size() > max) {
    SysError::setError(factoryName + " config for " + paramName + " must have no more than "s + std::to_string(max) + " elements");
    return std::nullopt;
  }

  std::forward_list<T> list;
  for (auto& name : cfg.items()) {
    list.push_front(dict.get(name.value().get<std::string>()));
  }
  return list;
}

Vector3D parseV3DFromCfg(nlohmann::json cfgValue, std::string paramName, std::string factoryName);

}  // namespace JSONFactory

}  // namespace zbe

#endif  // ZBE_FACTORIES_JSONFACTORY_H_
