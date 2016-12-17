/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleMobile.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Simple implementation of the Mobile2D interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE2D_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE2D_H

#include "ZBE/archetypes/Mobile2D.h"

namespace zbe {

class SimpleMobile2D : public Mobile2D, public SimplePosition2D {
  public:
    SimpleMobile2D() : SimplePosition2D(), v(.0, .0) {}
    SimpleMobile2D(double x, double y) : SimplePosition2D(x, y), v(.0, .0) {}
    SimpleMobile2D(double x, double y, double vx, double vy) : SimplePosition2D(x, y), v(vx, vy) {}
    SimpleMobile2D(Point2D position) : SimplePosition2D(p), v(.0, .0) {}
    SimpleMobile2D(Point2D position, double vx, double vy) : SimplePosition2D(position), v(vx, vy) {}
    SimpleMobile2D(Point2D position, Vector2D velocity) : SimplePosition2D(position), v(velocity) {}

    void setVelocityX(double x) {v.x = x;}
    void setVelocityY(double y) {v.y = y;}
    void setVelocity(double x, double y) {v.x = x; v.y = y;}
    void setVelocity(Vector2D velocity) {v = velocity;}

    double getVelocityX() {return (v.x);}
    double getVelocityY() {return (v.y);}
    Vector2D getVelocity() {return (v);}

  private:
    Vector2D v;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE2D_H
