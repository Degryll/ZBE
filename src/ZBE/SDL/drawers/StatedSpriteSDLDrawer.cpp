/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author degryll
 * @brief Class that know how to draw StatedSprite entities with SDL.
 */

#include "ZBE/SDL/drawers/StatedSpriteSDLDrawer.h"

namespace zbe {

void StatedSpriteSDLDrawer::apply(std::shared_ptr<AvatarEntity<StatedSprite> > entity) {
  StatedSprite* avatar;
  entity->assignAvatar(&avatar);
  SDL_Rect src,dst;
  src.x = avatar->w * avatar->state;
  src.y = avatar->h * avatar->state;
  src.w = avatar->w;
  src.h = avatar->h;

  dst.x = avatar->x;
  dst.y = avatar->y;
  dst.w = avatar->w;
  dst.h = avatar->h;
  SDL_Point p;
  p.x = avatar->x + avatar->w / 2;
  p.y = avatar->y + avatar->h / 2;
  window->render(imgStore->getTexture(avatar->graphics), &src, &dst, avatar->degrees, &p);
}

}  // namespace zbe
