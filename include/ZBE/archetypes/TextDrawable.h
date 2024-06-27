/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedDrawable.h
 * @since 2017-04-05
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief This define an entity that can be drawn in any direction with different animations.
 */

#ifndef ZBE_ARCHETYPES_TEXTDRAWABLE_H_
#define ZBE_ARCHETYPES_TEXTDRAWABLE_H_

#include <string>

#include <SDL3_ttf/SDL_ttf.h>

#include "ZBE/archetypes/Drawable.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an entity that can be drawn in any direction.
 */
class ZBEAPI TextDrawable : virtual public Drawable {
public:
  /** \brief Virtual destructor.
   */
  virtual ~TextDrawable() {}

  /** \brief Gets the text.
   *  \return Return string text.
   */
  virtual const std::string& getText() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_TEXTDRAWABLE_H_
