#include "ZBE/core/system/MainLoop.h"


#include <iostream>//--------------------


namespace zbe {

void MainLoop::loop() {

  keep = true;
  while(keep){
    //Pre daemon
    dPre->run();
    // Inner loop
    while (sysTime.isFrameRemaining()) {
      // Timed events daemon (gema)
      dTE->run();
      sysTime.setEventTime(store.getTime());
      if (sysTime.isPartialFrame()) {
        // commonBehaviorMaster
        dCBM->run();
        store.manageCurrent();
        // reactBehaviorMaster
        dRBM->run();
      } else {
        // commonBehaviorMaster
        dCBM->run();
        store.clearStore();
      }
      sysTime.updateInitTime();
    }
    //Post daemon
    dDM->run();
    dPost->run();
    // end
  }
}

}
