/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Class that know how to draw RotatedSprite entities with SDL.
 */

#ifndef ZBE_SDL_DRAWERS_ROTATEDPRITESDLDRAWER_H_
#define ZBE_SDL_DRAWERS_ROTATEDPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/RotatedSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/SDL/system/SDLWindow.h"

namespace zbe {

/** \brief This draws a sprite (an image) in any direction.
 */
class RotatedSpriteSDLDrawer : public Behavior<RotatedSprite> {
  public:
    RotatedSpriteSDLDrawer(const RotatedSpriteSDLDrawer&) = delete; //!< Avoid copy.
    void operator=(const RotatedSpriteSDLDrawer&) = delete; //!< Avoid copy.

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    RotatedSpriteSDLDrawer(SDLWindow* window, SDLImageStore* imgStore) : window(window), imgStore(imgStore) {}

    /** \brief Destructor.
     */
    ~RotatedSpriteSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(AvatarEntityContainer<RotatedSprite> *entity);

  private:
    SDLWindow* window;  //!< A SDL window with its context.
    SDLImageStore* imgStore; //!< Where the images are stored.
};

}  // namespace zbe

#endif  // ZBE_SDL_DRAWERS_ROTATEDPRITESDLDRAWER_H_
