/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Positionable.h
 * @since 2015-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that has a position in the world.
 */

#ifndef CORE_ARCHETYPES_POSITIONABLE_H_
#define CORE_ARCHETYPES_POSITIONABLE_H_

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

template <unsigned s>
class Positionable {
  public:
    Positionable() : position() {}
    Positionable(Point<s> position) : position(position) {}

    virtual ~Positionable() {}

    inline Point<s> getPosition() const {return (position);}
    inline void setPosition(Point<s> position) {this->position = position;}

    inline void increase(Vector<s> offset) {this->position += offset;}

  private:
    Point<s> position;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_POSITIONABLE_H_
