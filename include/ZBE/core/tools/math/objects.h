/**
 * Copyright 2011 Batis Degryll Ludo
 * @file objects.h
 * @since 2015/05/19
 * @date 2015/05/19
 * @author Degryll
 * @brief Math objects definitions
 */

#ifndef ZBE_CORE_TOOLS_MATH_OBJECTS_H_
#define ZBE_CORE_TOOLS_MATH_OBJECTS_H_

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

template <unsigned s>
struct Ray {
  Ray() {}
  Ray(Point<s> p, Vector<s> v) : o(p), d(v) {}
  Ray(std::initializer_list<double> lo, std::initializer_list<double> lv) : o(lo), d(lv) {}

  Point<s> o;
  Vector<s> d;
};

// TODO probably Ray 2D|3D should be a typedef
struct Ray2D : Ray<2>{
  Ray2D() {}
  Ray2D(Point<2> p, Vector<2> v) : Ray(p,v) {}
  Ray2D(std::initializer_list<double> lo, std::initializer_list<double> lv) : Ray(lo,lv) {}
};

struct Ray3D : Ray<3>{
  Ray3D() {}
  Ray3D(Point<3> p, Vector<3> v) : Ray(p,v) {}
  Ray3D(std::initializer_list<double> lo, std::initializer_list<double> lv) : Ray(lo,lv) {}
};

template <unsigned s>
struct NSphere {
  NSphere() {}
  NSphere(Point<s> center, double radius) : c(center), r(radius) {}
  NSphere(std::initializer_list<double> lc, double r) : c(lc), r(r) {}

  Point<s> c;
  double r;
};

// TODO probably Circle|Sphere should be a typedef
struct Circle : NSphere<2> {
  Circle() {}
  Circle(Point<2> center, double radius) : NSphere(center,radius) {}
  Circle(std::initializer_list<double> lc, double r) : NSphere(lc,r) {}
};

struct Sphere : NSphere<3> {
  Sphere() {}
  Sphere(Point<3> center, double radius) : NSphere(center,radius) {}
  Sphere(std::initializer_list<double> lc, double r) : NSphere(lc,r) {}
};

template <unsigned s>
struct AABB {
  AABB() {}
  AABB(Point<s> pmin, Point<s> pmax) : minimun(pmin), maximun(pmax) {}
  AABB(std::initializer_list<double> lmin, std::initializer_list<double> lmax) : minimun(lmin), maximun(lmax) {}

  Point<s> minimun;
  Point<s> maximun;
};

struct AABB2D : AABB<2> {
  AABB2D() {}
  AABB2D(Point<2> pmin, Point<2> pmax) : AABB(pmin,pmax) {}
  AABB2D(std::initializer_list<double> lmin, std::initializer_list<double> lmax) : AABB(lmin,lmax) {}
};

struct AABB3D : AABB<3> {
  AABB3D() {}
  AABB3D(Point<3> pmin, Point<3> pmax) : AABB(pmin,pmax) {}
  AABB3D(std::initializer_list<double> lmin, std::initializer_list<double> lmax) : AABB(lmin,lmax) {}
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_OBJECTS_H_
