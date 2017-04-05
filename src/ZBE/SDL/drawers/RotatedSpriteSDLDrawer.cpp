/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author degryll
 * @brief Class that know how to draw RotatedSprite entities with SDL.
 */

#include "ZBE/SDL/drawers/RotatedSpriteSDLDrawer.h"

namespace zbe {

void RotatedSpriteSDLDrawer::apply(AvatarEntity<RotatedSprite> *entity) {
  RotatedSprite* avatar;
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
  SDL_Point p;
  p.x = avatar->x + avatar->w / 2;
  p.y = avatar->y + avatar->h / 2;
  window->render(avatar->graphics, &src, &dst, avatar->degrees, p);
}

}  // namespace zbe
