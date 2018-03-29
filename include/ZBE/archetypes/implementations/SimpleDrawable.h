/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleDrawable.h
 * @since 2016-11-22
 * @date 2018-02-25
 * @author Degryll
 * @brief This implements an entity that can be drawn.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDRAWABLE_H_
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDRAWABLE_H_

#include <cstdint>

#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief This implements an entity that can be drawn.
 */
class SimpleDrawable : virtual public Drawable {
public:
  /** \brief Construct a SimpleDrawable with its top-left corner, width and height, and a index of the graphic resources.
   *  \param x The left coordinate.
   *  \param y The top coordinate.
   *  \param w The width of the image.
   *  \param h The height of the image.
   *  \param graphics The graphic resource. It could be and image index, text index, a complex 3D model.
   */
  SimpleDrawable(const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint64_t graphics) : x(x), y(y), w(w), h(h), graphics(graphics) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleDrawable() {}

  /** \brief Gets the left coordinate.
   *  \return The left coordinate.
   *  \sa setX, getY, getW, getH, getGraphics
   */
  int64_t getX() {return (x);}

  /** \brief Gets the top coordinate.
   *  \return The top coordinate.
   *  \sa setY, getX, getW, getH, getGraphics
   */
  int64_t getY() {return (y);}

  /** \brief Gets the width of the image.
   *  \return The width of the image.
   *  \sa setW, getX, getY, getH, getGraphics
   */
  int64_t getW() {return (w);}

  /** \brief Gets the height of the image.
   *  \return The height of the image.
   *  \sa setH, getX, getY, getW, getGraphics
   */
  int64_t getH() {return (h);}

  /** \brief Gets the graphics resource.
   *  \return The graphics resource. It could be and image index, text index, a complex 3D model.
   *  \sa setGraphics, getX, getY, getW, getH
   */
  uint64_t getGraphics() {return (graphics);}

  /** \brief Sets the left coordinate.
   *  \param x The left coordinate.
   *  \sa getX, setY, setW, setH, setGraphics
   */
  void setX(const int64_t x) {this->x = x;}

  /** \brief Sets the top coordinate.
   *  \param x The top coordinate.
   *  \sa getY, setX, setW, setH, setGraphics
   */
  void setY(const int64_t y) {this->y = y;}

  /** \brief Sets the width of the image.
   *  \param x The width of the image.
   *  \sa getW, setX, setY, setH, setGraphics
   */
  void setW(const int64_t w) {this->w = w;}

  /** \brief Sets the height of the image.
   *  \param x The height of the image.
   *  \sa getH, setX, setY, setW, setGraphics
   */
  void setH(const int64_t h) {this->h = h;}

  /** \brief Sets the graphics resource.
   *  \param graphics The graphics resource. It could be and image index, text index, a complex 3D model.
   *  \sa getGraphics, setX, setY, setW, setH
   */
  void setGraphics(const uint64_t graphics) {this->graphics = graphics;}

private:
  int64_t x; //!< X coordinate
  int64_t y; //!< Y coordinate
  int64_t w; //!< width
  int64_t h; //!< height
  uint64_t graphics;    //!< Image index
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDRAWABLE_H_
