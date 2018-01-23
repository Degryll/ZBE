#include "ZBE/core/daemons/StateMachineDaemon.h"

namespace zbe {

void StateMachineDaemon::run(){
  while(state->getValue()>=0 && state->getValue() < static_cast<int64_t>(daemons.size()) ) {
    daemons[state->getValue()]->run();
  }
}

}
