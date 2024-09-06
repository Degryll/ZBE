/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSpriteSDLDrawer.cpp
 * @since 2012-02-01
 * @date 2016-03-29
 * @author degryll
 * @brief class ZBEAPI that know how to draw SimpleSprite entities with SDL.
 */

#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"

namespace zbe {

void SingleSpriteSDLDrawer::apply(std::shared_ptr<MAvatar<uint64_t, Vector2D, Vector2D> > avatar) {
  auto vgid = AvtUtil::get<3, uint64_t>(avatar);
  auto vsize = AvtUtil::get<2, Vector2D >(avatar);
  auto vpos = AvtUtil::get<1, Vector2D >(avatar);

  SDL_Rect src,dst;
  src.x = 0;
  src.y = 0;
  src.w = static_cast<int>(vsize->get().x);
  src.h = static_cast<int>(vsize->get().y);

  dst.x = static_cast<int>(vpos->get().x);
  dst.y = static_cast<int>(vpos->get().y);
  dst.w = static_cast<int>(vsize->get().x);
  dst.h = static_cast<int>(vsize->get().y);
  window->render(imgStore->getTexture(vgid->get()), &src, &dst);
}

}  // namespace zbe
