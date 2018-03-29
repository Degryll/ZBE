/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MainLoop.cpp
 * @since 2018-03-27
 * @date 2018-03-27
 * @author Batis Degryll Ludo
 * @brief Daemon that executes a main game loop.
 */

#include "ZBE/core/system/MainLoop.h"

#include <iostream>

namespace zbe {

void MainLoop::run() {

  keep = true;
  while(keep) {  // Each iteration generates a frame.
    // Pre daemon
    dPre->run();
    // Inner loop
    while (sysTime.isFrameRemaining()) {
      // Timed events generator daemon
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
    }  // while frame remaining
    // Drawer daemon
    dDM->run();
    // Post daemon
    dPost->run();
    // end
  }  // while keep
}

}  // namespace zbe
