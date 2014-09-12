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

#include "ZBE/core/tools/math/Vector2D.h"

namespace zbe {

class Collisioner {
  public:
    virtual ~Collisioner() {}

    virtual void react(Collisioner *c, const Vector2D& normal,const Vector2D& point, double time) = 0;

    virtual unsigned int getType() = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_COLLISIONER_H_
