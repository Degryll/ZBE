/**
 * Copyright 2011 Batis Degryll Ludo
 * @file SDLWindowDaemon.cpp
 * @since 2019-03-19
 * @date 2019-03-19
 * @author Ludo Degryll Batis
 * @brief Daemon that generates a SDLWindow.
 */

#include "ZBE/SDL/daemons/SDLWindowDaemon.h"

#include <memory>

#include "ZBE/core/tools/containers/RsrcStore.h"

namespace zbe {

void SDLWindowDaemon::run(){
  auto w = std::make_shared<SDLWindow>(title, x, y, width, height, window_flags, renderer_flags);
  auto& rs = zbe::RsrcStore<SDLWindow>::getInstance();
  rs.insert(name, w);
}

}  // namespace zbe
