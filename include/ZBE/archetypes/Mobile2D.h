/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Mobile2D.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Defines the interface of a class with a 2D position and a velocity.
 */

#ifndef ZBE_ARCHETYPES_MOBILE2D_H
#define ZBE_ARCHETYPES_MOBILE2D_H

#include "ZBE/archetypes/Position2D.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

class Mobile2D : public Position2D {
  public:
    virtual ~Mobile2D() {}

    virtual void setVelocityX(double x) = 0;
    virtual void setVelocityY(double y) = 0;
    virtual void setVelocity(double x, double y) = 0;
    virtual void setVelocity(Vector2D velocity) = 0;

    virtual double getVelocityX() = 0;
    virtual double getVelocityY() = 0;
    virtual Vector2D getVelocity() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_MOBILE2D_H
