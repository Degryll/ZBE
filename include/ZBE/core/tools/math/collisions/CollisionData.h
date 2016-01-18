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
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

/** \brief Stores the data of a collision between two entities.
 *
 *  The information stored is a reference to each entity, the point and the normal.
 */
class CollisionData {
  public:
    /** \brief Parametrized constructor
     *
     *  Build the collision data with a reference to the entities, the point and normal of the collision.
     */
    CollisionData(Collisioner *collisionador, Collisioner *collisionable, const Vector2D& normal,const Point2D& point)
      : d(collisionador), b(collisionable), n(normal), p(point){}

    Collisioner* getCollisionador() const {return d;}
    Collisioner* getCollisionable() const {return b;}
    const Vector2D& getNormal() const {return n;}
    const Point2D& getPoint()  const {return p;}

    void react(double time);

  private:
    Collisioner *d;
    Collisioner *b;
    const Vector2D& n;
    const Point2D& p;
};

}  // namespace zbe

#endif  // CORE_COLLISIONDATA_H_
