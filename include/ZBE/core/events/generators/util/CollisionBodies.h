/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionBodies.h
 * @since 2017-04-23
 * @date 2018-03-11
 * @author Ludo Degryll Batis
 * @brief Collection ob bodies for use in collision syste,.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONBODIES_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONBODIES_H_

#include "ZBE/core/events/generators/util/CollisionObject.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

/** \brief Defines a AABB area of the space that is "solid" inside.
 * Its used to detect collisions with objects that come from outside the box.
 */
template <typename R>
class StaticSolidAABB2D: public CollisionObjectCommon<StaticSolidAABB2D<R>, R> {
public:

  /** \brief Empty constructor
   */
  StaticSolidAABB2D() : CollisionObjectCommon<StaticSolidAABB2D<R>, R>(this), box() {}

  /** \brief Builds a StaticSolidAABB2D from a AABB2D structure.
   *  \param box The required AABB2D
   */
  StaticSolidAABB2D(AABB2D box) : CollisionObjectCommon<StaticSolidAABB2D<R>, R>(this), box(box) {}

  /** \brief Return the 2D AABB.
   *  \return A 2D AABB.
   */
  inline AABB2D& getAABB2D() {return (box);}

private:
  AABB2D box;  //!< The 2D AABB.
};

/** \brief Defines a AABB area of the space that is "solid" outside.
 * Its used to detect collisions with objects that come from inside the box.
 */
template <typename R>
class StaticLimiterAABB2D: public CollisionObjectCommon<StaticLimiterAABB2D<R>, R> {
public:

  /** \brief Empty constructor
   */
  StaticLimiterAABB2D() : CollisionObjectCommon<StaticLimiterAABB2D<R>, R>(this), box() {}

  /** \brief Parametrized constructor
      \param box The 2D AABB
   */
  StaticLimiterAABB2D(AABB2D box) : CollisionObjectCommon<StaticLimiterAABB2D<R>, R>(this), box(box) {}

  /** \brief getter for box:
   *  \return box The 2D AABB.
   */
  inline AABB2D& getAABB2D() {return (box);}

private:
  AABB2D box;  //!< The 2D AABB.
};

/** \brief A collision object defined by a circle moving with a constant speed.
 * Its used to detect collisions with objects that are approached from the outside.
 */
template <typename R>
class ConstantMovingCircle: public CollisionObjectCommon<ConstantMovingCircle<R>, R> {
public:

  /** \Empty constructor
   */
  ConstantMovingCircle() : CollisionObjectCommon<ConstantMovingCircle<R>, R>(this), circle(), direction() {}

  /** \brief Parametrized constructor
   *  \param circle The moving Circle
   *  \param direction The direction of the moving Circle
   */
  ConstantMovingCircle(Circle circle, Vector2D direction) : CollisionObjectCommon<ConstantMovingCircle<R>, R>(this), circle(circle), direction(direction) {}

  /** \brief Parametrized constructor
   *  \param rhs The moving Circle
   */
  ConstantMovingCircle(ConstantMovingCircle&& rhs) : CollisionObjectCommon<ConstantMovingCircle<R>, R>(this), circle(std::move(rhs.circle)), direction(std::move(rhs.direction)) {}

  /** \brief getter for circle. Returns the circle.
   *  \return circle The moving circle.
   */
  inline Circle& getCircle() {return (circle);}
  /** \brief getter for direction. Returns the circle's movement direction.
   *  \return The direction of movement.
   */
  inline Vector2D& getDirection() {return (direction);}

private:
  Circle circle;       //!< The circle.
  Vector2D direction;  //!< The direction of movement.
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONBODIES_H_
