/**
 * Copyright 2026 Batis Degryll Ludo
 * @file SDLOGLWindowViewportDaemon.h
 * @brief Synchronizes an OpenGL window's resolution after SDL window events.
 */

#ifndef ZBE_SDL_DAEMONS_SDLOGLWINDOWVIEWPORTDAEMON_H_
#define ZBE_SDL_DAEMONS_SDLOGLWINDOWVIEWPORTDAEMON_H_

#include <cstdint>
#include <memory>
#include <utility>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"

namespace zbe {

class ZBEAPI SDLOGLWindowViewportDaemon : public Daemon {
public:
  SDLOGLWindowViewportDaemon() : window(nullptr) {}

  void setWindow(std::shared_ptr<SDLOGLWindow> value) {
    window = std::move(value);
  }

  void run() override {
    if (!window) {
      SysError::setError("SDLOGLWindowViewportDaemon requires a configured window.");
      return;
    }

    window->updateResolutionFromWindow();
  }

private:
  std::shared_ptr<SDLOGLWindow> window;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_SDLOGLWINDOWVIEWPORTDAEMON_H_
