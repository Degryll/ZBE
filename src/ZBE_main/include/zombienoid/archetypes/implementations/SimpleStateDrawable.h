/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleStateDrawable.h
 * @since 2017-12-10
 * @date 2017-12-10
 * @author Degryll Ludo Batis
 * @brief A simple archetype implementation for an entity that can be drawed with an area and a state.
 */

#ifndef ZOMBIENOID_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATEDRAWABLE_H
#define ZOMBIENOID_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATEDRAWABLE_H

#include <cstdint>

#include "ZBE/core/system/SysTime.h"

#include "ZBE/archetypes/State.h"
#include "ZBE/archetypes/Drawable.h"

#include "ZBE/core/entities/avatars/AnimatedSprite.h"

namespace zombienoid {

class SimpleStateDrawable : virtual public zbe::State, virtual public zbe::Drawable, virtual public zbe::AnimatedSprite {
public:
  SimpleStateDrawable(zbe::Region2D area, int64_t state, double degrees, uint64_t graphics) : area(area), state(state), graphics(graphics), time(0), degrees(degrees), sysTime(zbe::SysTime::getInstance()) {}

  void setState(int64_t state) {
    this->time = sysTime.getEventTime();
    this->state = state;
  }

  void add(int64_t value) {this->state += value;}

  int64_t getState() {return (state);}

  int64_t getX() {return (area.p.x);}

  int64_t getY() {return (area.p.y);}

  int64_t getW() {return (area.v.x);}

  int64_t getH() {return (area.v.y);}

  uint64_t getGraphics() {return graphics;}

  uint64_t getTime() {return sysTime.getTotalTime() - time;}

  double getDegrees() {return degrees;}

  zbe::Region2D getArea() {return (area);}

  void setArea(zbe::Region2D area) {this->area = area;}

private:
  zbe::Region2D area;
  int64_t state;
  int64_t graphics;
  int64_t time;
  double degrees;
  zbe::SysTime& sysTime;
};

} // namespace zombienoid

#endif // ZOMBIENOID_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATEDRAWABLE_H
