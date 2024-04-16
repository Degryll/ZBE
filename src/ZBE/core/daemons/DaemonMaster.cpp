/**
 * Copyright 2015 Batis Degryll Ludo
 * @file DaemonMaster.cpp
 * @since 2015-05-04
 * @date 2018-03-26
 * @author Ludo Degryll Batis
 * @brief A Daemon capable of run other Daemons.
 */

#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

void DaemonMaster::run(){
  for(auto it = daemonList.begin(); it != daemonList.end(); ++it) {
    (*it)->run();
  }
}

}  // namespace zbe
