/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonClickIH.cpp
 * @since 2019-01-14
 * @date 2019-01-14
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonClickIH.
 */

#include "ZBE/factories/implementations/events/handlers/input/DaemonClickIHFtry.h"

namespace zbe {

void DaemonClickIHFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  std::shared_ptr<DaemonClickIH> dcih = std::make_shared<DaemonClickIH>();

  uint64_t id = SysIdGenerator::getId();
  inputRsrc.insert(id, dcih);
  dict.insert("InputHandler."s + name, id);
  id = SysIdGenerator::getId();
  dcihRsrc.insert(id, dcih);
  dict.insert("DaemonClickIH."s + name, id);
}

void DaemonClickIHFtry::setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json daemonCfg = j["daemon"];
      auto dcih = dcihRsrc.get("DaemonClickIH."s + name);
      if (daemonCfg.is_string()){
        std::string daemonName = daemonCfg.get<std::string>();
        dcih->setDaemon(daemonRsrc.get("Daemon."s + daemonName));
      } else {
        SysError::setError("DaemonClickIH handler daemon config for "s + name + " is invalid."s);
      }
      json xcfg = j["x"];
      json ycfg = j["y"];
      json hcfg = j["h"];
      json wcfg = j["w"];

      if (xcfg.is_number() && ycfg.is_number() && hcfg.is_number() && wcfg.is_number()){
        dcih->setArea(Region2D({xcfg.get<double>(), ycfg.get<double>()},{hcfg.get<double>(),wcfg.get<double>()}));
      } else {
        SysError::setError("DaemonClickIH handler box config for "s + name + " is invalid."s);
      }

      json xValcfg = j["xval"];
      json yValcfg = j["yval"];

      if (xValcfg.is_string() && yValcfg.is_string()){
        std::string daemonName = xValcfg.get<std::string>();
        dcih->setYValue(valueDRsrc.get("ValueD."s + yValcfg.get<std::string>()));
        dcih->setXValue(valueDRsrc.get("ValueD."s + xValcfg.get<std::string>()));
      } else {
        SysError::setError("DaemonClickIH handler pointer input config for "s + name + " is invalid."s);
      }

    } else {
      SysError::setError("DaemonClickIH config for "s + name + " not found."s);
    }
}

}  // namespace zbe
