/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2016-03-29
 * @author degryll
 * @brief Class that know how to draw SimpleSprite entities with SDL.
 */

#include "ZBE/core/drawers/SDL/SimpleSpriteSDLDrawer.h"

namespace zbe {

void SimpleSpriteSDLDrawer::apply(SimpleSprite *entity) {
  SDL_Rect src,dst;
  src.x = 0;
  src.y = 0;
  src.w = entity.getWidth();
  src.h = entity.getHeight();

  dst.x = entity.getLeftX();
  dst.y = entity.getTopY();
  dst.w = entity.getWidth();
  dst.h = entity.getHeight();
  window->render(entity.getImage(), &src, &dst);
}

}  // namespace zbe
