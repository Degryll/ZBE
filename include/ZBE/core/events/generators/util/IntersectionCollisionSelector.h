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

    inline bool visit(StaticSolidAABB2D<R>&, StaticSolidAABB2D<R>&, int64_t&, Point2D&);

    inline bool visit(StaticLimiterAABB2D<R>&, StaticLimiterAABB2D<R>&, int64_t&, Point2D&);

    inline bool visit(StaticSolidAABB2D<R>&, StaticLimiterAABB2D<R>&, int64_t&, Point2D&);

    inline bool visit(StaticLimiterAABB2D<R>&, StaticSolidAABB2D<R>&, int64_t&, Point2D&);

    inline bool visit(StaticSolidAABB2D<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point);

    inline bool visit(StaticLimiterAABB2D<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point);

    inline bool visit(ConstantMovingCircle<R>& param1, StaticSolidAABB2D<R>& param2, int64_t& time, Point2D& point);

    inline bool visit(ConstantMovingCircle<R>& param1, StaticLimiterAABB2D<R>& param2, int64_t& time, Point2D& point);

    inline bool visit(ConstantMovingCircle<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point);
};

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticSolidAABB2D<R>&, StaticSolidAABB2D<R>&, int64_t&, Point2D&) {return (false);}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticLimiterAABB2D<R>&, StaticLimiterAABB2D<R>&, int64_t&, Point2D&) {return (false);}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticSolidAABB2D<R>&, StaticLimiterAABB2D<R>&, int64_t&, Point2D&) {return (false);}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticLimiterAABB2D<R>&, StaticSolidAABB2D<R>&, int64_t&, Point2D&) {return (false);}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticSolidAABB2D<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point) {
  return(IntersectionMovingCircleOutsideAABB2D(param2.getCircle(), param2.getDirection(), param1.getAABB2D(), time, point));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(StaticLimiterAABB2D<R>& param1, ConstantMovingCircle<R>& param2, int64_t& time, Point2D& point) {
  return(IntersectionMovingCircleInsideAABB2D(param2.getCircle(), param2.getDirection(), param1.getAABB2D(), time, point));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(ConstantMovingCircle<R>& param1, StaticSolidAABB2D<R>& param2, int64_t& time, Point2D& point) {
  return(IntersectionMovingCircleOutsideAABB2D(param1.getCircle(), param1.getDirection(), param2.getAABB2D(), time, point));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(ConstantMovingCircle<R>& param1, StaticLimiterAABB2D<R>& param2, int64_t& time, Point2D& point) {
  return(IntersectionMovingCircleInsideAABB2D(param1.getCircle(), param1.getDirection(), param2.getAABB2D(), time, point));
}

template <typename R>
bool IntersectionCollisionSelector<R>::visit(ConstantMovingCircle<R>& , ConstantMovingCircle<R>& , int64_t& , Point2D& ) {
  // TODO Degryll implementar ConstantMovingSphere contra ConstantMovingSphere
  return (false);
}

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_INTERSECTIONCOLLISIONSELECTOR_H_
