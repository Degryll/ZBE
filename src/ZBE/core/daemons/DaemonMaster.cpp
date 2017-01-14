#include "ZBE/core/daemons/DaemonMaster.h"

namespace zbe {

void DaemonMaster::run(uint64_t time){
  for(auto it = daemonList.begin(); it < daemonList.end(); ++it) {
    (*it)->run(time);
  }
}

}
