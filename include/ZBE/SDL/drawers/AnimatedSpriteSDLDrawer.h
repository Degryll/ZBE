/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2016-03-29
 * @author degryll
 * @brief Class that know how to draw SimpleSprite entities with SDL.
 */

#ifndef CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/entities/avatars/SimpleSprite.h"
#include "ZBE/SDL/system/Window.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class AnimatedSpriteSDLDrawer : public Drawer<SimpleSprite> {
  public:
    AnimatedSpriteSDLDrawer(const AnimatedSpriteSDLDrawer&) = delete;
    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    AnimatedSpriteSDLDrawer(Window* window) : window(window) {}

    /** \brief Destructor.
     */
    ~AnimatedSpriteSDLDrawer() {}

    void operator=(const AnimatedSpriteSDLDrawer&) = delete;

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    void apply(AvatarEntity<SimpleSprite> *entity);

  private:
    Window* window;  //!< A SDL window with its context.
};

}  // namespace zbe

#endif  // CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
