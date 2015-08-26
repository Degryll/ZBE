/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Collisioner.h
 * @since 2014-09-12
 * @date 2014-09-12
 * @author Ludo and Degryll
 * @brief Define a class that participate in collision system.
 */

#ifndef CORE_ARCHETYPES_COLLISIONER_H_
#define CORE_ARCHETYPES_COLLISIONER_H_

#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

class Collisioner {
  public:
    enum CollysionType{
      SPHERE = 0,
      AABB   = 1
    };

    virtual ~Collisioner() {}

    virtual void react(Collisioner *c, const Vector2D& normal,const Vector2D& point, double time) = 0;

    virtual CollysionType getType() = 0;
    virtual unsigned collisionLevel() = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_COLLISIONER_H_
