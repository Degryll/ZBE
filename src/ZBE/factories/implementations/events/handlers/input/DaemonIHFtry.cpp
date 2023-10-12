/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonIH.cpp
 * @since 2019-01-31
 * @date 2019-01-31
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonIH.
 */

#include "ZBE/factories/implementations/events/handlers/input/DaemonIHFtry.h"

namespace zbe {

void DaemonIHFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;
  std::shared_ptr<DaemonIH> dcih = std::make_shared<DaemonIH>();

  uint64_t id = SysIdGenerator::getId();
  inputRsrc.insert(id, dcih);
  dict.insert("InputHandler."s + name, id);
  id = SysIdGenerator::getId();
  dcihRsrc.insert(id, dcih);
  dict.insert("DaemonIH."s + name, id);
}

void DaemonIHFtry::setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      if (!j["daemon"].is_string()) {
        SysError::setError("DaemonIH config for daemon: "s + j["daemon"].get<std::string>() + ": must be a daemon name."s);
        return;
      }

      std::string daemonName = j["daemon"].get<std::string>();
      if(!daemonStore.contains("Daemon."s + daemonName)) {
        SysError::setError("DaemonIH config for daemon: "s + daemonName + " is not a daemon name."s);
        return;
      }

      auto daemon = daemonStore.get("Daemon."s + daemonName);
      auto ih   = dcihRsrc.get("DaemonIH."s + name);
      ih->setDaemon(daemon);

      bool haskey = j["key"].is_string();
      bool hasIeg = j["inputEventGenerator"].is_string();

      if(haskey != hasIeg) {
        if (!hasIeg) {
          SysError::setError("DaemonIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
          return;
        } else {
          SysError::setError("DaemonIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
          return;
        }
      }

      if(haskey) {
        std::string inputEventGeneratorName = j["inputEventGenerator"].get<std::string>();
        if(!iegStore.contains("InputEventGenerator."s + inputEventGeneratorName)) {
          SysError::setError("DaemonIHFtry config for inputEventGenerator: "s + inputEventGeneratorName + " is not an inputEventGenerator name."s);
          return;
        }

        std::string keyName = j["key"].get<std::string>();
        if(!keyDict.contains(keyName)) {
          SysError::setError("DaemonIHFtry config for key: "s + keyName + " is not a key name."s);
          return;
        }

        auto ieg    = iegStore.get("InputEventGenerator."s + inputEventGeneratorName);
        auto key    = keyDict.get(keyName);
        ieg->addHandler(key, ih);
      }

    } else {
      SysError::setError("DaemonIH config for "s + name + " not found."s);
    }
}

}  // namespace zbe
