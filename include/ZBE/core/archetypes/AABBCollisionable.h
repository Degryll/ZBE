/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AABBCollisionable.h
 * @since 2014-05-94
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that collides as a Axis Aligned Bounding Box (AABB).
 */

#ifndef CORE_ARCHETYPES_AABBCOLLISIONABLE_H_
#define CORE_ARCHETYPES_AABBCOLLISIONABLE_H_

namespace zbe {

class AABBCollisionable {
  public:
    AABBCollisionable() : x(0), y(0), w(0), h(0), r(0) {}
    AABBCollisionable(int x, int y, unsigned width, unsigned height, unsigned radius)  : x(x), y(y), w(width), h(heigth), r(radius) {}

    ~AABBCollisionable() {}

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

#endif  // CORE_ARCHETYPES_AABBCOLLISIONABLE_H_
