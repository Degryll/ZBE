/**
 * Copyright 2012 Batis Degryll Ludo
 * @file IntersectionCollisionSelector.h
 * @since 2017-04-23
 * @date 2017-04-23
 * @author Ludo Degryll
 * @brief Apply the correct function to solve intersections.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_INTERSECTIONCOLLISIONSELECTOR_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_INTERSECTIONCOLLISIONSELECTOR_H_

#include <cstdint>

#include "ZBE/core/events/generators/util/CollisionSelector.h"

namespace zbe {

/** \brief Apply the correct function to solve a collision.
 */
template <typename R>
class IntersectionCollisionSelector : public CollisionSelector<R> {

    inline bool visit(StaticSolidAABB2D<R>&, StaticSolidAABB2D<R>&, int64_t&, Point2D&, Vector2D&);

    inline bool visit(StaticLimiterAABB2D<R>&, StaticLimiterAABB2D<R>&, int64_t&, Point2D&, Vector2D&);

    inline bool visit(StaticSolidAABB2D<R>&, StaticLimiterAABB2D<R>&, int64_t&, Point2D&, Vector2D&);

    inline bool visit(StaticLimiterAABB2D<R>&, StaticSolidAABB2D<R>&, int64_t&, Point2D&, Vector2D&);

    inline bool visit(StaticSolidAABB2D<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point, Vector2D& normal);

    inline bool visit(StaticLimiterAABB2D<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point, Vector2D& normal);

    inline bool visit(ConstantMovingCircle<R>& param1, StaticSolidAABB2D<R>& param2, int64_t& time, Point2D& point, Vector2D& normal);

    inline bool visit(ConstantMovingCircle<R>& param1, StaticLimiterAABB2D<R>& param2, int64_t& time, Point2D& point, Vector2D& normal);

    inline bool visit(ConstantMovingCircle<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point, Vector2D& normal);
};

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticSolidAABB2D<R>& param1, StaticSolidAABB2D<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return (intersectionAABBAABB<2>(param1.getAABB2D(),param2.getAABB2D()));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticLimiterAABB2D<R>& param1, StaticLimiterAABB2D<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return (intersectionAABBAABB<2>(param1.getAABB2D(),param2.getAABB2D()));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticSolidAABB2D<R>& param1, StaticLimiterAABB2D<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return (intersectionAABBAABB<2>(param1.getAABB2D(),param2.getAABB2D()));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticLimiterAABB2D<R>& param1, StaticSolidAABB2D<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return intersectionAABBAABB<2>(param1.getAABB2D(),param2.getAABB2D());
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticSolidAABB2D<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return(intersectionCircleAABB2D(param2.getCircle(), param1.getAABB2D()));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticLimiterAABB2D<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return(intersectionCircleAABB2D(param2.getCircle(), param1.getAABB2D()));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(ConstantMovingCircle<R>& param1, StaticSolidAABB2D<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return(intersectionCircleAABB2D(param1.getCircle(), param2.getAABB2D()));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(ConstantMovingCircle<R>& param1, StaticLimiterAABB2D<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return(intersectionCircleAABB2D(param1.getCircle(), param2.getAABB2D()));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(ConstantMovingCircle<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point, Vector2D& normal) {
  time=0; point = Point2D{0,0}; normal = Vector2D{0,0};
  return(intersectionCircleCircle(param1.getCircle(), param2.getCircle()));
}

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_INTERSECTIONCOLLISIONSELECTOR_H_
