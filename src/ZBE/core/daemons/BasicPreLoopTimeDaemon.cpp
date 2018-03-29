/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BasicPreLoopTimeDaemon.cpp
 * @since 2017-05-11
 * @date 2018-03-27
 * @author Batis Degryll Ludo
 * @brief Basic daemon to use in pre-loop.
 */

#include "ZBE/core/daemons/BasicPreLoopTimeDaemon.h"

namespace zbe {

void BasicPreLoopTimeDaemon::run(){
  sysTime.update();
}

}  // namespace zbe
