/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedDrawable.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an entity that can be drawn in any direction with different animations.
 */

#ifndef ZBE_MAIN_BATIS_TEXTDRAWABLE_H_
#define ZBE_MAIN_BATIS_TEXTDRAWABLE_H_

#include <SDL2/SDL_ttf.h>

#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief This define an entity that can be drawn in any direction.
 */
class TextDrawable : virtual public Drawable {
  public:
    virtual ~TextDrawable() {}

    virtual const char* getText() = 0;
};

}  // namespace zbe

#endif  // ZBE_MAIN_BATIS_TEXTDRAWABLE_H_
