/**
 * Copyright 2011 Batis Degryll Ludo
 * @file TextBox.h
 * @since 2017-08-21
 * @date 2017-08-21
 * @author Batis Degryll Ludo
 * @brief A simple text box.
 */

#ifndef ZBE_ENTITIES_TEXTBOX_H
#define ZBE_ENTITIES_TEXTBOX_H

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/SingleTextSprite.h"

#include "ZBE/archetypes/TextDrawable.h"

namespace zbe {

class TextBox: public TextDrawable,
               public AvatarEntityFixed<SingleTextSprite> {
public:

  TextBox(int64_t x, int64_t y, int64_t width, int64_t height, uint64_t graphics)
    : x(x), y(y), w(width), h(height), g(graphics) {}

  int64_t getX() {return (x);}
  int64_t getY() {return (y);}
  int64_t getW() {return (w);}
  int64_t getH() {return (h);}
  uint64_t getGraphics() {return (g);}

private:

  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;
  uint64_t g;
};

} // namespace zbe

#endif  // ZBE_ENTITIES_TEXTBOX_H
