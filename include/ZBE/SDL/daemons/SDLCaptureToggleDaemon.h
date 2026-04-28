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

#ifndef ZBE_SDL_CAPTURETOGGLEDAEMON_H_
#define ZBE_SDL_CAPTURETOGGLEDAEMON_H_

#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

#include "ZBE/core/system/system.h"

namespace zbe {
/** \brief
 */
class ZBEAPI SDLCaptureToggleDaemon : public Daemon {
  public:

    SDLCaptureToggleDaemon(const SDLCaptureToggleDaemon&) = delete; //!< Avoid copy.
    void operator=(const SDLCaptureToggleDaemon&) = delete; //!< Avoid copy.

    /** \brief Empty constructor.
     */
    SDLCaptureToggleDaemon() {}

    /** \brief Destroys the SDLCaptureToggleDaemon
     */
    virtual ~SDLCaptureToggleDaemon() = default;

    /** \brief Runs the daemon.
     */
    void run() override {
      capture = !capture;
      SDL_CaptureMouse(capture ? SDL_FALSE : SDL_TRUE);
      SDL_SetRelativeMouseMode(capture ? SDL_FALSE : SDL_TRUE);
    };
  private:
    bool capture = false;
};

}  // namespace zbe

#endif  // ZBE_SDL_CAPTURETOGGLEDAEMON_H_
