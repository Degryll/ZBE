/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSprite.h
 * @since 2016-11-22
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an avatar that can be drawn.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESINGLESPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESINGLESPRITE_H_

#include "ZBE/core/entities/avatars/SingleSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn.
 */
class SimpleSingleSprite : virtual public SingleSprite {

public:

  /** \brief Parametrized Constructor.
  *  \param x X coordinate (horizontal).
  *  \param y Y coordinate (vertical).
  *  \param w Width.
  *  \param h height.
  *  \param graphics Index for the image in the store.
  */
  SimpleSingleSprite (int64_t x, int64_t y , int64_t w , int64_t h , uint64_t graphics ) :
  x(x), y(y), w(w), h(h), graphics(graphics) {}

  /** \brief Returns x.
   *  \return x.
   */
  int64_t getX() {return x;}

  /** \brief Returns y.
   *  \return y.
   */
  int64_t getY() {return y;}

  /** \brief Returns w.
   *  \return w.
   */
  int64_t getW() {return w;}

  /** \brief Returns h.
   *  \return h.
   */
  int64_t getH() {return h;}

  /** \brief Returns graphics.
   *  \return graphics.
   */
  int64_t getGraphics() {return graphics;}

private:
  int64_t x; //!< X coordinate
  int64_t y; //!< Y coordinate
  int64_t w; //!< width
  int64_t h; //!< height
  uint64_t graphics;    //!< Image index

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESINGLESPRITE_H_
