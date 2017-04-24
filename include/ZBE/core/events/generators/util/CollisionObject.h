/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionObject.h
 * @since 2016-11-22
 * @date 2017-01-19
 * @author Degryll Ludo Batis
 * @brief Defines an element that can collide.
 */

#ifndef CORE_EVENTS_GENERATORS_UTIL_COLLISIONOBJECT_H_
#define CORE_EVENTS_GENERATORS_UTIL_COLLISIONOBJECT_H_


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

template <typename R>
class CollisionObject {
public:
  virtual ~CollisionObject() {}  //!< Empty destructor
// You must add a new "accept" function for any new derived CollisionObject
  virtual bool accept(CollisionSelector<R> &visitor, CollisionObject& collObject, int64_t& time, Point2D& point) = 0;       //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector<R> &visitor, StaticSolidAABB2D<R>& collObject, int64_t& time, Point2D& point) = 0;          //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector<R> &visitor, StaticLimiterAABB2D<R>& collObject, int64_t& time, Point2D& point) = 0;          //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector<R> &visitor, ConstantMovingCircle<R>& collObject, int64_t& time, Point2D& point) = 0;  //!< Collision solver using the visitor pattern
};

// You must add to this class a new "accept" function for any new derived CollisionObject
// This class is used to avoid repeated code
template <typename T, typename R>
class CollisionObjectCommon : public CollisionObject<R> {
public:
  CollisionObjectCommon(const CollisionObjectCommon&) = delete;
  void operator=(const CollisionObjectCommon&) = delete;

  CollisionObjectCommon(T* collisionObject) : c(collisionObject) {}

  bool accept(CollisionSelector<R> &visitor, CollisionObject<R>& collObject, int64_t& time, Point2D& point) {
    return (collObject.accept(visitor, *c, time, point));
  }

  bool accept(CollisionSelector<R> &visitor, StaticSolidAABB2D<R>& collObject, int64_t& time, Point2D& point) {
    return (visitor.visit(*c, collObject, time, point));
  }

  bool accept(CollisionSelector<R> &visitor, StaticLimiterAABB2D<R>& collObject, int64_t& time, Point2D& point) {
    return (visitor.visit(*c, collObject, time, point));
  }

  bool accept(CollisionSelector<R> &visitor, ConstantMovingCircle<R>& collObject, int64_t& time, Point2D& point) {
    return (visitor.visit(*c, collObject, time, point));
  }

private:
  T* c;
};


} //namespace zbe

#endif  // CORE_EVENTS_GENERATORS_UTIL_COLLISIONOBJECT_H_
