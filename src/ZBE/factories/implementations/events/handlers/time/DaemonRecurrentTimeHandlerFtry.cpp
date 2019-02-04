/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonRecurrentTimeHandlerFtry.cpp
 * @since 2019-01-31
 * @date 2019-01-31
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonRecurrentTimeHandler.
 */

#include "ZBE/factories/implementations/events/handlers/time/DaemonRecurrentTimeHandlerFtry.h"

namespace zbe {

void DaemonRecurrentTimeHandlerFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  std::shared_ptr<DaemonRecurrentTimeHandler> drth = std::make_shared<DaemonRecurrentTimeHandler>();
  timeRsrc.insert("TimeHandler."s + name, drth);
  dmnRecurrentTimeHandlerRsrc.insert("DaemonRecurrentTimeHandler."s + name, drth);
}

void DaemonRecurrentTimeHandlerFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    std::shared_ptr<Daemon> daemon;
    std::shared_ptr<TimeEventGenerator> teg;
    std::shared_ptr<AvatarEntity<Avatar> > a;
    uint64_t id = 0;
    uint64_t period = 0;
    if (j["daemon"].is_string()) {
      std::string dname = j["daemon"].get<std::string>();
      daemon = dmnRsrc.get("Daemon."s + dname);
    } else {
      SysError::setError("DaemonRecurrentTimeHandlerFtry config for "s + j["daemon"].get<std::string>() + ": must be a string."s);
    }

    if (j["timeEventGenerator"].is_string()) {
      std::string tname = j["timeEventGenerator"].get<std::string>();
      teg = tegRsrc.get("timeEventGenerator."s + tname);
    } else {
      SysError::setError("DaemonRecurrentTimeHandlerFtry config for "s + j["timeEventGenerator"].get<std::string>() + ": must be a string."s);
    }

    if (j["avatar"].is_string()) {
      std::string aname = j["avatar"].get<std::string>();
      a = avatarRsrc.get("avatar."s + aname);
    } else {
      SysError::setError("DaemonRecurrentTimeHandlerFtry config for "s + j["avatar"].get<std::string>() + ": must be a string."s);
    }

    if (j["id"].is_string()) {
      std::string iname = j["id"].get<std::string>();
      id = dict.get(iname);
    } else {
      SysError::setError("DaemonRecurrentTimeHandlerFtry config for "s + j["id"].get<std::string>() + ": must be a string."s);
    }

    if (j["period"].is_string()) {
      std::string pname = j["period"].get<std::string>();
      period = dict.get(pname);
    } else {
      SysError::setError("DaemonRecurrentTimeHandlerFtry config for "s + j["period"].get<std::string>() + ": must be a string."s);
    }

    auto drth = dmnRecurrentTimeHandlerRsrc.get("DaemonRecurrentTimeHandler."s + name);
    drth->setDaemon(daemon);
    drth->setTimeEventGenerator(teg);
    drth->setAvatar(a, id);
    drth->setPeriod(period);

  } else {
    SysError::setError("DaemonRecurrentTimeHandlerFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
