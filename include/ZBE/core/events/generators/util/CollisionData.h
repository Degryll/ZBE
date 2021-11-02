/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameApp.h
 * @since 2014-09-12
 * @date 2014-09-12
 * @author Ludo Degryll
 * @brief Data of a collision.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_OLDCOLLISIONDATA_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_OLDCOLLISIONDATA_H_

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Stores the data of a collision between two entities.
 *
 *  For now, the information stored is just the point of collision.
 */
class ZBEAPI OldCollisionData {
  public:
    /** \brief Parametrized constructor
     *
     *  Build the collision data with the point of the collision.
     */
    OldCollisionData() : p(), n() {}

    /** \brief Parametrized constructor
     *
     *  Build the collision data with the point of the collision.
     */
    OldCollisionData(const Point2D& point, const Vector2D& normal) : p(point), n(normal) {}

    /** \brief Returns the point associated with the collision.
     *
     * \return A Point2D.
     */
    const Point2D& getPoint() const {return p;}

    /** \brief Returns the point associated with the collision.
     *
     * \return A Point2D.
     */
    Point2D& getPoint() {return p;}

    /** \brief Returns the point associated with the collision.
     *
     * \return A Point2D.
     */
    const Vector2D& getNormal() const {return n;}

    /** \brief Returns the point associated with the collision.
     *
     * \return A Point2D.
     */
    Vector2D& getNormal() {return n;}

  private:

    Point2D p;
    Vector2D n;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_OLDCOLLISIONDATA_H_
