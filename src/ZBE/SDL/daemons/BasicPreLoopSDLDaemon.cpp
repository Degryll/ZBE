/**
 * Copyright 2011 Batis Degryll Ludo
 * @file BasicPreLoopSDLDaemon.cpp
 * @since 2018-03-28
 * @date 2018-03-28
 * @author Ludo Degryll Batis
 * @brief Daemon that runs before the main loop.
 * at the beginning of every frame:
 * Clears the window and captures SDL events.
 */

#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

namespace zbe {

void BasicPreLoopSDLDaemon::run(){
  BasicPreLoopSDLDaemon::window->clear();
  sdlEventDist.run();
}

}  // namespace zbe
