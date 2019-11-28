/**
 * Copyright 2015 Batis Degryll Ludo
 * @file IOPreLoopSDL.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis
 * @brief Daemon that runs before the main loop.
 * at the beginning of every frame:
 * Clears the window and captures SDL events.
 */

#ifndef ZBE_SDL_DAEMONS_IOPRELOOPSDL_H_
#define ZBE_SDL_DAEMONS_IOPRELOOPSDL_H_

#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include "ZBE/core/system/system.h"

namespace zbe {
  /** \brief
   */
  class ZBEAPI IOPreLoopSDL : public Daemon {
    public:

      IOPreLoopSDL(const IOPreLoopSDL&) = delete; //!< Avoid copy.
      void operator=(const IOPreLoopSDL&) = delete; //!< Avoid copy.

      /** \brief Empty constructor.
       */
      IOPreLoopSDL() : sdlEventDist(zbe::SDLEventDispatcher::getInstance()) {}

      /** \brief Destroys the IOPreLoopSDL
       */
      virtual ~IOPreLoopSDL() {}

      /** \brief Runs the daemon.
       */
      void run();

    private:
      zbe::SDLEventDispatcher& sdlEventDist;
  };

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_IOPRELOOPSDL_H_
