/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2017-05-11
 * @author Degryll Ludo
 * @brief Class that know how to draw SingleSprite entities with SDL.
 */

#ifndef SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/SingleSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLImageStore.h"


namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class SingleSpriteSDLDrawer : public Behavior<SingleSprite> {
  public:
    SingleSpriteSDLDrawer(const SingleSpriteSDLDrawer&) = delete;
    void operator=(const SingleSpriteSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    SingleSpriteSDLDrawer(SDLWindow* window, SDLImageStore* imgStore) : window(window), imgStore(imgStore) {}

    /** \brief Destructor.
     */
    ~SingleSpriteSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntityContainer<SingleSprite> > entity);

  private:
    SDLWindow* window;  //!< A SDL window with its context.
    SDLImageStore* imgStore; //!< Where the images are stored.
};

}  // namespace zbe

#endif  // SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_
