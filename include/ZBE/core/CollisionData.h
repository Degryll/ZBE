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
#include "ZBE/core/tools/math/Vector2D.h"

namespace zbe {

class CollisionData {
  public:
    CollisionData(Collisioner *collisionador, Collisioner *collisionable, const Vector2D& normal,const Vector2D& point)
      : d(collisionador), b(collisionable), n(normal), p(point){}

    Collisioner* getCollisionador() {return d;}
    Collisioner* getCollisionable() {return b;}
    const Vector2D& getNormal() const {return n;}
    const Vector2D& getPoint()  const {return p;}

    void react(double time);

  private:
    Vector2D n;
    Vector2D p;
    Collisioner *d;
    Collisioner *b;
};

}  // namespace zbe

#endif  // CORE_COLLISIONDATA_H_
