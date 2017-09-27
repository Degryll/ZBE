/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author degryll
 * @brief Class that know how to draw StatedSprite entities with SDL.
 */

#ifndef CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/StatedSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLImageStore.h"

namespace zbe {

/** \brief This draws a sprite in any direction using different images.
 */
class StatedSpriteSDLDrawer : public Behavior<StatedSprite> {
  public:
    StatedSpriteSDLDrawer(const StatedSpriteSDLDrawer&) = delete;
    void operator=(const StatedSpriteSDLDrawer&) = delete;

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
    void apply(std::shared_ptr<AvatarEntityContainer<StatedSprite> > entity);

  private:
    SDLWindow* window;  //!< A SDL window with its context.
    SDLImageStore* imgStore; //!< Where the images are stored.
};

}  // namespace zbe

#endif  // CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
