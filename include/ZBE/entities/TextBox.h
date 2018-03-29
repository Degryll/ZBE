/**
 * Copyright 2011 Batis Degryll Ludo
 * @file TextBox.h
 * @since 2017-08-21
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief A simple text box.
 */

#ifndef ZBE_ENTITIES_TEXTBOX_H
#define ZBE_ENTITIES_TEXTBOX_H

#include <cstdint>

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/archetypes/TextDrawable.h"

namespace zbe {

class TextBox: virtual public TextDrawable,
               public AvatarEntityFixed<SingleTextSprite> {
public:

  /** \brief Constructs a TextBox form its raw data
   *  \param x TextBox position coord x
   *  \param y TextBox position coord x
   *  \param width TextBox width
   *  \param height TextBox height
   *  \param graphics graphics id
   */
  TextBox(int64_t x, int64_t y, int64_t width, int64_t height, uint64_t graphics)
    : x(x), y(y), w(width), h(height), g(graphics) {}

  /** \brief Getter for the x coord.
   *  \return x coord
   */
  int64_t getX() {return (x);}

  /** \brief Getter for the y coord.
   *  \return y coord
   */
  int64_t getY() {return (y);}

  /** \brief Getter for the width
   *  \return width
   */
  int64_t getW() {return (w);}

  /** \brief Getter for the height
   *  \return height
   */
  int64_t getH() {return (h);}

  /** \brief Getter for the graphics id.
   *  \return the graphics id
   */
  uint64_t getGraphics() {return (g);}

private:

  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;
  uint64_t g;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_TEXTBOX_H
