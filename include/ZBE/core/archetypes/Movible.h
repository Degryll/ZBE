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

namespace zbe {

class Movible : public Positionable {
  public:
    Movible() : Positionable(), vx(0), vy(0) {}
    Movible(int x, int y, int vx, int vy) : Positionable(x,y), vx(vx), vy(vy) {}

    ~Movible() {}

    inline void setVelocityX(int vx) {this->vx = vx;}
    inline void setVelocityY(int vy) {this->vy = vy;}

    inline unsigned getVelocityX() const {return (vx);}
    inline unsigned getVelocityY() const {return (vy);}

  private:
    int vx = 0;
    int vy = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_MOVIBLE_H_
