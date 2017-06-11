/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2017-05-11
 * @author Degryll Ludo
 * @brief Class that know how to draw AnimatedSprite entities with SDL.
 */

#ifndef SDL_DRAWERS_ANIMATEDSPRITESDLDRAWER_H_
#define SDL_DRAWERS_ANIMATEDSPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLImageStore.h"

namespace zbe {

/** \brief This draws a sprite in any direction using different animations.
 */
class AnimatedSpriteSDLDrawer : public Drawer<AnimatedSprite> {
  public:
    AnimatedSpriteSDLDrawer(const AnimatedSpriteSDLDrawer&) = delete;
    void operator=(const AnimatedSpriteSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    AnimatedSpriteSDLDrawer(SDLWindow* window, SDLImageStore* imgStore) : window(window), imgStore(imgStore) {}

    /** \brief Destructor.
     */
    ~AnimatedSpriteSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntity<AnimatedSprite> > entity);

  private:
    SDLWindow* window;  //!< A SDL window with its context.
    SDLImageStore* imgStore; //!< Where the images are stored.
};

}  // namespace zbe

#endif  // SDL_DRAWERS_ANIMATEDSPRITESDLDRAWER_H_
