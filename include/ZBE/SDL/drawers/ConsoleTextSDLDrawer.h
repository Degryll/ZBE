/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ConsoleTextDrawer.h
 * @since 2017-04-12
 * @date 2018-02-25
 * @author Batis Ludo Degryll
 * @brief class ZBEAPI that know how to draw text boxes as SingleTextSprite entities with SDL.
 */

#ifndef ZBE_SDL_DRAWERS_CONSOLETEXTSDLDRAWER_H_
#define ZBE_SDL_DRAWERS_CONSOLETEXTSDLDRAWER_H_

#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class ConsoleTextDrawer : public Behavior<uint64_t, std::string, int64_t, std::vector<std::string> > {
  public:
    ConsoleTextDrawer(const ConsoleTextDrawer&) = delete; //!< Avoid copy.
    void operator=(const ConsoleTextDrawer&) = delete; //!< Avoid copy.

    /** \brief Empty constructor.
     */
    ConsoleTextDrawer()
      : window(nullptr), textFontStore(nullptr){}

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    ConsoleTextDrawer(std::shared_ptr<SDLWindow> window)
      : window(window), textFontStore(window->getFontStore()) {}

    /** \brief Destructor.
     */
    ~ConsoleTextDrawer() {}

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
    void apply(std::shared_ptr<MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > > avatar) override {
      using namespace std::string_literals;

      auto fid = avatar->get<4, uint64_t>()->get();
      auto vc = avatar->get<3, std::string>()->get();
      auto vl = avatar->get<2, int64_t>()->get();
      auto vh = avatar->get<1, std::vector<std::string> >()->get();

//      // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
//      if (show_demo_window)
//        ImGui::ShowDemoWindow(&show_demo_window);


      int ini = std::max(0ll, vl - 10ll);
      int fin = vl;
      int posy = 0;

      for(int i = ini; i < fin; i++) {
        renderText(fid, ">> "s + vh[i], posy);
      }

      renderText(fid, ">> "s + vc, posy);
    }

  protected:
    void renderText(uint64_t fid, std::string text, int& posy) {
      int w = 0;
      int h = 0;
      SDL_Texture* t = textFontStore->renderText(fid, text.c_str());
      SDL_QueryTexture(t, 0, 0, &w, &h);
      SDL_Rect dst = {0, posy, w, h};
      posy += h;
      window->render(t, nullptr, &dst);
      SDL_DestroyTexture(t);
    }

  private:
    std::shared_ptr<SDLWindow> window;  //!< A SDL window with its context.
    std::shared_ptr<SDLTextFontStore> textFontStore; //!< Where the images are stored.

    bool show_demo_window = true;
};

}  // namespace zbe

#endif  // ZBE_SDL_DRAWERS_CONSOLETEXTSDLDRAWER_H_
