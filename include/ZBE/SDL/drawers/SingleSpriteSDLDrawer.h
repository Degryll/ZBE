/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief class ZBEAPI that know how to draw SingleSprite entities with SDL.
 */

#ifndef SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include <memory>
#include <SDL3/SDL.h>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/SingleSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/SDL/system/SDLWindow.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This draws a simple sprite (an image).
 */
class ZBEAPI SingleSpriteSDLDrawer : public Behavior<uint64_t, Vector2D, Vector2D> {
  public:
    SingleSpriteSDLDrawer(const SingleSpriteSDLDrawer&) = delete; //!< Avoid copy.
    void operator=(const SingleSpriteSDLDrawer&) = delete; //!< Avoid copy.

    /** \brief Create a new drawer in the given context.
     *  \param window A SDLwindow with its context.
     */
    SingleSpriteSDLDrawer(std::shared_ptr<SDLWindow> window) : window(window), imgStore(window->getImgStore()) {}

    /** \brief Destructor.
     */
    ~SingleSpriteSDLDrawer() {}

    /** \brief Draws the given entity.
     *  \param The entity to be drawn.
     */
    void apply(std::shared_ptr<MAvatar<uint64_t, Vector2D, Vector2D> > avatar) override;

  private:
    std::shared_ptr<SDLWindow> window;  //!< A SDL window with its context.
    std::shared_ptr<SDLImageStore> imgStore; //!< Where the images are stored.
};

}  // namespace zbe

#endif  // SDL_DRAWERS_SIMPLESPRITESDLDRAWER_H_
