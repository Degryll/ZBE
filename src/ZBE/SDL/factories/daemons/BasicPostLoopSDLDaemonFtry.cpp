/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BasicPostLoopSDLDaemonFtry.cpp
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Ludo Degryll Batis
 * @brief Factory for BasicPostLoopSDLDaemon.
 */

#include "ZBE/SDL/factories/daemons/BasicPostLoopSDLDaemonFtry.h"

namespace zbe {

void BasicPostLoopSDLDaemonFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto postloop = std::make_shared<BasicPostLoopSDLDaemon>();
  daemonRsrc.insert("Daemon."s + name, postloop);
  postloopRsrc.insert("BasicPostLoopSDLDaemon."s + name, postloop);
}

void BasicPostLoopSDLDaemonFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json window = j["window"];
    if(!window.is_string()) {
      SysError::setError("Bad config for BasicPostLoopSDLDaemonFtry - window."s + window.get<std::string>());
      return;
    }

    auto winname = j["window"].get<std::string>();
    auto win = sdlWindowRsrc.get("SDLWindow."s + winname);

    auto postloop = postloopRsrc.get("BasicPostLoopSDLDaemon."s + name);
    postloop->setWindow(win);
  } else {
    SysError::setError("BasicPostLoopSDLDaemonFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
