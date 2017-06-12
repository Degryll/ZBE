/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSprite.h
 * @since 2016-11-22
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an avatar that can be drawn.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_

namespace zbe {

/** \brief This define an avatar that can be drawn.
 */
class SingleSprite {

public:

  using Base = void;

  //SingleSprite() {}

  /** \brief Parametrized Constructor.
  *  \param x X coordinate (horizontal).
  *  \param y Y coordinate (vertical).
  *  \param w Width.
  *  \param h height.
  *  \param graphics Index for the image in the store.
  */
  SingleSprite (int64_t x = 0, int64_t y = 0, int64_t w = 0, int64_t h = 0, uint64_t graphics = 0) :
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

#endif  // ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_
