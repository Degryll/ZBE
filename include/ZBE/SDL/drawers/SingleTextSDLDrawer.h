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

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLTextFontStore.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class SingleTextSDLDrawer : public Behavior<SingleTextSprite> {
  public:
    SingleTextSDLDrawer(const SingleTextSDLDrawer&) = delete;
    void operator=(const SingleTextSDLDrawer&) = delete;

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    SingleTextSDLDrawer(std::shared_ptr<SDLWindow> window, std::shared_ptr<SDLTextFontStore> textFontStore) : window(window), textFontStore(textFontStore) {}

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

#endif  // SDL_DRAWERS_SIMPLETEXTSDLDRAWER_H_
