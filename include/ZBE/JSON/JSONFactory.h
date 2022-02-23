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

#include "ZBE/factories/Factory.h"
#include "ZBE/core/system/system.h"

#include <nlohmann/json.hpp>

namespace zbe {

namespace JSONFactory {
using namespace nlohmann;

template<typename T>
std::optional<std::shared_ptr<T>> readFromStore(RsrcStore<T>& store, json cfg, std::string parameter, std::string factoryName) {
  using namespace std::string_literals;
  if (!cfg[parameter].is_string()) {
    SysError::setError(factoryName + " config for "s + parameter + ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
    return std::nullopt;
  }

  std::string paramName = cfg[parameter].get<std::string>();
  if(!store.contains(paramName)) {
    SysError::setError(factoryName + " config for " + parameter + ": "s + paramName + " does not exist."s);
    return std::nullopt;
  }

  return store.get(paramName);
}

template<typename T>
std::optional<std::shared_ptr<T>> readFromDcit(RsrcDictionary<T>& dict, json cfg, std::string prefix, std::string parameter, std::string factoryName) {
  using namespace std::string_literals;
  if (!cfg[parameter].is_string()) {
    SysError::setError(factoryName + " config for "s + parameter + ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
    return std::nullopt;
  }

  std::string paramName = cfg[parameter].get<std::string>();
  if(!dict.contains(prefix + paramName)) {
    SysError::setError(factoryName + " config for " + parameter + ": "s + paramName + "inside " + prefix + " does not exist."s);
    return std::nullopt;
  }

  return dict.get(prefix+paramName);
}

template<typename T>
bool loadAllIndexed(RsrcStore<T>& store, RsrcDictionary<uint64_t>& uintDict, json cfg, std::string parameter, std::string factoryName, std::function<bool(uint64_t, std::shared_ptr<T>)> callback) {
  using namespace std::string_literals;
  if (cfg[parameter].is_object()) {
    auto arrayCfg = cfg[parameter];
    for (auto item : arrayCfg.items()) {
      auto key = item.key();
      auto element = readFromStore<T>(store, arrayCfg, key, factoryName);
      if(!element) {
        SysError::setError(factoryName + " config for "s + parameter + ": "s + cfg[parameter].get<std::string>() + " contains a non valid tool name:"s + key);
        return false;
      }
      if(!uintDict.contains(key)) {
        SysError::setError(factoryName + " config for "s + parameter + ": "s + cfg[parameter].get<std::string>() + " contains a non valid index name:"s + key);
        return false;
      }
      uint64_t idx = uintDict.get(key);
      if(!callback(idx, *element)) {
        return false;
      }
    }
  } else if(cfg.contains(parameter)) {
    return false;
  }
  return true;
}

}  // namespace JSONFactory

}  // namespace zbe

#endif  // ZBE_FACTORIES_JSONFACTORY_H_
