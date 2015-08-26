/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameApp.h
 * @since 2014-09-12
 * @date 2014-09-12
 * @author Degryll
 * @brief Data of a collision.
 */

#ifndef CORE_COLLISIONDATA_H_
#define CORE_COLLISIONDATA_H_

#include "ZBE/core/archetypes/Collisioner.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

class CollisionData {
  public:
    CollisionData(Collisioner *collisionador, Collisioner *collisionable, const Vector2D& normal,const Vector2D& point)
      : d(collisionador), b(collisionable), n(normal), p(point){}

    Collisioner* getCollisionador() const {return d;}
    Collisioner* getCollisionable() const {return b;}
    const Vector2D& getNormal() const {return n;}
    const Vector2D& getPoint()  const {return p;}

    void react(double time);

  private:
    Collisioner *d;
    Collisioner *b;
    const Vector2D& n;
    const Vector2D& p;
};

}  // namespace zbe

#endif  // CORE_COLLISIONDATA_H_
