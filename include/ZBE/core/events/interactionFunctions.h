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
  int64_t time;
  zbe::Point<s> point;
  zbe::Vector<s> normal;
};

using CollisionData3D = NewCollisionData<3>;
using CollisionData2D = NewCollisionData<2>;

template<unsigned s>
bool MovingNSphereMovingNSphere(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, int64_t time, NewCollisionData<s> &data) {
  data.time = time;
  return intersectionMovingNSphereOutsideMovingNSphere(*(arg1->getShape()), arg1->v, *(arg2->getShape()), arg2->v, data.time, data.point, data.normal);
}


template<unsigned s>
bool MovingNSphereMovingTriangle(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingTriangle<s>> arg2, int64_t time, NewCollisionData<s> &data) {
  data.time = time;
  return intersectionMovingNSphereOutsideMovingNTriangle<s>(*(arg1->getShape()), arg1->v, *(arg2->getShape()), arg2->v, data.time, data.point, data.normal);
}


template<unsigned s>
bool MovingTriangleMovingNSphere(std::shared_ptr<MovingTriangle<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, int64_t time, NewCollisionData<s> &data) {
  data.time = time;
  return intersectionMovingNSphereOutsideMovingNTriangle<s>(*(arg2->getShape()), arg2->v, *(arg1->getShape()), arg1->v, data.time, data.point, data.normal);
}

template<typename a, typename b, unsigned s>
bool notIntersect(std::shared_ptr<a>, std::shared_ptr<b>, int64_t time, NewCollisionData<s> &data) {
  data.time = time;
  return false;
}

template<unsigned s>
class MovingNSphereFunctor {
public:
  bool operator()(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, int64_t time, NewCollisionData<s> &data) {
    return MovingNSphereMovingNSphere(arg1, arg2, time, data);
  }
};

template<unsigned s>
class MovingNSphereMovingTriangleFunctor {
public:
  bool operator()(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingTriangle<s>> arg2, int64_t time, NewCollisionData<s> &data) {
    return MovingNSphereMovingTriangle(arg1, arg2, time, data);
  }
};


template<unsigned s>
class MovingTriangleMovingNSphereFunctor {
public:
  bool operator()(std::shared_ptr<MovingTriangle<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, int64_t time, NewCollisionData<s> &data) {
    return MovingTriangleMovingNSphere(arg1, arg2, time, data);
  }
};

template<typename a, typename b, unsigned s>
class NotIntersectFunctor {
public:
  bool operator()(std::shared_ptr<a> arg1, std::shared_ptr<b> arg2, int64_t time, NewCollisionData<s> &data){
    return notIntersect(arg1, arg2, time, data);
  }
};

using MovingSphereFunctor = MovingNSphereFunctor<3>;
using MovingSphereMovingTriangle3DFunctor = MovingNSphereMovingTriangleFunctor<3>;
using MovingTriangle3DMovingSphereFunctor = MovingTriangleMovingNSphereFunctor<3>;

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_INTERACTIONFUNCTIONS_H
