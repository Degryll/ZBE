/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SpriteSheetSDLDrawer.h
 * @since 2017-06-15
 * @date 2018-02-25
 * @author Ludo
 * @brief class ZBEAPI that know how to draw using SpriteSheets.
 */

#ifndef ZBE_SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_
#define ZBE_SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_

#include <memory>
#include <cstdint>

#include <SDL2/SDL.h>

#include "ZBE/core/behaviors/Behavior.h"



#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/graphics/SpriteSheet.h"

#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/SDL/tools/SDLUtils.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief class that know how to draw using SpriteSheets.
 */
template<unsigned idx, typename T, typename ...Ts>
class SpriteSheetSDLDrawer : public Behavior<T, Ts...> {
  public:
    SpriteSheetSDLDrawer(const SpriteSheetSDLDrawer&) = delete; //!< Avoid copy.
    void operator=(const SpriteSheetSDLDrawer&) = delete; //!< Avoid copy.

    /** \brief Empty constructor.
     */
    SpriteSheetSDLDrawer()
      : window(nullptr), imgStore(nullptr), rmss(RsrcStore<SpriteSheet<T, Ts...> >::getInstance()) {}

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    SpriteSheetSDLDrawer(std::shared_ptr<SDLWindow> window)
      : window(window), imgStore(window->getImgStore()), rmss(RsrcStore<SpriteSheet<T, Ts...> >::getInstance()) {}

    /** \brief Destructor.
     */
    ~SpriteSheetSDLDrawer() {}

    /** \brief sets the window, imgStore and rmss.
     *  \param window A SDLwindow with its context.
     */
    void setWindow(std::shared_ptr<SDLWindow> window) {
      this->window = window;
      imgStore = window->getImgStore();
    }

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<MAvatar<T, Ts...> > avatar) override{
      std::shared_ptr<_Avatar<idx, uint64_t> > av = avatar;
      auto val = av->get();
      uint64_t gId = val->get();

      std::shared_ptr<SpriteSheet<T, Ts...> > sst = rmss.get(gId);

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
    RsrcStore<SpriteSheet<T, Ts...> >& rmss; //!< Resource manager instance.
};

}  // namespace zbe

#endif  // ZBE_SDL_DRAWERS_SPRITESHEETSDLDRAWER_H_
