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

  /** \brief Virtual Destructor.
   */
  virtual ~SingleSprite() {};

  /** \brief Returns x.
   *  \return x.
   */
  virtual int64_t getX() = 0;

  /** \brief Returns y.
   *  \return y.
   */
  virtual int64_t getY() = 0;

  /** \brief Returns w.
   *  \return w.
   */
  virtual int64_t getW() = 0;

  /** \brief Returns h.
   *  \return h.
   */
  virtual int64_t getH() = 0;

  /** \brief Returns graphics.
   *  \return graphics.
   */
  virtual int64_t getGraphics() = 0;

  /** \brief Sets x.
   *  \param x value for the x attribute
   */
  virtual void setX(int64_t x) = 0;

  /** \brief Sets y.
   *  \param y value for the y attribute
   */
  virtual void setY(int64_t y) = 0;

  /** \brief Sets w.
   *  \param w value for the w attribute
   */
  virtual void setW(int64_t w) = 0;

  /** \brief Sets h.
   *  \param h value for the h attribute
   */
  virtual void setH(int64_t h) = 0;

  /** \brief Sets graphics.
    *  \param graphics value for the graphics attribute
   */
  virtual void setGraphics(uint64_t graphics) = 0;

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_
