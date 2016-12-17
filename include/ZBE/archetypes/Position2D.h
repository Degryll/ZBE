/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Position2D.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Defines the interface of a class with a 2D position.
 */

#ifndef ZBE_ARCHETYPES_POSITION2D_H
#define ZBE_ARCHETYPES_POSITION2D_H

#include "ZBE/core/tools/math/Point.h"

namespace zbe {

class Position2D {
  public:
    virtual ~Position2D() {}

    virtual void setX(double x) = 0;
    virtual void setY(double y) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void setPosition(Point2D position) = 0;

    virtual double getX() = 0;
    virtual double getY() = 0;
    virtual Point2D getPosition() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_POSITION2D_H
