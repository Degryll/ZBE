/**
 * Copyright 2015 Batis Degryll Ludo
 * @file MainLoopExit.h
 * @since 2015-05-04
 * @date 2015-12-09
 * @author Ludo
 * @brief Define the minimal functions of demons.
 */

#ifndef CORE_DAEMONS_MAINLOOPEXIT_H
#define CORE_DAEMONS_MAINLOOPEXIT_H

#include <memory>
#include <cstdint>

#include "ZBE/core/system/MainLoop.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class MainLoopExit : virtual public Daemon {
public:

  MainLoopExit(std::shared_ptr<MainLoop> mainLoop, std::shared_ptr< Value<int64_t> > value, int64_t exitValue)
    : mainLoop(mainLoop), value(value), exitValue(exitValue) {}

  ~MainLoopExit() {}

  void run() {
    value->setValue(exitValue);
    mainLoop->stop();
  }

private:
  std::shared_ptr<MainLoop> mainLoop;
  std::shared_ptr< Value<int64_t> > value;
  int64_t exitValue;
};

}  // namespace zbe

#endif // CORE_DAEMONS_MAINLOOPEXIT_H
