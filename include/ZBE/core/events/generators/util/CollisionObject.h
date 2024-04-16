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

#include "ZBE/core/events/generators/util/CollisionData.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI StaticSolidAABB2D;
class ZBEAPI StaticLimiterAABB2D;
class ZBEAPI ConstantMovingCircle;

/** \brief Defines an element that, using a CollisionSelector, is able to
 * solve a collision with another CollisionObject.
 * It is solved through visitor pattern.
 * You must add a new "accept" function for any new derived CollisionObject
 */
class ZBEAPI CollisionObject {
public:
  virtual ~CollisionObject() {}  //!< Empty destructor

  /** \brief Collision solver using the visitor pattern
   *  \param visitor    Object that solves the collision
   *  \param collObject The other object involved in the collision with it's type unsolved.
   *  \param time       Will store the time when the collision occurs.
   *  \param point      Will store the point where the collision occurs.
   *  \param normal     Will store the normal from the collision surface
   */
  virtual bool accept(CollisionSelector *visitor, CollisionObject& collObject, uint64_t& time, OldCollisionData* data) = 0;

  /** \brief Collision solver using the visitor pattern
   *  \param visitor    Object that solves the collision
   *  \param collObject The other object involved in the collision, a static Solid AABB2D
   *  \param time       Will store the time when the collision occurs.
   *  \param point      Will store the point where the collision occurs.
   *  \param normal     Will store the normal from the collision surface
   */
  virtual bool accept(CollisionSelector *visitor, StaticSolidAABB2D& collObject, uint64_t& time, OldCollisionData* data) = 0;

  /** \brief Collision solver using the visitor pattern
   *  \param visitor    Object that solves the collision
   *  \param collObject The other object involved in the collision, a static limiter AABB2D
   *  \param time       Will store the time when the collision occurs.
   *  \param point      Will store the point where the collision occurs.
   *  \param normal     Will store the normal from the collision surface
   */
  virtual bool accept(CollisionSelector *visitor, StaticLimiterAABB2D& collObject, uint64_t& time, OldCollisionData* data) = 0;

  /** \brief Collision solver using the visitor pattern
   *  \param visitor    Object that solves the collision
   *  \param collObject The other object involved in the collision, a Constant Moving Circle
   *  \param time       Will store the time when the collision occurs.
   *  \param point      Will store the point where the collision occurs.
   *  \param normal     Will store the normal from the collision surface
   */
  virtual bool accept(CollisionSelector *visitor, ConstantMovingCircle& collObject, uint64_t& time, OldCollisionData* data) = 0;  //!< Collision solver using the visitor pattern
};


/** \brief Common implementation of collisionObject used to avoid repeated code
 * You must add to this class ZBEAPI a new "accept" function for any new derived CollisionObject
 */
template <typename T>
class CollisionObjectCommon : public CollisionObject {
public:

  CollisionObjectCommon(const CollisionObjectCommon&) = delete;  //!< Avoid copy
  void operator=(const CollisionObjectCommon&) = delete;  //!< Avoid copy

  /* \brief parametrized constructor
   * \param collisionObject Object that solves the collision.
   */
  CollisionObjectCommon(T* collisionObject) : c(collisionObject) {}

  bool accept(CollisionSelector *visitor, CollisionObject& collObject, uint64_t& time, OldCollisionData* data) {
    return (collObject.accept(visitor, *c, time, data));
  }

  bool accept(CollisionSelector *visitor, StaticSolidAABB2D& collObject, uint64_t& time, OldCollisionData* data) {
    return (visitor->visit(*c, collObject, time, data));
  }

  bool accept(CollisionSelector *visitor, StaticLimiterAABB2D& collObject, uint64_t& time, OldCollisionData* data) {
    return (visitor->visit(*c, collObject, time, data));
  }

  bool accept(CollisionSelector *visitor, ConstantMovingCircle& collObject, uint64_t& time, OldCollisionData* data) {
    return (visitor->visit(*c, collObject, time, data));
  }

private:
  T* c;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONOBJECT_H_
