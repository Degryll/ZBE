/*
 * Copyright 2010 Batis Degryll Ludo
 * @file SDL_Starter.h
 *
 * @since 2010/07/06
 * @date 2014/09/25
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
    static SDL_Starter* createInstance() {return (_instance = new SDL_Starter);}
    static void         deleteInstance() {delete _instance;}
    static SDL_Starter* getInstance()    {return (_instance);}

    bool addSubsystem(Uint32 flags);
    SDL_Surface* createWindow(const char* title, int x, int y, int w, int h, Uint32 flags);
    void destroyWindow() {SDL_DestroyWindow(window);}

    SDL_Window* getWindow() {return window;}
    SDL_Surface* getSurface() {return s;}

  private:
    static SDL_Starter* _instance;

    SDL_Window* window;
    SDL_Surface* s;

    SDL_Starter() {}
};

}  // namespace zbe

#endif  // SRC_SDL_SDL_STARTER_H_
