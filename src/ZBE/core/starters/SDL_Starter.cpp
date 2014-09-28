/*
 * Copyright 2011 Batis Degryll Ludo
 * @file SDL_Starter.cpp
 *
 * @since 2010/07/06
 * @date 2014/09/25
 * @author Degryll
 * @brief Implements SDL_Starter class.
 */

#include "ZBE/core/starters/SDL_Starter.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

SDL_Starter* SDL_Starter::_instance = NULL;

/**
 * @fn bool SDL_Starter::addSubsystem(Uint32 flags)
 * @brief Initiates the SDL subsystem if it's not already initiated
 * @param flags Uint32. A integer with the necessary flags to initiate SDL.
 * @return if no errors occur, it returns true, else, false.
 */
bool SDL_Starter::addSubsystem(Uint32 flags) {
  Uint32 f = SDL_WasInit(0);

  if (f == 0) {
    if (SDL_Init(flags) != 0) {
      zbe::SysError::setError("SDL ERROR: SDL could not initialize!");
      return (true);
    }
  } else if ((flags & f) != flags) {
    if (SDL_InitSubSystem(flags) != 0) {
      zbe::SysError::setError("SDL ERROR: Could not initialize subsystem!");
      return (true);
    }
  }
  return (false);
}

SDL_Surface* SDL_Starter::createWindow(const char* title, int x, int y, int w, int h, Uint32 flags) {
  window = SDL_CreateWindow( title, x, y, w, h, flags);
  if( window == NULL ) {
    zbe::SysError::setError("SDL ERROR: The window could not be created!");
  } else {
    s = SDL_GetWindowSurface(window);
  }
  return s;
}

}  // namespace zbe
