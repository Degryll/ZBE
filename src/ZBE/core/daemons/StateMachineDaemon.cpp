/**
 * Copyright 2015 Batis Degryll Ludo
 * @file StateMachineDaemon.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief A Daemon capable of execute an specific sub Daemon depending on
 * an state.
 */

#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

void StateMachineDaemon::run(){
  int64_t s = state->get();
  auto it = daemons.find(s);
  while(it != daemons.end()) {
    it->second->run();
    s = state->get();
    it = daemons.find(s);
  }
}

}  // namespace zbe
