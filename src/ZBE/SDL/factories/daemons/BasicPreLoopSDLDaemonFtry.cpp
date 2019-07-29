/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BasicPreLoopSDLDaemonFtry.cpp
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Ludo Degryll Batis
 * @brief Factory for BasicPreLoopSDLDaemon.
 */

#include "ZBE/SDL/factories/daemons/BasicPreLoopSDLDaemonFtry.h"

namespace zbe {

void BasicPreLoopSDLDaemonFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto preloop = std::make_shared<BasicPreLoopSDLDaemon>();
  daemonRsrc.insert("Daemon."s + name, preloop);
  preloopRsrc.insert("BasicPreLoopSDLDaemon."s + name, preloop);
}

void BasicPreLoopSDLDaemonFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json window = j["window"];
    if(!window.is_string()) {
      SysError::setError("Bad config for BasicPreLoopSDLDaemonFtry - window."s + window.get<std::string>());
      return;
    }

    auto winname = j["window"].get<std::string>();
    auto win = sdlWindowRsrc.get("SDLWindow."s + winname);

    auto preloop = preloopRsrc.get("BasicPreLoopSDLDaemon."s + name);
    preloop->setWindow(win);
  } else {
    SysError::setError("BasicPreLoopSDLDaemonFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
