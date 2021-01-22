/**
 * Copyright 2016 Batis Degryll Ludo
 * @file NetEventGenerator.cpp
 * @since 2018-08-16
 * @date 2018-08-16
 * @author Degryll
 * @brief Network event generator.
 */

#include "ZBE/core/events/generators/NetEventGenerator.h"

namespace zbe {

void NetEventGenerator::run() {
  std::vector<NetMessage> msgs;
  netBuffer->getFirstInRange(contextTime->getInitFrameTime(), contextTime->getEndFrameTime(), msgs);
  for(auto msg : msgs) {
    SDLSocket s = msg.getSocket();
    NetEvent* e = new NetEvent(eventId, msg.getTime(), msg.getSequence(), s, msg.getMsg(), s.getHandler());
    store.storeEvent(e);
  } // for each currentInput
}

}  // namespace zbe
