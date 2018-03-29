/**
 * Copyright 2015 Batis Degryll Ludo
 * @file StateMachineDaemon.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief A Daemon capable of execute an specific sub Daemon depending on
 * an state.
 */

#include "ZBE/core/daemons/StateMachineDaemon.h"

namespace zbe {

void StateMachineDaemon::run(){
  while(state->getValue()>=0 && state->getValue() < static_cast<int64_t>(daemons.size()) ) {
    daemons[state->getValue()]->run();
  }
}

}  // namespace zbe
