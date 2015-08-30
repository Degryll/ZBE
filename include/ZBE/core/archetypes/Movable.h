/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movible.h
 * @since 2015-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that can be moved around the world.
 */

#ifndef CORE_ARCHETYPES_MOVIBLE_H_
#define CORE_ARCHETYPES_MOVIBLE_H_

#include "ZBE/core/archetypes/Positionable.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

template<unsigned s>
class Movable : public Positionable<s> {
  public:
    Movable() : Positionable<s>(), velocity() {}
    //TODO: constructor por coordenadas. Movable(int x, int y, int vx, int vy) : Positionable(x,y), vx(vx), vy(vy) {}
    Movable(Point<s> position, Vector<s> velocity) : Positionable<s>(position), velocity(velocity) {}

    ~Movable() {}

    inline void setVelocity(Vector<s> velocity) {this->velocity = velocity;}
    inline Vector<s> getVelocity() const {return (velocity);}

    inline void travel(double time) {Positionable<s>::increase(velocity*time);}

  private:
    Vector<s> velocity;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_MOVIBLE_H_
