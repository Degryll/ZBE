/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.h
 * @since 2016-04-27
 * @date 2018-03-28
 * @author Ludo Batis Degryll
 * @brief Dispatcher for sdl events.
 */

#include "ZBE/SDL/system/SDLNetDispatcher.h"

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/io/InputStatus.h"

namespace zbe {

SDLNetDispatcher::~SDLNetDispatcher() {
  sdl.quitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS);
}

void SDLNetDispatcher::run() {
  int numready=SDLNet_CheckSockets(sset, 0);
  uint64_t sequence;
  std::vector<char> msg;

//  if(numready==-1) {
//    printf("SDLNet_CheckSockets: %s\n",SDLNet_GetError());
//    break;
//  }
  auto it = sockets.begin();
  while(it != sockets.end() && numready > 0) {
    if (it->isReady()) {
      it->getMsg(sequence, msg);
      NetMessage nm(sequence,*it, msg, contextTime->getInitFrameTime() + zbe::TIME_QUANTUM);
      netBuffer->insert(nm);
      numready--;
    }
    it++;
  }  // while numready
}

}  // namespace zbe
