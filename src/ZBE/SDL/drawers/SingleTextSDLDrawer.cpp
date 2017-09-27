/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSpriteSDLDrawer.h
 * @since 2017-04-12
 * @date 2017-10-11
 * @author batis ludo
 * @brief Class that know how to draw text boxes as SingleTextSprite entities with SDL.
 */

#include <SDL2/SDL.h>

#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"

namespace zbe {

void SingleTextSDLDrawer::apply(std::shared_ptr<AvatarEntityContainer<SingleTextSprite> > entity) {
  SingleTextSprite* avatar;
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
  SDL_Texture* t = textFontStore->renderText(avatar->getGraphics(), avatar->getText().c_str());
  window->render(t, &src, &dst);
  SDL_DestroyTexture(t);
}

}  // namespace zbe
