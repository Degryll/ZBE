/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSpriteSDLDrawer.h
 * @since 2017-04-12
 * @date 2017-04-12
 * @author batis
 * @brief Class that know how to draw text boxes as SingleTextSprite entities with SDL.
 */

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

  window->render(avatar->graphics, avatar->text, &src, &dst);
    //window->render((uint64_t)0, &src, &dst);
}

}  // namespace zbe
