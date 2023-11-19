/**
 * Copyright 2010 Batis Degryll Ludo
 * @file SDL_Starter.h
 *
 * @since 2010-07-06
 * @date 2018-02-25
 * @author Degryll Ludo
 * @brief Implements SDL_Starter class.
 */

#ifndef ZBE_SDL_STARTERS_STARTER_H_
#define ZBE_SDL_STARTERS_STARTER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#include "ZBE/core/system/system.h"

namespace zbe {

/**
 * @class SDL_Starter
 * @brief Used to init SDL subsystems only once.
 */
class ZBEAPI SDL_Starter {
public:
  SDL_Starter(SDL_Starter const&)    = delete;  //!< Needed for singleton.
  void operator=(SDL_Starter const&) = delete;  //!< Needed for singleton.

  static const Uint32 SDLNET = 1;

  /** \brief Singleton implementation to start SDL subsystems.
   *  \return The only instance of the SDL_Starter.
   */
  static SDL_Starter& getInstance(Uint32 flags = 0, Uint32 other = 0) {
    static SDL_Starter instance;
    SDL_InitSubSystem(flags);
    SDL_CaptureMouse(SDL_FALSE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    if (other & SDLNET) {
      SDLNet_Init();
      sdlnetrefs++;
    }
    return (instance);
  }

  /** \brief Shutdowns all SDL subsystems.
   */
  void quit() {SDL_Quit(); SDLNet_Quit();}  //!< Call SDL_Quit.

  /** \brief Shutdowns given SDL subsystem.
   */
  void quitSubSystem(Uint32 flags) {
    SDL_QuitSubSystem(flags);
  }

  /** \brief Shutdowns given SDL subsystem.
   */
  void quitOtherSystem(Uint32 flags) {
    if (flags & SDLNET) {
      sdlnetrefs--;
      if (!sdlnetrefs) SDLNet_Quit();
    }
  }

private:
  SDL_Starter() {SDL_Init(0); SDLNet_Init();}  //!< Call SDL_Init(0).

  static int sdlnetrefs;
};

}  // namespace zbe

#endif  // ZBE_SDL_STARTERS_STARTER_H_
