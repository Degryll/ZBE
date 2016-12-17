/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimplePosition2D.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Simple implementation of the Position2D interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION2D_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION2D_H

#include "ZBE/archetypes/Position2D.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

class SimplePosition2D : public Position2D {
  public:
    SimplePosition2D() : p(.0, .0) {}
    SimplePosition2D(double x, double y) : p(x, y) {}
    SimplePosition2D(Point2D position) : p(position) {}

    void setX(double x) {p.x = x;}
    void setY(double y) {p.y = y;}
    void setPosition(double x, double y) {p.x = x; p.y = y;}
    void setPosition(Point2D position) {p = position;}

    double getX() {return (p.x);}
    double getY() {return (p.y);}
    virtual Point2D getPosition() {return (p);}

  private:
    Point2D p;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION2D_H
