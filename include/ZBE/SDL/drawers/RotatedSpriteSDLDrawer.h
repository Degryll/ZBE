/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedSpriteSDLDrawer.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author degryll
 * @brief Class that know how to draw RotatedSprite entities with SDL.
 */

#ifndef CORE_DRAWERS_ROTATEDPRITESDLDRAWER_H_
#define CORE_DRAWERS_ROTATEDPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/entities/avatars/RotatedSprite.h"
#include "ZBE/SDL/system/Window.h"

namespace zbe {

/** \brief This draws a sprite (an image) in any direction.
 */
class RotatedSpriteSDLDrawer : public Drawer<RotatedSprite> {
  public:
    RotatedSpriteSDLDrawer(const RotatedSpriteSDLDrawer&) = delete;
    void operator=(const RotatedSpriteSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    RotatedSpriteSDLDrawer(Window* window) : window(window) {}

    /** \brief Destructor.
     */
    ~RotatedSpriteSDLDrawer() {}

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    void apply(AvatarEntity<RotatedSprite> *entity);

  private:
    Window* window;  //!< A SDL window with its context.
};

}  // namespace zbe

#endif  // CORE_DRAWERS_ROTATEDPRITESDLDRAWER_H_
