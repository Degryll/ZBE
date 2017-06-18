/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SpriteSheetSDLDrawer.h
 * @since 2017-06-18
 * @date 2017-06-18
 * @author Ludo Degryll Batis
 * @brief Class that know how to draw AnimatedSprite entities with SDL.
 */

#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"

#include <memory>

#include "ZBE/SDL/tools/SDLUtils.h"

namespace zbe {

template <typename T>
void SpriteSheetSDLDrawer<T>::apply(AvatarEntity<T> *entity) {
  T* avatar;
  entity->assignAvatar(&avatar);
  std::shared_ptr<SpriteSheet<T> > sst = rmss.get(avatar->getGraphics());
  Sprite s = sst->generateSprite(avatar);

  SDL_Rect src = convert2SDLRect(s.src);
  SDL_Rect dst = convert2SDLRect(s.dst);

  SDL_Point p;
  p.x = s.dst.p.x + (s.dst.v.x / 2);
  p.y = s.dst.p.y + (s.dst.v.y / 2);
  window->render(imgStore->getTexture(s.g), &src, &dst, s.a, &p);
}

}  // namespace zbe
