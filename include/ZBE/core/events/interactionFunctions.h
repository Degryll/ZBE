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

// template<typename F, typename A1, typename A2>
// class InteractionFunctor {
// public:
//   //using typename F = std::function<bool(std::shared_ptr<A1>, std::shared_ptr<A2>, int64_t, CollisionData<s>&)>;
//
//   InteractionFunctor() : f() {}
//
//   bool operator()(std::shared_ptr<A1> arg1, std::shared_ptr<A2> arg2, int64_t time, CollisionData<s> &data) {
//     return f(arg1, arg2, time, data);
//   }
//
// private:
//   F f;
// }

template<unsigned s>
class MovingNSphereFunctor {
public:
  bool operator()(std::shared_ptr<MovingNSphere<s>> arg1, std::shared_ptr<MovingNSphere<s>> arg2, int64_t time, NewCollisionData<s> &data) {
    return MovingNSphereMovingNSphere(arg1, arg2, time, data);
  }
};

using MovingSphereFunctor = MovingNSphereFunctor<3>;

// template<unsigned s>
// using typename MovingNSphereFunctor = InteractionFunctor<MovingNSphere<s>, MovingNSphere<s>>;

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_INTERACTIONFUNCTIONS_H
