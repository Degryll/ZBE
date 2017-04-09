/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSpriteSDLDrawer.cpp
 * @since 2012-02-01
 * @date 2016-03-29
 * @author degryll
 * @brief Class that know how to draw SimpleSprite entities with SDL.
 */

#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"

namespace zbe {

void SingleSpriteSDLDrawer::apply(std::shared_ptr<AvatarEntity<SingleSprite> > entity) {
  SingleSprite* avatar;
  entity->assignAvatar(&avatar);
  SDL_Rect src,dst;
  src.x = 0;
  src.y = 0;
  src.w = avatar->w;
  src.h = avatar->h;

  dst.x = avatar->x;
  dst.y = avatar->y;
  dst.w = avatar->w;
  dst.h = avatar->h;
  window->render(avatar->graphics, &src, &dst);
}

}  // namespace zbe
