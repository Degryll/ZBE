/*
 * Copyright 2010 Batis Degryll Ludo
 * @file SDL_ttf_Starter.h
 *
 * @since 2017/03/13
 * @date 2017/03/13
 * @author Degryll, Batis
 * @brief Implements SDL_ttf_Starter class.
 */

#ifndef ZBE_MAIN_BATIS_STARTERS_SDL_TTF_STARTER_H_
#define ZBE_MAIN_BATIS_STARTERS_SDL_TTF_STARTER_H_

#include <SDL2/SDL.h>

namespace zbe {

/**
 * @class SDL_ttf_Starter
 * @brief Used to init SDL_ttf only once.
 */
class SDL_ttf_Starter {
  public:
    SDL_ttf_Starter(SDL_ttf_Starter const&)    = delete;  //!< Needed for singleton.
    void operator=(SDL_ttf_Starter const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation to start SDL_ttf.
     *  \return The only instance of the SDL_ttf_Starter.
     */
    static SDL_ttf_Starter& getInstance() {
      static SDL_ttf_Starter instance;
      return (instance);
    }

    void quit() {TTF_Quit();}  //!< Call SDL_Quit.

  private:
    SDL_ttf_Starter() {TTF_Init();}  //!< Call SDL_Init(0).
};

}  // namespace zbe

#endif  // ZBE_MAIN_BATIS_STARTERS_SDL_TTF_STARTER_H_
