/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionBodies.h
 * @since 2017-04-23
 * @date 2017-04-23
 * @author Ludo Degryll
 * @brief Collection ob bodies for use in collision syste,.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONBODIES_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONBODIES_H_

#include "ZBE/core/events/generators/util/CollisionObject.h"

namespace zbe {

/** \brief A collision object defined by a 2D AABB
 */
template <typename R>
class StaticSolidAABB2D: public CollisionObjectCommon<StaticSolidAABB2D<R>, R> {
public:

  StaticSolidAABB2D() : CollisionObjectCommon<StaticSolidAABB2D<R>, R>(this), box() {}
  StaticSolidAABB2D(AABB2D box) : CollisionObjectCommon<StaticSolidAABB2D<R>, R>(this), box(box) {}

  /** \brief Return the 2D AABB.
   *  \return A 2D AABB.
   */
  inline AABB2D& getAABB2D() {return (box);}

private:
  AABB2D box;  //!< The 2D AABB.
};

/** \brief A collision object defined by a 2D AABB
 */
template <typename R>
class StaticLimiterAABB2D: public CollisionObjectCommon<StaticLimiterAABB2D<R>, R> {
public:

  StaticLimiterAABB2D() : CollisionObjectCommon<StaticLimiterAABB2D<R>, R>(this), box() {}
  StaticLimiterAABB2D(AABB2D box) : CollisionObjectCommon<StaticLimiterAABB2D<R>, R>(this), box(box) {}

  /** \brief Return the 2D AABB.
   *  \return A 2D AABB.
   */
  inline AABB2D& getAABB2D() {return (box);}

private:
  AABB2D box;  //!< The 2D AABB.
};

/** \brief A collision object defined by a circle moving with a constant speed.
 */
template <typename R>
class ConstantMovingCircle: public CollisionObjectCommon<ConstantMovingCircle<R>, R> {
public:

  ConstantMovingCircle() : CollisionObjectCommon<ConstantMovingCircle<R>, R>(this), circle(), direction() {}
  ConstantMovingCircle(Circle circle, Vector2D direction) : CollisionObjectCommon<ConstantMovingCircle<R>, R>(this), circle(circle), direction(direction) {}
  ConstantMovingCircle(ConstantMovingCircle&& rhs) : CollisionObjectCommon<ConstantMovingCircle<R>, R>(this), circle(std::move(rhs.circle)), direction(std::move(rhs.direction)) {}

  /** \brief Return the circle.
   *  \return A circle.
   */
  inline Circle& getCircle() {return (circle);}
  /** \brief Return the circle's movement direction.
   *  \return The direction of movement.
   */
  inline Vector2D& getDirection() {return (direction);}

private:
  Circle circle;       //!< The circle.
  Vector2D direction;  //!< The direction of movement.
};

} // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONBODIES_H_
