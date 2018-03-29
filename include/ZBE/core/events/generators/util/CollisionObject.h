/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionObject.h
 * @since 2016-11-22
 * @date 2018-03-11
 * @author Degryll Ludo Batis
 * @brief Defines an element that can collide.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONOBJECT_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONOBJECT_H_

#include <cstdint>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

template <typename R>
class CollisionSelector;
template <typename R>
class StaticSolidAABB2D;
template <typename R>
class StaticLimiterAABB2D;
template <typename R>
class ConstantMovingCircle;

template <typename R>
class CollisionSelector;

/** \brief Defines an element that, using a CollisionSelector, is able to
 * solve a collision with another CollisionObject.
 * It is solved through visitor pattern.
 * You must add a new "accept" function for any new derived CollisionObject
 */
template <typename R>
class CollisionObject {
public:
  virtual ~CollisionObject() {}  //!< Empty destructor

  /** \brief Collision solver using the visitor pattern
   *  \param visitor    Object that solves the collision
   *  \param collObject The other object involved in the collision with it's type unsolved.
   *  \param time       Will store the time when the collision occurs.
   *  \param point      Will store the point where the collision occurs.
   *  \param normal     Will store the normal from the collision surface
   */
  virtual bool accept(CollisionSelector<R> &visitor, CollisionObject& collObject, int64_t& time, Point2D& point, Vector2D& normal) = 0;

  /** \brief Collision solver using the visitor pattern
   *  \param visitor    Object that solves the collision
   *  \param collObject The other object involved in the collision, a static Solid AABB2D
   *  \param time       Will store the time when the collision occurs.
   *  \param point      Will store the point where the collision occurs.
   *  \param normal     Will store the normal from the collision surface
   */
  virtual bool accept(CollisionSelector<R> &visitor, StaticSolidAABB2D<R>& collObject, int64_t& time, Point2D& point, Vector2D& normal) = 0;

  /** \brief Collision solver using the visitor pattern
   *  \param visitor    Object that solves the collision
   *  \param collObject The other object involved in the collision, a static limiter AABB2D
   *  \param time       Will store the time when the collision occurs.
   *  \param point      Will store the point where the collision occurs.
   *  \param normal     Will store the normal from the collision surface
   */
  virtual bool accept(CollisionSelector<R> &visitor, StaticLimiterAABB2D<R>& collObject, int64_t& time, Point2D& point, Vector2D& normal) = 0;

  /** \brief Collision solver using the visitor pattern
   *  \param visitor    Object that solves the collision
   *  \param collObject The other object involved in the collision, a Constant Moving Circle
   *  \param time       Will store the time when the collision occurs.
   *  \param point      Will store the point where the collision occurs.
   *  \param normal     Will store the normal from the collision surface
   */
  virtual bool accept(CollisionSelector<R> &visitor, ConstantMovingCircle<R>& collObject, int64_t& time, Point2D& point, Vector2D& normal) = 0;  //!< Collision solver using the visitor pattern
};


/** \brief Common implementation of collisionObject used to avoid repeated code
 * You must add to this class a new "accept" function for any new derived CollisionObject
 */
template <typename T, typename R>
class CollisionObjectCommon : public CollisionObject<R> {
public:

  CollisionObjectCommon(const CollisionObjectCommon&) = delete;  //!< Avoid copy
  void operator=(const CollisionObjectCommon&) = delete;  //!< Avoid copy

  /* \brief parametrized constructor
   * \param collisionObject Object that solves the collision.
   */
  CollisionObjectCommon(T* collisionObject) : c(collisionObject) {}

  bool accept(CollisionSelector<R> &visitor, CollisionObject<R>& collObject, int64_t& time, Point2D& point, Vector2D& normal) {
    return (collObject.accept(visitor, *c, time, point, normal));
  }

  bool accept(CollisionSelector<R> &visitor, StaticSolidAABB2D<R>& collObject, int64_t& time, Point2D& point, Vector2D& normal) {
    return (visitor.visit(*c, collObject, time, point, normal));
  }

  bool accept(CollisionSelector<R> &visitor, StaticLimiterAABB2D<R>& collObject, int64_t& time, Point2D& point, Vector2D& normal) {
    return (visitor.visit(*c, collObject, time, point, normal));
  }

  bool accept(CollisionSelector<R> &visitor, ConstantMovingCircle<R>& collObject, int64_t& time, Point2D& point, Vector2D& normal) {
    return (visitor.visit(*c, collObject, time, point, normal));
  }

private:
  T* c;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONOBJECT_H_
