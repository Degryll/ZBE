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

SDL_Starter* SDL_Starter::createInstance(Uint32 flags) {
  if (SDL_Init(flags) != 0) {
    zbe::SysError::setError("SDL ERROR: SDL could not initialize!");
    // añadir al mensaje de error SDL_GetError()
  }
  return (_instance = new SDL_Starter);
}

/**
 * @fn bool SDL_Starter::addSubsystem(Uint32 flags)
 * @brief Initiates the SDL subsystem if it's not already initiated
 * @param flags Uint32. A integer with the necessary flags to initiate SDL.
 * @return if any errors occur, it returns true, else, false.
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

}  // namespace zbe
