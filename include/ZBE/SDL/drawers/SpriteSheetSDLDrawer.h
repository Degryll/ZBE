/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SpriteSheetSDLDrawer.h
 * @since 2017-06-15
 * @date 2017-06-15
 * @author Ludo
 * @brief Class that know how to draw using SpriteSheets.
 */

#ifndef SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_
#define SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_

#include <SDL2/SDL.h>

#include "ZBE/core/drawers/Drawer.h"

#include "ZBE/core/tools/containers/ResourceManager.h"
#include "ZBE/core/tools/graphics/SpriteSheet.h"

#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLImageStore.h"

namespace zbe {

/** \brief Class that know how to draw using SpriteSheets.
 */
template<typename T>
class SpriteSheetSDLDrawer : public Drawer<T> {
  public:
    SpriteSheetSDLDrawer(const SpriteSheetSDLDrawer&) = delete;
    void operator=(const SpriteSheetSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    SpriteSheetSDLDrawer(SDLWindow* window, SDLImageStore* imgStore)
      : window(window), imgStore(imgStore), rmss(ResourceManager<SpriteSheet<T> >::getInstance()) {}

    /** \brief Destructor.
     */
    ~SpriteSheetSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(AvatarEntity<T> *entity);

  private:
    SDLWindow* window;  //!< A SDL window with its context.
    SDLImageStore* imgStore; //!< Where the images are stored.
    ResourceManager<SpriteSheet<T> >& rmss;
};

}  // namespace zbe

#endif  // SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_
