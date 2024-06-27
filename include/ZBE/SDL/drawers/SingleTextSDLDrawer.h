/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleTextDrawer.h
 * @since 2017-04-12
 * @date 2018-02-25
 * @author Batis Ludo Degryll
 * @brief class ZBEAPI that know how to draw text boxes as SingleTextSprite entities with SDL.
 */

#ifndef ZBE_SDL_DRAWERS_SIMPLETEXTSDLDRAWER_H_
#define ZBE_SDL_DRAWERS_SIMPLETEXTSDLDRAWER_H_

#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class ZBEAPI SingleTextSDLDrawer : public Behavior<std::string, uint64_t, Vector2D, Vector2D> {
  public:
    SingleTextSDLDrawer(const SingleTextSDLDrawer&) = delete; //!< Avoid copy.
    void operator=(const SingleTextSDLDrawer&) = delete; //!< Avoid copy.

    /** \brief Empty constructor.
     */
    SingleTextSDLDrawer()
      : window(nullptr), textFontStore(nullptr){}

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    SingleTextSDLDrawer(std::shared_ptr<SDLWindow> window)
      : window(window), textFontStore(window->getFontStore()) {}

    /** \brief Destructor.
     */
    ~SingleTextSDLDrawer() {}

    /** \brief sets the window, imgStore and rmss.
     *  \param window A SDLwindow with its context.
     */
    void setWindow(std::shared_ptr<SDLWindow> window) {
      this->window = window;
      textFontStore = window->getFontStore();
    }

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<MAvatar<std::string, uint64_t, Vector2D, Vector2D> > avatar) override{
      SDL_Texture* t = textFontStore->renderText(avatar->get<3, uint64_t>()->get(), avatar->get<4, std::string>()->get().c_str());

      int tw, th, aw, ah;
      SDL_QueryTexture(t, NULL,NULL, &tw, &th);
      SDL_Rect src,dst;
      auto dim = avatar->get<2, Vector2D>()->get();
      aw = (int)dim.x;
      ah = (int)dim.y;
      src.w = std::min(tw,aw);
      src.h = std::min(th,ah);
      dst.w = src.w;
      dst.h = src.h;
      src.x = 0;
      src.y = 0;
      auto pos = avatar->get<1, Vector2D>()->get();
      dst.x = (int)pos.x + (aw - dst.w);
      dst.y = (int)pos.y + (ah - dst.h);

      window->render(t, &src, &dst);
      SDL_DestroyTexture(t);
    }

  private:
    std::shared_ptr<SDLWindow> window;  //!< A SDL window with its context.
    std::shared_ptr<SDLTextFontStore> textFontStore; //!< Where the images are stored.
};

}  // namespace zbe

#endif  // ZBE_SDL_DRAWERS_SIMPLETEXTSDLDRAWER_H_
