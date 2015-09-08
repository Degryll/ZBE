#include "ZBE/core/daemons/DaemonMaster.h"

namespace zbe {

    DaemonMaster::DaemonMaster():daemonList(0) {
      daemonList = new std::vector<Daemon>();
    }

    DaemonMaster::~DaemonMaster() {
      if(daemonList){
        delete daemonList;
      }
    }

    void DaemonMaster::run(){
      for(auto it = daemonList->begin(); it < daemonList->end(); ++it) {
        it->run();
      }
    }

    void DaemonMaster::addDaemon(const Daemon &daemon){
        //daemonList->push_back(daemon);
    }

}
