/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSpriteSDLDrawer.h
 * @since 2017-04-12
 * @date 2017-10-11
 * @author batis ludo
 * @brief class ZBEAPI that know how to draw text boxes as SingleTextSprite entities with SDL.
 */

#include <SDL2/SDL.h>

#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"

namespace zbe {

void SingleTextSDLDrawer::apply(std::shared_ptr<AvatarEntityContainer<SingleTextSprite> > entity) {
  SingleTextSprite* avatar;
  assignAvatar(entity, &avatar);
  SDL_Texture* t = textFontStore->renderText(avatar->getGraphics(), avatar->getText().c_str());

  int tw, th, aw, ah;
  SDL_QueryTexture(t, NULL,NULL, &tw, &th);
  SDL_Rect src,dst;
  aw = (int)avatar->getW();
  ah = (int)avatar->getH();
  src.w = std::min(tw,aw);
  src.h = std::min(th,ah);
  dst.w = src.w;
  dst.h = src.h;
  src.x = 0;
  src.y = 0;
  dst.x = (int)avatar->getX() + (aw - dst.w);
  dst.y = (int)avatar->getY() + (ah - dst.h);

  window->render(t, &src, &dst);
  SDL_DestroyTexture(t);
}

}  // namespace zbe
