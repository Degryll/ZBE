/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Positionable.h
 * @since 2015-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that has a position in the world.
 */

#ifndef CORE_ARCHETYPES_POSITIONABLE_H_
#define CORE_ARCHETYPES_POSITIONABLE_H_

namespace zbe {

class Positionable {
  public:
    Positionable() : x(0), y(0) {}
    Positionable(int x, int y) : x(x), y(y) {}

    virtual ~Positionable() {}

    inline int getX() const {return (x);}
    inline int getY() const {return (y);}

    inline void setX(int x) {this->x = x;}
    inline void setY(int y) {this->y = y;}

    inline void increaseX(int x) {this->x += x;}
    inline void increaseY(int y) {this->y += y;}

  private:
    int x = 0;
    int y = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_POSITIONABLE_H_
