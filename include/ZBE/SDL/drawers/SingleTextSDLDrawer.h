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
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class ZBEAPI SingleTextSDLDrawer : public Behavior<SingleTextSprite> {
  public:
    SingleTextSDLDrawer(const SingleTextSDLDrawer&) = delete; //!< Avoid copy.
    void operator=(const SingleTextSDLDrawer&) = delete; //!< Avoid copy.

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    SingleTextSDLDrawer(std::shared_ptr<SDLWindow> window)
      : window(window), textFontStore(window->getFontStore()) {}

    /** \brief Destructor.
     */
    ~SingleTextSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<AvatarEntityContainer<SingleTextSprite> > entity);

  private:
    std::shared_ptr<SDLWindow> window;  //!< A SDL window with its context.
    std::shared_ptr<SDLTextFontStore> textFontStore; //!< Where the images are stored.
};

}  // namespace zbe

#endif  // ZBE_SDL_DRAWERS_SIMPLETEXTSDLDRAWER_H_
