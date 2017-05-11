/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleTextDrawer.h
 * @since 2017-04-12
 * @date 2017-05-11
 * @author Batis Ludo
 * @brief Class that know how to draw text boxes as SingleTextSprite entities with SDL.
 */

#ifndef SDL_DRAWERS_SIMPLETEXTSDLDRAWER_H_
#define SDL_DRAWERS_SIMPLETEXTSDLDRAWER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/SDL/system/Window.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class SingleTextSDLDrawer : public Drawer<SingleTextSprite> {
  public:
    SingleTextSDLDrawer(const SingleTextSDLDrawer&) = delete;
    void operator=(const SingleTextSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    SingleTextSDLDrawer(Window* window) : window(window) {}

    /** \brief Destructor.
     */
    ~SingleTextSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntity<SingleTextSprite> > entity);

  private:
    Window* window;  //!< A SDL window with its context.
};

}  // namespace zbe

#endif  // SDL_DRAWERS_SIMPLETEXTSDLDRAWER_H_
