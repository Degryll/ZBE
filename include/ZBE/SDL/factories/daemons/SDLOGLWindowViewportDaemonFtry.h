/**
 * Copyright 2026 Batis Degryll Ludo
 * @file SDLOGLWindowViewportDaemonFtry.h
 * @brief Factory for SDLOGLWindowViewportDaemon.
 */

#ifndef ZBE_SDL_FACTORIES_DAEMONS_SDLOGLWINDOWVIEWPORTDAEMONFTRY_H_
#define ZBE_SDL_FACTORIES_DAEMONS_SDLOGLWINDOWVIEWPORTDAEMONFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/SDL/daemons/SDLOGLWindowViewportDaemon.h"

namespace zbe {

class SDLOGLWindowViewportDaemonFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto daemon = std::make_shared<SDLOGLWindowViewportDaemon>();
    daemonRsrc.insert("Daemon."s + name, daemon);
    specificRsrc.insert("SDLOGLWindowViewportDaemon."s + name, daemon);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;

    auto config = configRsrc.get(cfgId);
    if (!config || !config->is_object() ||
        !config->contains("window") || !(*config)["window"].is_string()) {
      SysError::setError("SDLOGLWindowViewportDaemonFtry requires a string window setting for " + name + ".");
      return;
    }

    const std::string windowName = (*config)["window"].get<std::string>();
    const std::string windowResource = "SDLOGLWindow."s + windowName;

    if (!windowRsrc.contains(windowResource)) {
      SysError::setError("SDLOGLWindowViewportDaemonFtry window not found: " + windowResource);
      return;
    }

    auto window = windowRsrc.get(windowResource);
    auto daemon = specificRsrc.get("SDLOGLWindowViewportDaemon."s + name);
    if (!window || !daemon) {
      SysError::setError("SDLOGLWindowViewportDaemonFtry resources are invalid for " + name + ".");
      return;
    }

    daemon->setWindow(window);
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<SDLOGLWindowViewportDaemon>& specificRsrc = RsrcStore<SDLOGLWindowViewportDaemon>::getInstance();
  RsrcStore<SDLOGLWindow>& windowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_SDL_FACTORIES_DAEMONS_SDLOGLWINDOWVIEWPORTDAEMONFTRY_H_
