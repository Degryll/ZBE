/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Collisionable.h
 * @since 2014-09-22
 * @date 2014-09-22
 * @author Ludo and Degryll
 * @brief Define a class that participate in collision system.
 */

#ifndef CORE_ARCHETYPES_COLLISIONABLE_H_
#define CORE_ARCHETYPES_COLLISIONABLE_H_

#include "ZBE/core/tools/math/Vector2D.h"

namespace zbe {

class Collisionable : Collisioner {
  public:
    virtual ~Collisionable() {}
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_COLLISIONABLE_H_
