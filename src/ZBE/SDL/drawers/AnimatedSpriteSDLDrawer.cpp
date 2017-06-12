/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author degryll
 * @brief Class that know how to draw AnimatedSprite entities with SDL.
 */

#include "ZBE/SDL/drawers/AnimatedSpriteSDLDrawer.h"

namespace zbe {

void AnimatedSpriteSDLDrawer::apply(std::shared_ptr<AvatarEntity<AnimatedSprite> > entity) {/*
  AnimatedSprite* avatar;
  entity->assignAvatar(&avatar);
  int64_t w = avatar->getW()[avatar->getState()];
  int64_t h = avatar->getH()[avatar->getState()];

  SDL_Rect src,dst;
  src.x = w * avatar->frame;
  src.y = h * avatar->frame;
  src.w = w;
  src.h = h;

  dst.x = avatar->x;
  dst.y = avatar->y;
  dst.w = w;
  dst.h = h;
  SDL_Point p;
  p.x = avatar->x + w / 2;
  p.y = avatar->y + h / 2;
  window->render(imgStore->getTexture(avatar->graphics), &src, &dst, avatar->degrees, &p);*/
}

}  // namespace zbe
