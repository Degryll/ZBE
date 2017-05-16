
#include "ZBE/core/daemons/BasicPreLoopTimeDaemon.h"

namespace zbe {

void BasicPreLoopTimeDaemon::run(){
  BasicPreLoopTimeDaemon::sysTime.update();
}

}
