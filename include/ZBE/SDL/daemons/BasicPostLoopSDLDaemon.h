/**
 * Copyright 2015 Batis Degryll Ludo
 * @file
 * @since 2017-05-11
 * @date 2017-05-11
 * @author Batis
 * @brief
 */

#ifndef CORE_DAEMONS_BASICPOSTLOOPSDLDAEMON_H_
#define CORE_DAEMONS_BASICPOSTLOOPSDLDAEMON_H_

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/Window.h"

namespace zbe {
  /** \brief
   */
  class BasicPostLoopSDLDaemon : public Daemon {
    public:

      BasicPostLoopSDLDaemon(const BasicPostLoopSDLDaemon&) = delete;
      void operator=(const BasicPostLoopSDLDaemon&) = delete;

      BasicPostLoopSDLDaemon(zbe::Window* window): window(window) {}

      /** \brief Destroys the BasicPostLoopSDLDaemon
       */
      ~BasicPostLoopSDLDaemon() {}

      /** \brief Runs the daemon.
       */
      void run();
    private:
      zbe::Window* window;
  };
}  // namespace zbe


#endif // CORE_DAEMONS_BASICPOSTLOOPSDLDAEMON_H_
