/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Sprite.h
 * @since 2017-06-14
 * @date 2017-06-14
 * @author Degryll Ludo Batis
 * @brief Structure representing from where and where to draw a graphic element.
 */

#ifndef ZBE_CORE_TOOLS_GRAPHICS_SPRITE_H_
#define ZBE_CORE_TOOLS_GRAPHICS_SPRITE_H_

#include <stdint.h>

namespace zbe {

/** \brief Structure representing from where and where to draw a graphic element.
 */
struct Sprite {

  /** \brief Builds a Sprite with all its needed data.
   *
   *  \param srcX Source x coord
   *  \param srcY Source y coord
   *  \param srcW Source width
   *  \param srcH Source height
   *  \param dstX destiny x coord
   *  \param dstY destiny y coord
   *  \param dstW destiny width
   *  \param dstH destiny height
   *  \param angle destiny angle rotation
   *  \param graphics Graphic resource id
   */
  Sprite(int64_t srcX, int64_t srcY, int64_t srcW, int64_t srcH, int64_t dstX, int64_t dstY, int64_t dstW, int64_t dstH, double angle, uint64_t graphics) : sx(srcX), sy(srcY), sw(srcW), sh(srcH), dx(dstX), dy(dstY), dw(dstW), dh(dstH), a(angle), g(graphics) {};

  int64_t sx; //!< Source x coord
  int64_t sy; //!< Source y coord
  int64_t sw; //!< Source width
  int64_t sh; //!< Source height
  int64_t dx; //!< destiny x coord
  int64_t dy; //!< destiny y coord
  int64_t dw; //!< destiny width
  int64_t dh; //!< destiny height
  double a;   //!< destiny angle rotation
  uint64_t g; //!< Graphic resource id

};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_GRAPHICS_SPRITE_H_
