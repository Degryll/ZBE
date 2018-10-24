/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author degryll
 * @brief class ZBEAPI that know how to draw RotatedSprite entities with SDL.
 */

#include "ZBE/SDL/drawers/RotatedSpriteSDLDrawer.h"

namespace zbe {

void RotatedSpriteSDLDrawer::apply(AvatarEntityContainer<RotatedSprite> *entity) {
  RotatedSprite* avatar;
  assignAvatar(entity, &avatar);
  SDL_Rect src,dst;
  src.x = 0;
  src.y = 0;
  src.w = avatar->getW();
  src.h = avatar->getH();

  dst.x = avatar->getX();
  dst.y = avatar->getY();
  dst.w = avatar->getW();
  dst.h = avatar->getH();
  SDL_Point p;
  p.x = avatar->getX() + avatar->getW() / 2;
  p.y = avatar->getY() + avatar->getH() / 2;
  window->render(imgStore->getTexture(avatar->getGraphics()), &src, &dst, avatar->getDegrees(), &p);
}

}  // namespace zbe
