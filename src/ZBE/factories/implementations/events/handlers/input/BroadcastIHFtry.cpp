/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BroadcastIHFtry.cpp
 * @since 2019-01-14
 * @date 2019-01-14
 * @author Ludo Degryll Batis
 * @brief Factory for BroadcastIH.
 */

#include "ZBE/factories/implementations/events/handlers/input/BroadcastIHFtry.h"

namespace zbe {

void BroadcastIHFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;
  std::shared_ptr<BroadcastIH> bih = std::make_shared<BroadcastIH>();

  uint64_t id = SysIdGenerator::getId();
  inputRsrc.insert(id, bih);
  dict.insert("InputHandler."s + name, id);
  id = SysIdGenerator::getId();
  bihRsrc.insert(id, bih);
  dict.insert("BroadcastIH."s + name, id);
}

void BroadcastIHFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(!cfg) {
    SysError::setError("BroadcastIHFtry config for "s + name + " not found."s);
    return;
  }

  auto j = *cfg;


  bool haskey = j["key"].is_string();
  bool hasIeg = j["inputEventGenerator"].is_string();

  json handlers = j["handlers"];
  auto bih = bihRsrc.get("BroadcastIH."s + name);
  for (auto hnd : handlers) {
    if (hnd.is_string()){
      std::string handlerName = hnd.get<std::string>();
      bih->addHandler(inputRsrc.get("InputHandler."s + handlerName));
    } else {
      SysError::setError("BroadcastIHFtry handlers config contains an invalid element ."s);
    }
  }

  if(haskey != hasIeg) {
    if (!hasIeg) {
      SysError::setError("BroadcastIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
      return;
    } else {
      SysError::setError("BroadcastIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
      return;
    }
  }

  if(haskey) {
    auto ieg = JSONFactory::loadParamCfgStoreP<InputEventGenerator>(iegStore, j, "InputEventGenerator"s, "inputEventGenerator"s, "BroadcastIHFtry"s);
    if(!ieg) {
      SysError::setError("BroadcastIHFtry config for inputEventGenerator is invalid"s);
      return;
    }

    auto key = JSONFactory::loadParamCfgDict<ZBE_K>(keyDict, j, "key"s, "BroadcastIHFtry"s);
    if(!key) {
      SysError::setError("BroadcastIHFtry config for key is invalid"s);
      return;
    }

    (*ieg)->addHandler(*key, bih);
  }

}

}  // namespace zbe