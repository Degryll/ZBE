/**
 * Copyright 2012 Batis Degryll Ludo
 * @file shapes.h
 * @since 2021-10-19
 * @date 2021-10-19
 * @author Degryll Batis Ludo
 * @brief Collection of interaction shapes and its functions,
 */

#ifndef ZBE_CORE_EVENTS_SHAPES_H
#define ZBE_CORE_EVENTS_SHAPES_H

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"

namespace zbe {

template <typename Shape, unsigned s>
struct Moving : public Shape {
  Moving() : Shape(), v() {}
  Moving(Shape shape, Vector<s> v) : Shape(shape), v(v) {}
  Shape* getShape() {
    return this;
  }
  Vector<s> v;
};

using MovingCircle = Moving<Circle, 2>;
using MovingSphere = Moving<Sphere, 3>;

template<unsigned s>
using MovingNSphere = Moving<NSphere<s>, s>;

using MovingAABB2D = Moving<AABB2D, 2>;
using MovingAABB3D = Moving<AABB3D, 3>;

template<unsigned s>
using MovingAABB = Moving<AABB<s>, s>;

template<unsigned s>
using MovingTriangle = Moving<Triangle<s>, s>;

using MovingTriangle3D = MovingTriangle<3>;
using MovingTriangle2D = MovingTriangle<2>;

template<unsigned s>
using MovingPoint = Moving<Point<s>, s>;

using MovingPoint2D = MovingPoint<2>;
using MovingPoint3D = MovingPoint<3>;

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_SHAPES_H
