/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteSDLDrawer.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Test drawers for ludo's proving grounds.
 */

#ifndef ZBE_MAIN_LUDO_DRAWERS_LUDODRAWERS
#define ZBE_MAIN_LUDO_DRAWERS_LUDODRAWERS

#include <SDL2/SDL.h>

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/entities/avatars/SimpleSprite.h"
#include "ZBE/SDL/system/Window.h"

#include "ludo/entities/LudoAvatars.h"

namespace ludo {

/** \brief This draws a simple sprite (an image).
 */
class SimpleRotatedSpriteSDLDrawer : public zbe::Drawer<SimpleRotatedSprite> {
  public:
    SimpleRotatedSpriteSDLDrawer(const SimpleRotatedSpriteSDLDrawer&) = delete;
    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    SimpleRotatedSpriteSDLDrawer(zbe::Window* window) : window(window) {}

    /** \brief Destructor.
     */
    ~SimpleRotatedSpriteSDLDrawer() {}

    void operator=(const SimpleRotatedSpriteSDLDrawer&) = delete;

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    void apply(SimpleRotatedSprite *entity) {
      SDL_Rect src,dst;
      src.x = 0;
      src.y = 0;
      src.w = entity->w;
      src.h = entity->h;

      dst.x = entity->x;
      dst.y = entity->y;
      dst.w = entity->w;
      dst.h = entity->h;
      SDL_Point center = {dst.x + (dst.w / 2), dst.y + (dst.h / 2)};
      window->render(entity->graphics, &src, &dst, entity->angle, &center, SDL_FLIP_NONE);
    }

  private:
    zbe::Window* window;  //!< A SDL window with its context.
};

}  // namespace

#endif  // ZBE_MAIN_LUDO_DRAWERS_LUDODRAWERS