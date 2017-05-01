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

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/entities/avatars/StatedSprite.h"
#include "ZBE/SDL/system/Window.h"

namespace zbe {

/** \brief This draws a sprite in any direction using different images.
 */
class StatedSpriteSDLDrawer : public Drawer<StatedSprite> {
  public:
    StatedSpriteSDLDrawer(const StatedSpriteSDLDrawer&) = delete;
    void operator=(const StatedSpriteSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    StatedSpriteSDLDrawer(Window* window) : window(window) {}

    /** \brief Destructor.
     */
    ~StatedSpriteSDLDrawer() {}

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntity<StatedSprite> > entity);

  private:
    Window* window;  //!< A SDL window with its context.
};

}  // namespace zbe

#endif  // CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
