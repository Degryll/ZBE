/*
 * Copyright 2010 Batis Degryll Ludo
 * @file SDL_Starter.h
 *
 * @since 2010/07/06
 * @date 2015/05/28
 * @author Degryll
 * @brief Implements SDL_Starter class.
 */

#ifndef SRC_SDL_SDL_STARTER_H_
#define SRC_SDL_SDL_STARTER_H_

#include <SDL2/SDL.h>

namespace zbe {

/**
 * @class SDL_Starter
 * @brief Used to init SDL subsystems only once.
 */
class SDL_Starter {
  public:
    SDL_Starter(SDL_Starter const&)    = delete;  //!< Needed for singleton.
    void operator=(SDL_Starter const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation to start SDL subsystems.
     *  \return The only instance of the SDL_Starter.
     */
    static SDL_Starter& getInstance(Uint32 flags) {
      static SDL_Starter instance;
      SDL_InitSubSystem(flags);
      return (instance);
    }

    void quit() {SDL_Quit();}  //!< Call SDL_Quit.

    void quitSubSystem(Uint32 flags) {
      SDL_QuitSubSystem(flags);
    }

  private:
    SDL_Starter() {SDL_Init(0);}  //!< Call SDL_Init(0).
};

}  // namespace zbe

#endif  // SRC_SDL_SDL_STARTER_H_