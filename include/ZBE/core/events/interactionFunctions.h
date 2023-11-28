/**
 * Copyright 2012 Batis Degryll Ludo
 * @file interactionFunctions.h
 * @since 2021-10-19
 * @date 2021-10-19
 * @author Degryll Batis Ludo
 * @brief Collection of interaction shapes and its functions,
 */

#ifndef ZBE_CORE_EVENTS_INTERACTIONFUNCTIONS_H
#define ZBE_CORE_EVENTS_INTERACTIONFUNCTIONS_H

#include "ZBE/core/tools/math/collisions/intersections.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/events/shapes.h"

namespace zbe {

template<unsigned s>
struct NewCollisionData {
  uint64_t time{};
  zbe::Point<s> point{};
  zbe::Vector<s> normal{};
};

using CollisionData3D = NewCollisionData<3>;
using CollisionData2D = NewCollisionData<2>;

template<unsigned s>
bool MovingNSphereMovingNSphere(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, uint64_t time, NewCollisionData<s> &data) {
  data.time = time;
  return intersectionMovingNSphereOutsideMovingNSphere(*(arg1->getShape()), arg1->v, *(arg2->getShape()), arg2->v, data.time, data.point, data.normal);
}


template<unsigned s>
bool MovingNSphereMovingTriangle(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingTriangle<s>> arg2, uint64_t time, NewCollisionData<s> &data) {
  data.time = time;
  return intersectionMovingNSphereOutsideMovingNTriangle<s>(*(arg1->getShape()), arg1->v, *(arg2->getShape()), arg2->v, data.time, data.point, data.normal);
}


template<unsigned s>
bool MovingTriangleMovingNSphere(std::shared_ptr<MovingTriangle<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, uint64_t time, NewCollisionData<s> &data) {
  data.time = time;
  return intersectionMovingNSphereOutsideMovingNTriangle<s>(*(arg2->getShape()), arg2->v, *(arg1->getShape()), arg1->v, data.time, data.point, data.normal);
}

template<typename a, typename b, unsigned s>
bool notIntersect(std::shared_ptr<a>, std::shared_ptr<b>, uint64_t time, NewCollisionData<s> &data) {
  data.time = time;
  return false;
}

template<unsigned s>
class MovingNSphereFunctor {
public:
  bool operator()(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, uint64_t time, NewCollisionData<s> &data) {
    return MovingNSphereMovingNSphere(arg1, arg2, time, data);
  }
};

template<unsigned s>
class MovingNSphereMovingTriangleFunctor {
public:
  bool operator()(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingTriangle<s>> arg2, uint64_t time, NewCollisionData<s> &data) {
    return MovingNSphereMovingTriangle(arg1, arg2, time, data);
  }
};

template<unsigned s>
class MovingTriangleMovingNSphereFunctor {
public:
  bool operator()(std::shared_ptr<MovingTriangle<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, uint64_t time, NewCollisionData<s> &data) {
    return MovingTriangleMovingNSphere(arg1, arg2, time, data);
  }
};

template<typename a, typename b, unsigned s>
class NotIntersectFunctor {
public:
  bool operator()(std::shared_ptr<a> arg1, std::shared_ptr<b> arg2, uint64_t time, NewCollisionData<s> &data){
    return notIntersect(arg1, arg2, time, data);
  }
};


bool sameHalfSpace(Point2D pl1, Point2D pl2, Point2D a, Point2D b) {
    int result1 = halfspace(a, pl1, pl2);
    int result2 = halfspace(b, pl1, pl2);
    return (result1 == result2);
}
class MovingPoint2DTriangle2DFunctor {
public:
  bool operator()(std::shared_ptr<MovingPoint2D> movingpoint, std::shared_ptr<Triangle2D> triangle, uint64_t time, NewCollisionData<2> &data){
    NewCollisionData<2> bestData;
    bestData.time = time;

    NewCollisionData<2> currentData;
    currentData.time = time;
    auto currentpoint = *movingpoint->getShape();

    Ray2D r1((currentpoint), movingpoint->v); // The point
    Ray2D r2(triangle->a, triangle->b - triangle->a); // a - b
    Ray2D r3(triangle->b, triangle->c - triangle->b); // b - c
    Ray2D r4(triangle->c, triangle->a - triangle->c); // c - d
    
    Point2D center = triangleCenter(triangle->a, triangle->b, triangle->c);

    bool intersect1 = intersectionMovingRay2DRay2D(r1, r2, currentData.time, currentData.point, currentData.normal);
    if (intersect1) {
      bestData.time = currentData.time;
      bestData.point = currentData.point;
      bestData.normal = currentData.normal;
      auto same = sameHalfSpace(triangle->a, triangle->b, center, bestData.point + movingpoint->v);
      intersect1 = !same;
    } else {
      currentData.time = bestData.time;
    }

    bool intersect2 = intersectionMovingRay2DRay2D(r1, r3, currentData.time, currentData.point, currentData.normal);
    if (intersect2) {
      bestData.time = currentData.time;
      bestData.point = currentData.point;
      bestData.normal = currentData.normal;
      auto same = sameHalfSpace(triangle->b, triangle->c, center, bestData.point + movingpoint->v);
      intersect2 = !same;
    } else {
      currentData.time = bestData.time;
    }

    bool intersect3 = intersectionMovingRay2DRay2D(r1, r4, currentData.time, currentData.point, currentData.normal);
    if (intersect3) {
      bestData.time = currentData.time;
      bestData.point = currentData.point;
      bestData.normal = currentData.normal;
      auto same = sameHalfSpace(triangle->c, triangle->a, center, bestData.point + movingpoint->v);
      intersect3 = !same;
    }

    data.time = bestData.time;
    data.point = bestData.point;
    data.normal = bestData.normal;

    return (intersect1 || intersect2 || intersect3);
  }
};

// posiblemente MovingPoint2DConvexPolygon2D

using MovingSphereFunctor = MovingNSphereFunctor<3>;
using MovingSphereMovingTriangle3DFunctor = MovingNSphereMovingTriangleFunctor<3>;
using MovingTriangle3DMovingSphereFunctor = MovingTriangleMovingNSphereFunctor<3>;

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_INTERACTIONFUNCTIONS_H
