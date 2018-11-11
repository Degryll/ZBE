/**
 * Copyright 2015 Batis Degryll Ludo
 * @file MainLoopExit.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Ludo Batis Degryll
 * @brief Daemon capable of end a MainLoop
 */

#ifndef zBE_CORE_DAEMONS_MAINLOOPEXIT_H
#define zBE_CORE_DAEMONS_MAINLOOPEXIT_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/MainLoop.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Daemon capable of end a MainLoop
 */
class MainLoopExit : virtual public Daemon {
public:

  /** \brief Builds an empty MainLoopExit.
   */
  MainLoopExit() : mainLoop(nullptr), value(nullptr), exitValue(0) {}

  /** \brief Builds a MainLoopExit from its raw data.
   * \param mainLoop main loop to end.
   * \param value Value where exit value will be saved.
   * \param exitValue value to save.
   */
  MainLoopExit(std::shared_ptr<MainLoop> mainLoop, std::shared_ptr< Value<int64_t> > value, int64_t exitValue)
    : mainLoop(mainLoop), value(value), exitValue(exitValue) {}

  /** \brief Virtual destructor.
   */
  ~MainLoopExit() {}

  void setMainLoop(std::shared_ptr<MainLoop> mainLoop){
    this->mainLoop = mainLoop;
  }

  void setValue(std::shared_ptr< Value<int64_t> > value){
    this->value = value;
  }

  void setExitValue(int64_t exitValue){
    this->exitValue = exitValue;
  }

  /** \brief End MainLoop and save given value.
   */
  void run() {
    value->set(exitValue);
    mainLoop->stop();
  }

private:
  std::shared_ptr<MainLoop> mainLoop;
  std::shared_ptr< Value<int64_t> > value;
  int64_t exitValue;
};

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_MAINLOOPEXIT_H
