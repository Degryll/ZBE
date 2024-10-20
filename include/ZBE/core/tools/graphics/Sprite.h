/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Sprite.h
 * @since 2017-06-14
 * @date 2018-03-25
 * @author Degryll Ludo Batis
 * @brief Structure representing from where and where to draw a graphic element.
 */

#ifndef ZBE_CORE_TOOLS_GRAPHICS_SPRITE_H_
#define ZBE_CORE_TOOLS_GRAPHICS_SPRITE_H_

#include <cstdint>

#include "ZBE/core/tools/math/Region.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Structure representing from where and where to draw a graphic element.
 */
struct ZBEAPI Sprite {

  /** \brief Builds a Sprite with all its needed data.
   *
   *  \param src Source region
   *  \param dst Destiny region
   *  \param angle destiny angle rotation
   *  \param graphics Graphic resource id
   */
  Sprite(Region2D src, Region2D dst, double angle, uint64_t graphics) : src(src), dst(dst), a(angle), g(graphics) {};

  Region2D src; //!< Source region
  Region2D dst; //!< Destiny region
  double a;   //!< Destiny angle rotation
  uint64_t g; //!< Graphic resource id

};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_GRAPHICS_SPRITE_H_
