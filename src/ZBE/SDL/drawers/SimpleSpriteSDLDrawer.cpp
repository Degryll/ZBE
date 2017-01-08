/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2016-03-29
 * @author degryll
 * @brief Class that know how to draw SimpleSprite entities with SDL.
 */

#include "ZBE/SDL/drawers/SimpleSpriteSDLDrawer.h"

namespace zbe {

void SimpleSpriteSDLDrawer::apply(Drawable *entity) {
  SDL_Rect src,dst;
  src.x = 0;
  src.y = 0;
  src.w = entity->w;
  src.h = entity->h;

  dst.x = entity->x;
  dst.y = entity->y;
  dst.w = entity->w;
  dst.h = entity->h;
  window->render(entity->img, &src, &dst);
}

}  // namespace zbe
