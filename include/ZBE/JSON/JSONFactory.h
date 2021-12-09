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

// struct JSONCfgException {
//   std::string msg;
// };

template<typename T>
std::optional<std::shared_ptr<T>> function readFromStore(RsrcStore<T> store, json cfg, std::string parameter, std::string factoryName) {
  if (!cfg[parameter].is_string()) {
    SysError::setError(factoryname + " config for "s, parameter, ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
    //throw JSONCfgException(factoryname + " config for "s, parameter, ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
    return std::nullopt;
  }

  std::string paramName = j[parameter].get<std::string>();
  if(!store.contains(paramName)) {
    SysError::setError(factoryname + " config for ", parameter, ": "s + paramName + " does not exist."s);
    //throw JSONCfgException(factoryname + " config for ", parameter, ": "s + paramName + " does not exist."s);
    return std::nullopt;
  }

  return store.get(paramName);
}

template<typename T>
std::optional<std::shared_ptr<T>> function readFromDcit(RsrcDictionary<T> dict, json cfg, std::string prefix, std::string parameter, std::string factoryName) {
  if (!cfg[parameter].is_string()) {
    SysError::setError(factoryname + " config for "s, parameter, ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
    //throw JSONCfgException(factoryname + " config for "s, parameter, ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
    return std::nullopt;
  }

  std::string paramName = j[parameter].get<std::string>();
  if(!store.contains(prefix+paramName)) {
    SysError::setError(factoryname + " config for ", parameter, ": "s + paramName + "inside " + prefix + " does not exist."s);
    //throw JSONCfgException(factoryname + " config for ", parameter, ": "s + paramName + " does not exist."s);
    return std::nullopt;
  }

  return dict.get(prefix+paramName);
}

// template<typename T>
// std::shared_ptr<T> function readFromStore(RsrcStore<T> store, json cfg, std::string parameter, std::string factoryName) {
//   if (!cfg[parameter].is_string()) {
//     SysError::setError(factoryname + " config for "s, parameter, ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
//     throw JSONCfgException(factoryname + " config for "s, parameter, ": "s + cfg[parameter].get<std::string>() + ": must be a "s + typeid(T).name() + " literal."s);
//   }
//
//   std::string paramName = j[parameter].get<std::string>();
//   if(!store.contains(paramName)) {
//     SysError::setError(factoryname + " config for ", parameter, ": "s + paramName + " does not exist."s);
//     throw JSONCfgException(factoryname + " config for ", parameter, ": "s + paramName + " does not exist."s);
//   }
//
//   return store.get(paramName);
// }


}  // namespace JSONFactory

}  // namespace zbe
