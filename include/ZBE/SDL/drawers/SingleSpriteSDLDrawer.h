/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2017-04-05
 * @author degryll
 * @brief Class that know how to draw SingleSprite entities with SDL.
 */

#ifndef CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/entities/avatars/SingleSprite.h"
#include "ZBE/SDL/system/Window.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class SingleSpriteSDLDrawer : public Drawer<SingleSprite> {
  public:
    SingleSpriteSDLDrawer(const SingleSpriteSDLDrawer&) = delete;
    void operator=(const SingleSpriteSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    SingleSpriteSDLDrawer(Window* window) : window(window) {}

    /** \brief Destructor.
     */
    ~SingleSpriteSDLDrawer() {}

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    void apply(AvatarEntity<SingleSprite> *entity);

  private:
    Window* window;  //!< A SDL window with its context.
};

}  // namespace zbe

#endif  // CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
