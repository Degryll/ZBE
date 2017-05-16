
#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"

namespace zbe {

void BasicPostLoopSDLDaemon::run(){
  window->present();
}

}
