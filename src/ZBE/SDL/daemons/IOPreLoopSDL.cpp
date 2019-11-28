/**
 * Copyright 2011 Batis Degryll Ludo
 * @file IOPreLoopSDL.cpp
 * @since 2019-10-24
 * @date 2019-10-24
 * @author Ludo Degryll Batis
 * @brief Daemon that runs before the main loop.
 * at the beginning of every frame:
 * Clears the window and captures SDL events.
 */

#include "ZBE/SDL/daemons/IOPreLoopSDL.h"

namespace zbe {

void IOPreLoopSDL::run(){
  sdlEventDist.run();
}

}  // namespace zbe
