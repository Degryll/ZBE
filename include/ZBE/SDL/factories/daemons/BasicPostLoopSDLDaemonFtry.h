/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BasicPostLoopSDLDaemonFtry.h
 * @since 2019-07-23
 * @date 2019-07-23
 * @author Degryll
 * @brief Factory for BasicPostLoopSDLDaemon.
 */

#ifndef ZBE_SDL_FACTORIES_DAEMONS_BASICPOSTLOOPSDLDAEMONFTRY_H_
#define ZBE_SDL_FACTORIES_DAEMONS_BASICPOSTLOOPSDLDAEMONFTRY_H_

#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for BasicPostLoopSDLDaemonFtry.
 */
class BasicPostLoopSDLDaemonFtry : virtual public Factory {
public:

  /** \brief Builds a BasicPostLoopSDLDaemon.
   *  \param name Name for the created BasicPostLoopSDLDaemon.
   *  \param cfgId BasicPostLoopSDLDaemon's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto postloop = std::make_shared<BasicPostLoopSDLDaemon>();
    daemonRsrc.insert("Daemon."s + name, postloop);
    postloopRsrc.insert("BasicPostLoopSDLDaemon."s + name, postloop);
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

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLWindow> &sdlWindowRsrc = RsrcStore<SDLWindow>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<BasicPostLoopSDLDaemon> &postloopRsrc = RsrcStore<BasicPostLoopSDLDaemon>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_DAEMONS_BASICPOSTLOOPSDLDAEMONFTRY_H_
