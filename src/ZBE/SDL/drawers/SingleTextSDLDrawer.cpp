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

void SingleTextSDLDrawer::apply(std::shared_ptr<AvatarEntity<SingleTextSprite> > entity) {
  SingleTextSprite* avatar;
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
  SDL_Texture* t = textFontStore->renderText(avatar->graphics, avatar->text);
  window->render(t, &src, &dst);
  SDL_DestroyTexture(t);
}

}  // namespace zbe
