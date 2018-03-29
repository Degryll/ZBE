/**
 * Copyright 2011 Batis Degryll Ludo
 * @file BasicPostLoopSDLDaemon.cpp
 * @since 2018-03-28
 * @date 2018-03-28
 * @author Ludo Degryll Batis
 * @brief Daemon that runs after the main loop.
 * at the end of every frame:
 * Shows the window (if there is double buffer, swap it).
 */

#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"

namespace zbe {

void BasicPostLoopSDLDaemon::run(){
  window->present();
}

}  // namespace zbe
