/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author degryll
 * @brief Class that know how to draw AnimatedSprite entities with SDL.
 */

#ifndef CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/SDL/system/Window.h"

namespace zbe {

/** \brief This draws a sprite in any direction using different animations.
 */
class AnimatedSpriteSDLDrawer : public Drawer<AnimatedSprite> {
  public:
    AnimatedSpriteSDLDrawer(const AnimatedSpriteSDLDrawer&) = delete;
    void operator=(const AnimatedSpriteSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    AnimatedSpriteSDLDrawer(Window* window) : window(window) {}

    /** \brief Destructor.
     */
    ~AnimatedSpriteSDLDrawer() {}

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntity<AnimatedSprite> > entity);

  private:
    Window* window;  //!< A SDL window with its context.
};

}  // namespace zbe

#endif  // CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
