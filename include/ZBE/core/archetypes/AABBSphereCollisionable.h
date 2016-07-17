/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AABBSphereCollisionable.h
 * @since 2014-05-94
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that Collides hierarchically as a sphere and in more
 *        detail as an AABB.
 */

#ifndef CORE_ARCHETYPES_AABBSPHERECOLLISIONABLE_H_
#define CORE_ARCHETYPES_AABBSPHERECOLLISIONABLE_H_

//#include "ZBE/core/archerypes/SphereCollisionable.h"
//#include "ZBE/core/archerypes/AABBCollisionable.h"

namespace zbe {

// TODO tal vez no sea buena idea multiherencia de sphere y AABB collisionable
// Complica los constructores y duplica (o triplica) x e y.
// Por ahora no es necesario sabes que esto cumple SphereCollisionable o
// AABBCollisionable. Por lo tanto lo dejo sin herencia
class AABBSphereCollisionable {
  public:
    AABBSphereCollisionable() : x(0), y(0), w(0), h(0), r(0) {}
    AABBSphereCollisionable(int x, int y, unsigned width, unsigned height, unsigned radius) : x(x), y(y), w(width), h(height), r(radius) {}

    ~AABBSphereCollisionable() {}

    inline void setX(int x)                {this->x = x;}
    inline void setY(int y)                {this->y = y;}
    inline void setWidth(unsigned width)   {this->w = width;}
    inline void setHeight(unsigned height) {this->h = height;}
    inline void setRadius(unsigned radius) {this->r = radius;}

    inline int      getX()      const {return (x);}
    inline int      getY()      const {return (y);}
    inline unsigned getWidth()  const {return (w);}
    inline unsigned getHeight() const {return (h);}
    inline unsigned getRadius() const {return (r);}

  private:
    int x = 0;
    int y = 0;
    unsigned w = 0;
    unsigned h = 0;
    unsigned r = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_AABBSPHERECOLLISIONABLE_H_
