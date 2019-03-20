/**
 * Copyright 2011 Batis Degryll Ludo
 * @file SDLOGLWindowDaemon.cpp
 * @since 2018-03-28
 * @date 2018-03-28
 * @author Ludo Degryll Batis
 * @brief Daemon that generates a SDLOGLWindow.
 */

#include "ZBE/SDL/daemons/SDLOGLWindowDaemon.h"

#include <memory>

namespace zbe {

void SDLOGLWindowDaemon::run(){
  auto w = std::make_shared<SDLOGLWindow>(title, x, y, width, height, window_flags, renderer_flags);
  rs.insert(name, w);
}

}  // namespace zbe
