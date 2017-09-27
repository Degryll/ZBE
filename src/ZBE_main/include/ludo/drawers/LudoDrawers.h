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

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/SingleSprite.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLImageStore.h"

#include "ludo/entities/LudoAvatars.h"

namespace ludo {

/** \brief This draws a simple sprite (an image).
 */
class SimpleRotatedSpriteSDLDrawer : public zbe::Behavior<zbe::RotatedSprite> {
  public:
    SimpleRotatedSpriteSDLDrawer(const SimpleRotatedSpriteSDLDrawer&) = delete;
    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    SimpleRotatedSpriteSDLDrawer(zbe::SDLWindow* window, zbe::SDLImageStore* imgStore) : window(window), imgStore(imgStore) {}

    /** \brief Destructor.
     */
    ~SimpleRotatedSpriteSDLDrawer() {}

    void operator=(const SimpleRotatedSpriteSDLDrawer&) = delete;

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    void apply(std::shared_ptr<zbe::AvatarEntityContainer<zbe::RotatedSprite> > entity) {
      zbe::RotatedSprite* avatar;
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
      SDL_Point center = {src.w / 2, src.h/2 };
      window->render(imgStore->getTexture(avatar->getGraphics()), &src, &dst, (avatar->getDegrees() * -1) + 90 , &center, SDL_FLIP_NONE);
    }

  private:
    zbe::SDLWindow* window;  //!< A SDL window with its context.
    zbe::SDLImageStore* imgStore; //!< Where the images are stored.
};

}  // namespace

#endif  // ZBE_MAIN_LUDO_DRAWERS_LUDODRAWERS
