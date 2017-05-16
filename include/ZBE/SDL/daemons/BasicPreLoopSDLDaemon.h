/**
 * Copyright 2015 Batis Degryll Ludo
 * @file
 * @since 2017-05-11
 * @date 2017-05-11
 * @author Batis
 * @brief
 */

#ifndef CORE_DAEMONS_BASICPRELOOPSLDDAEMON_H_
#define CORE_DAEMONS_BASICPRELOOPSLDDAEMON_H_

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/Window.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

namespace zbe {
  /** \brief
   */
  class BasicPreLoopSDLDaemon : public Daemon {
    public:

      BasicPreLoopSDLDaemon(const BasicPreLoopSDLDaemon&) = delete;
      void operator=(const BasicPreLoopSDLDaemon&) = delete;

      BasicPreLoopSDLDaemon(zbe::Window* window): window(window), sdlEventDist(zbe::SDLEventDispatcher::getInstance()) {}

      /** \brief Destroys the BasicPreLoopSDLDaemon
       */
      virtual ~BasicPreLoopSDLDaemon() {}

      /** \brief Runs the daemon.
       */
      void run();
    private:
      zbe::Window* window;
      zbe::SDLEventDispatcher& sdlEventDist;
  };
}  // namespace zbe


#endif // CORE_DAEMONS_BASICPRELOOPSLDDAEMON_H_
