/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonTimeHandlerFtry.cpp
 * @since 2018-12-26
 * @date 2018-12-26
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonTimeHandler.
 */

#include "ZBE/factories/implementations/events/handlers/time/DaemonTimeHandlerFtry.h"

namespace zbe {

void DaemonTimeHandlerFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  std::shared_ptr<DaemonTimeHandler> dth = std::make_shared<DaemonTimeHandler>();
  dmnTimeHandlerRsrc.insert("DaemonTimeHandler."s + name, dth);
}

void DaemonTimeHandlerFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (!j["dmn"].is_string()) {
      SysError::setError("DaemonTimeHandlerFtry config for dmn "s + j["dmn"].get<std::string>() + ": must be a string."s);
      return;
    }
    if (!j["generator"].is_string()) {
      SysError::setError("DaemonTimeHandlerFtry config for generator "s + j["generator"].get<std::string>() + ": must be a string."s);
      return;
    }
    if (!j["time"].is_string()){
      SysError::setError("DaemonTimeHandlerFtry config for time "s + j["time"].get<std::string>() + ": must be a string."s);
      return;
    }
    std::string dname = j["dmn"].get<std::string>();
    std::string gname = j["generator"].get<std::string>();
    std::string tname = j["time"].get<std::string>();

    std::shared_ptr<Daemon> daemon = dmnRsrc.get("Daemon."s + dname);
    std::shared_ptr<TimeEventGenerator> teg = tegRsrc.get("TimeEventGenerator."s + gname);
    uint64_t time = intStore.get(tname);

    auto dth = dmnTimeHandlerRsrc.remove("DaemonTimeHandler."s + name);
    dth->setDaemon(daemon);

    teg->addTimer(dth, time);

  } else {
    SysError::setError("DaemonTimeHandlerFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
