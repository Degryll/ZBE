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
 * @brief Used to init SDL subsystems only once (alonelton).
 */
class SDL_Starter {
  public:
    static SDL_Starter* createInstance(Uint32 flags = 0);
    static void         deleteInstance() {SDL_Quit(); delete _instance;}
    static SDL_Starter* getInstance()    {return (_instance);}

    bool addSubsystem(Uint32 flags);

  private:
    static SDL_Starter* _instance;

    SDL_Starter() {}
};

}  // namespace zbe

#endif  // SRC_SDL_SDL_STARTER_H_
