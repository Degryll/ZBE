/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2016-03-29
 * @author degryll
 * @brief Class that know how to draw SimpleSprite entities with SDL.
 */

#ifndef CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/archetypes/SimpleSprite.h"
#include "ZBE/core/system/SDL/Window.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class SimpleSpriteSDLDrawer : public Drawer<SimpleSprite> {
  public:
    SimpleSpriteSDLDrawer(const SimpleSpriteSDLDrawer&) = delete;
    /** \brief Create a new drawer in the given context.
     *  \param window A SDL window with its context.
     */
    SimpleSpriteSDLDrawer(Window* window) : window(window) {}

    /** \brief Destructor.
     */
    ~SimpleSpriteSDLDrawer() {}

    operator=(const SimpleSpriteSDLDrawer&) = delete;

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    void apply(SimpleSprite *entity);

  private:
    Window* window;  //!< A SDL window with its context.
};

}  // namespace zbe

#endif  // CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
