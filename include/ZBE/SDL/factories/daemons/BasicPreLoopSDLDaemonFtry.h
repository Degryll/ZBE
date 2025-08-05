/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BasicPreLoopSDLDaemonFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for BasicPreLoopSDLDaemon.
 */

#ifndef ZBE_SDL_FACTORIES_DAEMONS_BASICPRELOOPSDLDAEMONFTRY_H_
#define ZBE_SDL_FACTORIES_DAEMONS_BASICPRELOOPSDLDAEMONFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for BasicPreLoopSDLDaemon.
 */
class BasicPreLoopSDLDaemonFtry : virtual public Factory {
public:

  /** \brief Builds a BasicPreLoopSDLDaemon.
   *  \param name Name for the created BasicPreLoopSDLDaemon.
   *  \param cfgId BasicPreLoopSDLDaemon's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto preloop = std::make_shared<BasicPreLoopSDLDaemon>();
    daemonRsrc.insert("Daemon."s + name, preloop);
    preloopRsrc.insert("BasicPreLoopSDLDaemon."s + name, preloop);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
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
  
private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLWindow> &sdlWindowRsrc = RsrcStore<SDLWindow>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<BasicPreLoopSDLDaemon> &preloopRsrc = RsrcStore<BasicPreLoopSDLDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_DAEMONS_BASICPRELOOPSDLDAEMONFTRY_H_
