/**
 * Copyright 2011 Batis Degryll Ludo
 * @file SDLWindowDaemon.cpp
 * @since 2019-03-19
 * @date 2019-03-19
 * @author Ludo Degryll Batis
 * @brief Daemon that generates a SDLWindow.
 */

#include "ZBE/SDL/daemons/SDLWindowDaemon.h"

namespace zbe {

void SDLWindowDaemon::run(){
  SDLWindowDaemon::window->clear();
  sdlEventDist.run();
}

}  // namespace zbe
