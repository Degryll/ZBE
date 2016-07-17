/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SphereCollisionable.h
 * @since 2014-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that collides as a sphere.
 */

#ifndef CORE_ARCHETYPES_SPHERECOLLISIONABLE_H_
#define CORE_ARCHETYPES_SPHERECOLLISIONABLE_H_

namespace zbe {

class SphereCollisionable {
  public:
    SphereCollisionable() : x(0), y(0), r(0) {}
    SphereCollisionable(int x, int y, unsigned radius) : x(x), y(y), r(radius) {}

    ~SphereCollisionable() {}

    inline void setX(int x)                {this->x = x;}
    inline void setY(int y)                {this->y = y;}
    inline void setRadius(unsigned radius) {this->r = radius;}

    inline int      getX()      const {return (x);}
    inline int      getY()      const {return (y);}
    inline unsigned getRadius() const {return (r);}

  private:
    int x = 0;
    int y = 0;
    unsigned r = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_SPHERECOLLISIONABLE_H_
