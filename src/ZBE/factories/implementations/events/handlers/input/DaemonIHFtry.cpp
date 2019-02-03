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
      json daemonCfg = j["daemon"];
      auto dcih = dcihRsrc.get("DaemonIH."s + name);
      if (daemonCfg.is_string()){
        std::string daemonName = daemonCfg.get<std::string>();
        dcih->setDaemon(daemonRsrc.get("Daemon."s + daemonName));
      } else {
        SysError::setError("DaemonIH handler daemon config for "s + name + " is invalid."s);
      }
    } else {
      SysError::setError("DaemonIH config for "s + name + " not found."s);
    }
}

}  // namespace zbe
