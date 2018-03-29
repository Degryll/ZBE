/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SpriteSheetSDLDrawer.h
 * @since 2017-06-15
 * @date 2018-02-25
 * @author Ludo
 * @brief Class that know how to draw using SpriteSheets.
 */

#ifndef ZBE_SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_
#define ZBE_SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_

#include <memory>
#include <SDL2/SDL.h>

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/tools/containers/ResourceManager.h"
#include "ZBE/core/tools/graphics/SpriteSheet.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/tools/SDLUtils.h"

namespace zbe {

/** \brief Class that know how to draw using SpriteSheets.
 */
template<typename T>
class SpriteSheetSDLDrawer : public Behavior<T> {
  public:
    SpriteSheetSDLDrawer(const SpriteSheetSDLDrawer&) = delete; //!< Avoid copy.
    void operator=(const SpriteSheetSDLDrawer&) = delete; //!< Avoid copy.

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    SpriteSheetSDLDrawer(std::shared_ptr<SDLWindow> window)
      : window(window), imgStore(window->getImgStore()), rmss(ResourceManager<SpriteSheet<T> >::getInstance()) {}

    /** \brief Destructor.
     */
    ~SpriteSheetSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntityContainer<T> > entity) {
      T* avatar;
      assignAvatar(entity, &avatar);
      std::shared_ptr<SpriteSheet<T> > sst = rmss.get(avatar->getGraphics());
      Sprite s = sst->generateSprite(avatar);

      SDL_Rect src = convert2SDLRect(s.src);
      SDL_Rect dst = convert2SDLRect(s.dst);

      SDL_Point p;
      p.x = s.dst.p.x + (s.dst.v.x / 2);
      p.y = s.dst.p.y + (s.dst.v.y / 2);
      window->render(imgStore->getTexture(s.g), &src, &dst, s.a, &p);
    }

  private:
    std::shared_ptr<SDLWindow> window;  //!< A SDL window with its context.
    std::shared_ptr<SDLImageStore> imgStore; //!< Where the images are stored.
    ResourceManager<SpriteSheet<T> >& rmss; //!< Resource manager instance.
};

}  // namespace zbe

#endif  // ZBE_SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_
