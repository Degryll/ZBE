/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameApp.h
 * @since 2014-09-12
 * @date 2014-09-12
 * @author Ludo Degryll
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
 *  For now, the information stored is just the point of collision.
 */
class CollisionData {
  public:
    /** \brief Parametrized constructor
     *
     *  Build the collision data with the point of the collision.
     */
    CollisionData(const Point2D& point): p(point){}

    const Point2D& getPoint()  const {return p;}

  private:
    const Point2D& p;
};

}  // namespace zbe

#endif  // CORE_COLLISIONDATA_H_
