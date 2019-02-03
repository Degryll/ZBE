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

  timeRsrc.insert("TimeHandler."s + name, dth);
  dmnTimeHandlerRsrc.insert("DaemonTimeHandler."s + name, dth);
}

void DaemonTimeHandlerFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["daemon"].is_string()) {
      std::string dname = j["daemon"].get<std::string>();
      std::shared_ptr<Daemon> daemon = dmnRsrc.get("Daemon."s + dname);

      auto dth = dmnTimeHandlerRsrc.get("DaemonTimeHandler."s + name);
      dth->setDaemon(daemon);

    } else {
      SysError::setError("DaemonTimeHandlerFtry config for "s + j["daemon"].get<std::string>() + ": must be a string."s);
    }
  } else {
    SysError::setError("DaemonTimeHandlerFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
