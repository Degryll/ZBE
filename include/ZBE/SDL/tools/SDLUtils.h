/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLUtils.h
 * @since 2017-06-18
 * @date 2017-06-18
 * @author Ludo Degryll Batis
 * @brief Utility funtions for SDL;
 */

#ifndef ZBE_SDL_TOOLS_SDLUTILS_H_
#define ZBE_SDL_TOOLS_SDLUTILS_H_

#include "ZBE/SDL/sdl_warning_suppressor.h"

namespace zbe {

/** \brief Converts a zbe::Region2D into a SDL_Rect.
 */
inline SDL_Rect convert2SDLRect(const Region2D& region2d) {
  SDL_Rect rect;
  rect.x = static_cast<int>(region2d.p.x);
  rect.y = static_cast<int>(region2d.p.y);
  rect.w = static_cast<int>(region2d.v.x);
  rect.h = static_cast<int>(region2d.v.y);
  return (rect);
}

}  // namespace zbe

#endif  // ZBE_SDL_TOOLS_SDLUTILS_H_
