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
  src.x = avatar->getW() * avatar->getState();
  src.y = avatar->getH() * avatar->getState();
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
