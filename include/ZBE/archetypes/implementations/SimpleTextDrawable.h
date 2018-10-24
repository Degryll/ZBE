/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleTextDrawable.h
 * @since 2017-16-16
 * @date 2017-16-16
 * @author Degryll, Ludo, Batis
 * @brief This implements an entity that can be wrote.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H_
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H_

#include "ZBE/archetypes/Drawable.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This implements an entity that can be wrote.
 */
class ZBEAPI SimpleTextDrawable : virtual public Drawable {
public:
  /** \brief Constructs a SimpleTextDrawable with position as x - y, size as w - h, graphics id to use, text value and color.
   */
  SimpleTextDrawable(int x, int y, unsigned w, unsigned h, int graphics, const char* text, TTF_Font* font, SDL_Color* color) : x(x), y(y), w(w), h(h), graphics(graphics) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleTextDrawable() {}

  /** \brief Returns x coord value
   * \return int x coord value
   */
  int      getX()        {return (x);}

  /** \brief Returns y coord value
   * \return int y coord value
   */
  int      getY()        {return (y);}

  /** \brief Returns Width value
   * \return width value
   */
  unsigned getW()        {return (w);}

  /** \brief Returns Height value
   * \return height value
   */
  unsigned getH()        {return (h);}

  /** \brief Returns the graphics id
   * \return graphics id
   */
  int      getGraphics() {return (graphics);}

  /** \brief Sets x coord
   *  \param x value for x coord.
   */
  void setX(int x)               {this->x = x;}

  /** \brief Sets the Y coord
   *  \param y value for x coord.
   */
  void setY(int y)               {this->y = y;}

  /** \brief Sets width
   *  \param w value for width
   */
  void setW(unsigned w)          {this->w = w;}

  /** \brief Sets height
   *  \param h value for height
   */
  void setH(unsigned h)          {this->h = h;}

  /** \brief Sets the graphics id
   *  \param graphics The graphics id
   */
  void setGraphics(int graphics) {this->graphics = graphics;}

private:
  int x;      //!< X coordinate
  int y;      //!< Y coordinate
  unsigned w; //!< width
  unsigned h; //!< height
  int graphics;    //!< Image index
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H_
