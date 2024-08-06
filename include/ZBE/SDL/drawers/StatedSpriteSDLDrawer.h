/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2018-02-25
 * @author degryll
 * @brief class ZBEAPI that know how to draw StatedSprite entities with SDL.
 */

#ifndef ZBE_SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define ZBE_SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include <memory>
#include <SDL2/SDL.h>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/StatedSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This draws a sprite in any direction using different images.
 */
class ZBEAPI StatedSpriteSDLDrawer : public Behavior<StatedSprite> {
  public:
    StatedSpriteSDLDrawer(const StatedSpriteSDLDrawer&) = delete; //!< Avoid copy.
    void operator=(const StatedSpriteSDLDrawer&) = delete; //!< Avoid copy.

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    StatedSpriteSDLDrawer(SDLWindow* window, SDLImageStore* imgStore) : window(window), imgStore(imgStore) {}

    /** \brief Destructor.
     */
    ~StatedSpriteSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntityContainer<StatedSprite> > entity) override;

  private:
    SDLWindow* window;  //!< A SDL window with its context.
    SDLImageStore* imgStore; //!< Where the images are stored.
};

}  // namespace zbe

#endif  // ZBE_SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_
