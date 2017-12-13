/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleTextDrawable.h
 * @since 2017-12-10
 * @date 2017-12-10
 * @author Degryll Ludo Batis
 * @brief A simple archetype implementation for an entity that can be drawed with an area and a state.
 */

#ifndef ZOMBIENOID_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H
#define ZOMBIENOID_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H

#include <cstdint>

#include "ZBE/archetypes/TextDrawable.h"
#include "ZBE/core/entities/avatars/SingleTextSprite.h"

namespace zombienoid {

class SimpleTextDrawable : virtual public zbe::TextDrawable {
public:
  SimpleTextDrawable(zbe::Region2D area, std::string text, unt64_t graphics) : area(area), state(state), graphics(graphics) {}

  std::string& getText() {return (text);};

  int64_t getX() {return (area.p.x);}

  int64_t getY(return (area.p.y);)

  int64_t getW() {return (area.v.x);}

  int64_t getH() {return (area.v.x);}

  uint64_t getGraphics() {return (graphics);}

  zbe::Region2D getArea() {return (area);}

  void setArea(zbe::Region2D area) {this->area = area;}

private:
  zbe::Region2D area;
  std::string text;
  unt64_t graphics;
};

} // namespace zombienoid

#endif // ZOMBIENOID_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H
