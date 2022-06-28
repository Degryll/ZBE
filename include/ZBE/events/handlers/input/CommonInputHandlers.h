/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CommonInputHandlers.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#ifndef ZBE_EVENTS_HANDLERS_COMMONINPUTHANDLERS_H_
#define ZBE_EVENTS_HANDLERS_COMMONINPUTHANDLERS_H_

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <nlohmann/json.hpp>

#include "ZBE/factories/Factory.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/io/Input.h"

#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

template<typename T>
class KeyValueSetterIHFtry;


template<typename T>
class KeyValueSetterIH : public InputHandler {
public:
  friend class KeyValueSetterIHFtry<T>;

  void setValue(std::shared_ptr<Value<T>> value) {
    this->value = value;
  }

  void setPressedVal(T val) {
    this->pressedVal = val;
  }

  void setReleaseVal(T val) {
    this->releaseVal = val;
  }

  void run(uint32_t, float status) {
    if (status < 0.5) {
      value->set(releaseVal);
    } else {
      value->set(pressedVal);
    }
  }

private:
  KeyValueSetterIH() : value(), pressedVal(), releaseVal() {}

  std::shared_ptr<Value<T>> value;
  T pressedVal;
  T releaseVal;
};

template<typename T>
class KeyValueSetterIHFtry : public Factory {

  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;

    auto kvsih = std::shared_ptr<KeyValueSetterIH<T>>(new KeyValueSetterIH<T>());
    mainRsrcStore.insert("InputHandler."s + name, kvsih);
    specificRsrcStore.insert("KeyValueSetterIH."s + name, kvsih);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);

    if(!cfg) {
      SysError::setError("KeyValueSetterIHFtry config for "s + name + " not found."s);
      return;
    }

    auto kvsih = specificRsrcStore.get("KeyValueSetterIH."s + name);
    auto j = *cfg;

    auto ieg = JSONFactory::loadParamCfgStoreP<InputEventGenerator>(iegStore, j, "InputEventGenerator"s, "inputEventGenerator"s, "KeyValueSetterIHFtry"s);
    if(!ieg) {
      SysError::setError("KeyValueSetterIHFtry config for inputEventGenerator is invalid"s);
      return;
    }

    auto key = JSONFactory::loadParamCfgDict<ZBE_K>(keyDict, j, "key"s, "KeyValueSetterIHFtry"s);
    if(!key) {
      SysError::setError("KeyValueSetterIHFtry config for key is invalid"s);
      return;
    }

    auto valuePressed = JSONFactory::loadParamCfgDict<T>(tDict, j, "valuePressed"s, "KeyValueSetterIHFtry"s);
    if(!valuePressed) {
      SysError::setError("KeyValueSetterIHFtry config for valuePressed is invalid"s);
      return;
    }

    auto valueReleased = JSONFactory::loadParamCfgDict<T>(tDict, j, "valueReleased"s, "KeyValueSetterIHFtry"s);
    if(!valueReleased) {
      SysError::setError("KeyValueSetterIHFtry config for valueReleased is invalid"s);
      return;
    }

    auto value = JSONFactory::loadParamCfgStore<Value<Vector3D>>(valueStore, j, "value"s, "KeyValueSetterIHFtry"s);
    if(!value) {
      SysError::setError("KeyValueSetterIHFtry config for value is invalid"s);
      return;
    }

    kvsih->setPressedVal(*valuePressed);
    kvsih->setReleaseVal(*valueReleased);
    kvsih->setValue(*value);

    (*ieg)->addHandler(*key, kvsih);

/*
const ZBE_K ZBEK_RIGHT = 1073741903;
const ZBE_K ZBEK_LEFT = 1073741904;
const ZBE_K ZBEK_DOWN = 1073741905;
const ZBE_K ZBEK_UP = 1073741906;
*/
/*
"inputEventGenerator" : "loadScreen.inputEventGenerator",
"key":"ZBEK_UP",
"valuePressed":"boxUpSpeed",
"valueReleased":"ZERO",
"value" : "zandbokz.boxVector"
*/

    // if(cfg) {
    //   auto j = *cfg;
    //   if (!j["ticket"].is_string()) {
    //     SysError::setError("ActivatorIHFtry config for ticket: "s + j["ticket"].get<std::string>() + ": must be a ticket name."s);
    //     return;
    //   }
    //   std::string ticketName = j["ticket"].get<std::string>();
    //   if(!ticketStore.contains(ticketName)) {
    //     SysError::setError("ActivatorIHFtry config for ticket: "s + ticketName + " is not a ticket name."s);
    //     return;
    //   }

    //   if (!j["inputEventGenerator"].is_string()) {
    //     SysError::setError("ActivatorIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
    //     return;
    //   }

    //   std::string inputEventGeneratorName = j["inputEventGenerator"].get<std::string>();
    //   if(!iegStore.contains("InputEventGenerator."s + inputEventGeneratorName)) {
    //     SysError::setError("ActivatorIHFtry config for inputEventGenerator: "s + inputEventGeneratorName + " is not an inputEventGenerator name."s);
    //     return;
    //   }

    //   if (!j["key"].is_string()) {
    //     SysError::setError("ActivatorIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
    //     return;
    //   }

    //   std::string keyName = j["key"].get<std::string>();
    //   if(!keyDict.contains(keyName)) {
    //     SysError::setError("ActivatorIHFtry config for key: "s + keyName + " is not a key name."s);
    //     return;
    //   }

    //   auto ticket = ticketStore.get(ticketName);
    //   auto ieg    = iegStore.get("InputEventGenerator."s + inputEventGeneratorName);
    //   auto key    = keyDict.get(keyName);
    //   auto ih     = paihStore.get("ActivatorIH."s + name);

    //   ih->setTicket(ticket);



    // } else {
    //   SysError::setError("ActivatorIHFtry config for "s + name + " not found."s);
    // }
  }

private:
  RsrcStore<nlohmann::json> &configStore            = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<std::string>& strStore             = RsrcDictionary<std::string>::getInstance();
  RsrcDictionary<ZBE_K>& keyDict                    = RsrcDictionary<ZBE_K>::getInstance();
  RsrcDictionary<T>& tDict                          = RsrcDictionary<T>::getInstance();
  RsrcStore<Value<T> > &valueStore                  = RsrcStore<Value<T> >::getInstance();
  RsrcStore<KeyValueSetterIH<T>>& specificRsrcStore = RsrcStore<KeyValueSetterIH<T>>::getInstance();
  RsrcStore<InputHandler>& mainRsrcStore            = RsrcStore<InputHandler>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore          = RsrcStore<InputEventGenerator>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_COMMONINPUTHANDLERS_H_
