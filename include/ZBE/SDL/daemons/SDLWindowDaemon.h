/**
 * Copyright 2015 Batis Degryll Ludo
 * @file SDLWindowDaemon.h
 * @since 2019-03-19
 * @date 2019-03-19
 * @author Degryll
 * @brief Daemon that generates a SDLWindow.
 */

#ifndef ZBE_SDL_DAEMONS_SDLWINDOWDAEMON_H_
#define ZBE_SDL_DAEMONS_SDLWINDOWDAEMON_H_

#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include "ZBE/core/system/system.h"

namespace zbe {
  /** \brief
   */
  class ZBEAPI SDLWindowDaemon : public Daemon {
    public:

      SDLWindowDaemon(const BasicPreLoopSDLDaemon&) = delete; //!< Avoid copy.
      void operator=(const SDLWindowDaemon&) = delete; //!< Avoid copy.

      /** \brief Empty constructor.
       */
      SDLWindowDaemon() :  {}

      /** \brief Runs the daemon.
       */
      void run();
    private:
      std::shared_ptr<zbe::SDLWindow> window;
      zbe::SDLEventDispatcher& sdlEventDist;
  };

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_SDLWINDOWDAEMON_H_
