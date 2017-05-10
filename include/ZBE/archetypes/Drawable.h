/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Drawable.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief This define an entity that can be drawn.
 */

#ifndef ZBE_ARCHETYPES_DRAWABLE_H_
#define ZBE_ARCHETYPES_DRAWABLE_H_

#include <cstdint>

namespace zbe {

/** \brief This define an entity that can be drawn.
 */
class Drawable {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Drawable() {}

  /** \brief Gets the left coordinate.
   *  \return The left coordinate.
   *  \sa setX, getY, getW, getH, getGraphics
   */
  virtual int64_t getX() = 0;

  /** \brief Gets the top coordinate.
   *  \return The top coordinate.
   *  \sa setY, getX, getW, getH, getGraphics
   */
  virtual int64_t getY() = 0;

  /** \brief Gets the width of the image.
   *  \return The width of the image.
   *  \sa setW, getX, getY, getH, getGraphics
   */
  virtual int64_t getW() = 0;

  /** \brief Gets the height of the image.
   *  \return The height of the image.
   *  \sa setH, getX, getY, getW, getGraphics
   */
  virtual int64_t getH() = 0;

  /** \brief Gets the graphics resource.
   *  \return The graphics resource. It could be and image index, text index, a complex 3D model.
   *  \sa setGraphics, getX, getY, getW, getH
   */
  virtual uint64_t getGraphics() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_DRAWABLE_H_
