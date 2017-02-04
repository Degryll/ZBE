/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionObject.h
 * @since 2016-11-22
 * @date 2017-01-19
 * @author Degryll Ludo Batis
 * @brief Defines an element that can collide.
 */

#ifndef CORE_TOOLS_COLLISION_COLLISIONOBJECT_H_
#define CORE_TOOLS_COLLISION_COLLISIONOBJECT_H_


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
class CollisionObject {
public:
  virtual ~CollisionObject() {}  //!< Empty destructor
// You must add a new "accept" function for any new derived CollisionObject
  virtual bool accept(CollisionSelector<R> &visitor, CollisionObject& param1, int64_t& time, Point2D& point) = 0;       //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector<R> &visitor, StaticSolidAABB2D<R>& param1, int64_t& time, Point2D& point) = 0;          //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector<R> &visitor, StaticLimiterAABB2D<R>& param1, int64_t& time, Point2D& point) = 0;          //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector<R> &visitor, ConstantMovingCircle<R>& param1, int64_t& time, Point2D& point) = 0;  //!< Collision solver using the visitor pattern
};

} //namespace zbe

#endif  // CORE_TOOLS_COLLISION_COLLISIONOBJECT_H_
