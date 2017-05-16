#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

namespace zbe {

void BasicPreLoopSDLDaemon::run(){
  BasicPreLoopSDLDaemon::window->clear();
  sdlEventDist.run();
}

}
