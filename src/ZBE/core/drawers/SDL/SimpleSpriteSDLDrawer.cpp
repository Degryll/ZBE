/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2014-09-27
 * @author degryll
 * @brief Class that know how to draw ball Entities
 *        for the game ZombieBall.
 */

#include "ZBE/core/drawers/SDL/SimpleSpriteSDLDrawer.h"

namespace zbe {

void SimpleSpriteSDLDrawer::draw() {
  SDL_Rect src,dst;
  src.x = 0;
  src.y = 0;
  for(auto it = firstSS; it != endSS; ++it) {
    SimpleSprite& entitie = *it;
    src.w = entitie.getWidth();
    src.h = entitie.getHeight();

    dst.x = entitie.getLeftX();
    dst.y = entitie.getTopY();
    dst.w = entitie.getWidth();
    dst.h = entitie.getHeight();
    window.render(entitie.getImage(),&src,&dst);
  }
}

}  // namespace zbe
