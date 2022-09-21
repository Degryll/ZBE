/**
 * Copyright 2011 Batis Degryll Ludo
 * @file objects.h
 * @since 2015-05-19
 * @date 2018-03-25
 * @author Degryll Ludo Batis
 * @brief Math objects definitions
 */

#ifndef ZBE_CORE_TOOLS_MATH_OBJECTS_H_
#define ZBE_CORE_TOOLS_MATH_OBJECTS_H_

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A class ZBEAPI that represent a Ray (an origin and a direction).
 *
 *  This template needs to know the number of dimensions of the hyperplane to which the Ray belongs to.
 */
template <unsigned s>
struct Ray {
  /** \brief Void constructor, the Ray's values are unknown.
   */
  Ray() {}

  /** \brief Parametrized constructor.
   *
   *  A Ray is constructed with a point to the origin and a director vector.
   *  \param p Origin point.
   *  \param v Direction vector.
   */
  Ray(Point<s> p, Vector<s> v) : o(p), d(v) {}

  /** \brief A list initializer constructor.
   *
   *  You can create a Ray of N dimension with two lists (origin and direction) of N values:
   *
   *        Ray<N> r({o1, o2, ... , oN}, {d1, d2, ... , dN})
   *
   *  or
   *
   *        Ray<N> r = {{o1, o2, ... , oN}, {d1, d2, ... , dN}}
   *  \param lo list of coordinates that defines the origin point of the Ray
   *  \param lv list of dimensions that defines the direction vector of the Ray
   */
  Ray(std::initializer_list<double> lo, std::initializer_list<double> lv) : o(lo), d(lv) {}

  Point<s> o;   //!< Origin data.
  Vector<s> d;  //!< Direction data.
};

/** \brief A class ZBEAPI that represent a 2D Ray (an origin and a direction).
 *
 *  Ray2D is an alias of Ray<2>.
 *
 *  This specialization let you access with the alias .x and .y to the first and second dimensions of the Ray attributes (origin and direction).
 */
template <>
struct Ray<2> {
  /** \brief Void constructor, the 2D Ray's values are unknown.
   */
  Ray() : o(), d() {}

  /** \brief Parametrized constructor.
   *
   *  A 2D Ray is constructed with a 2D point to the origin and a 2D direction vector.
   *  \param p Origin point.
   *  \param v Direction vector.
   */
  Ray(Point2D p, Vector2D v) : o(p), d(v) {}

  /** \brief A list initializer constructor.
   *
   *  You can create a Ray 2D with two lists (origin and direction) of 2 values:
   *
   *        Ray2D r({o1, o2}, {d1, d2})
   *
   *  or
   *
   *        Ray2D r = {{o1, o2}, {d1, d2}}
   *  \param lo list of coordinates that defines the origin point of the Ray
   *  \param lv list of dimensions that defines the direction vector of the Ray
   */
  Ray(std::initializer_list<double> lo, std::initializer_list<double> lv) : o(lo), d(lv) {}

  Point2D o;   //!< Origin data.
  Vector2D d;  //!< Direction data.
};

using Ray2D = Ray<2>;  //!< An alias to Ray<2>.

/** \brief A class ZBEAPI that represent a 3D Ray (an origin and a direction).
 *
 *  Ray3D is an alias of Ray<3>.
 *
 *  This specialization let you access with the alias .x, .y and .z to the first, second and third dimensions of the Ray attributes (origin and direction).
 */
template <>
struct Ray<3> {
  /** \brief Void constructor, the 3D Ray's values are unknown.
   */
  Ray() : o(), d() {}

  /** \brief Parametrized constructor.
   *
   *  A 3D Ray is constructed with a 3D point to the origin and a 3D director vector.
   */
  Ray(Point3D p, Vector3D v) : o(p), d(v) {}

  /** \brief A list initializer constructor.
   *
   *  You can create a Ray 3D with two lists (origin and direction) of 3 values:
   *
   *        Ray3D r({o1, o2, o3}, {d1, d2, d3})
   *
   *  or
   *
   *        Ray3D r = {{o1, o2, o3}, {d1, d2, d3}}
   *  \param lo list of coordinates that defines the origin point of the Ray
   *  \param lv list of dimensions that defines the direction vector of the Ray
   */
  Ray(std::initializer_list<double> lo, std::initializer_list<double> lv) : o(lo), d(lv) {}

  Point3D o;   //!< Origin data.
  Vector3D d;  //!< Direction data.
};

using Ray3D = Ray<3>;  //!< An alias to Ray<3>.

/** \brief A class ZBEAPI that represent a NSphere (a center and a radius).
 *
 *  This template needs to know the number of dimensions of the hyperplane to which the Nsphere belongs to.
 */
template <unsigned s>
struct NSphere {
  /** \brief Void constructor, the NSphere's values are unknown.
   */
  NSphere() {}

  /** \brief Parametrized constructor.
   *
   *  A NSphere is constructed with a point to the center and a radius.
   */
  NSphere(Point<s> center, double radius) : c(center), r(radius) {}

  /** \brief A list initializer constructor.
   *
   *  You can create a NSphere of N dimension with a list of N values (the center) and another value, the radius:
   *
   *        NSphere<N> s({c1, c2, ... , cN}, radius)
   *
   *  or
   *
   *        NSphere<N> s = {{c1, c2, ... , cN}, radius}
   *  \param lc list of coordinates that defines the center point of the NSphere
   *  \param r radius
   */
  NSphere(std::initializer_list<double> lc, double r) : c(lc), r(r) {}

  Point<s> c;  //!< Center data.
  double r;    //!< Radius data.
};

/** \brief A class ZBEAPI that represent a Circle (NSphere of 2 dimensions).
 *
 *  Circle is an alias of NSphere<2>.
 *
 *  This specialization let you access with the alias .x and .y to the first and second dimensions of the Circle center.
 */
template <>
struct NSphere<2> {
  /** \brief Void constructor, the Circle's values are unknown.
   */
  NSphere() : c(), r() {}

  /** \brief Parametrized constructor.
   *
   *  A Circle is constructed with a 2D point to the center and a radius.
   */
  NSphere(Point2D center, double radius) : c(center), r(radius) {}

  /** \brief A list initializer constructor.
   *
   *  You can create a Circle with a list of 2 values (the center) and another value, the radius:
   *
   *        Circle c({c1, c2}, radius)
   *
   *  or
   *
   *        Circle c = {{c1, c2}, radius}
   *  \param lc list of coordinates that defines the center point of the NSphere
   *  \param r radius
   */
  NSphere(std::initializer_list<double> lc, double r) : c(lc), r(r) {}

  Point2D c;  //!< Center data.
  double r;   //!< Radius data.
};

using Circle = NSphere<2>;  //!< An alias to NSphere<2>.

/** \brief A class ZBEAPI that represent a Sphere (NSphere of 3 dimensions).
 *
 *  Sphere is an alias of NSphere<3>.
 *
 *  This specialization let you access with the alias .x, .y and .z to the first, second and third dimensions of the Sphere center.
 */
template <>
struct NSphere<3> {
  /** \brief Void constructor, the Sphere's values are unknown.
   */
  NSphere() : c(), r() {}

  /** \brief Parametrized constructor.
   *
   *  A Sphere is constructed with a 3D point to the center and a radius.
   */
  NSphere(Point3D center, double radius) : c(center), r(radius) {}

  /** \brief A list initializer constructor.
   *
   *  You can create a Sphere with a list of 3 values (the center) and another value, the radius:
   *
   *        Sphere c({c1, c2, c3}, radius)
   *
   *  or
   *
   *        Sphere c = {{c1, c2, c3}, radius}
   *  \param lc list of coordinates that defines the center point of the NSphere
   *  \param r radius
   */
  NSphere(std::initializer_list<double> lc, double r) : c(lc), r(r) {}

  Point3D c;  //!< Center data.
  double r;   //!< Radius data.
};

using Sphere = NSphere<3>;  //!< An alias to NSphere<3>.

/** \brief A class ZBEAPI that represent an Axis Aligned Bounding Box (AABB).
 *
 *  An AABB is defined by two opposite corners. This corners are obtained with the minimum and maximum values its dimensions.
 *
 *  This template needs to know the number of dimensions of the hyperplane to which the AABB belongs to.
 */
template <unsigned s>
struct AABB {
  /** \brief Void constructor, the AABB's values are unknown.
   */
  AABB() {}

  /** \brief Parametrized constructor.
   *
   *  An AABB is constructed with two N dimensional points to the minimum and maximum corners.
   */
  AABB(Point<s> pmin, Point<s> pmax) : minimum(pmin), maximum(pmax) {}

  /** \brief A list initializer constructor.
   *
   *  You can create an AABB of N dimension with two lists of N values each (the minimum and maximum corners):
   *
   *        AABB<N> b({min1, min2, ... , minN}, {max1, max2, ... , maxN})
   *
   *  or
   *
   *        AABB<N> b = {{min1, min2, ... , minN}, {max1, max2, ... , maxN}}
   *  \param lmin list of coordinates that defines the "minimun" point of the AABB.
   *  \param lmax list of coordinates that defines the "maximum" point of the AABB.
   */
  AABB(std::initializer_list<double> lmin, std::initializer_list<double> lmax) : minimum(lmin), maximum(lmax) {}

  Point<s> minimum;  //!< minimum corner.
  Point<s> maximum;  //!< maximum corner.
};

/** \brief A class ZBEAPI that represent an Axis Aligned Bounding Box (AABB).
 *
 *  An AABB is defined by two opposite corners. This corners are obtained with the minimum and maximum values of x and y.
 *
 *  AABB2D is an alias of AABB<2>.
 *
 *  This specialization let you access with the alias .x and .y to the first and second dimension of the AABB corners.
 */
template <>
struct AABB<2> {
  /** \brief Void constructor, the AABB2D's values are unknown.
   */
  AABB() : minimum(), maximum() {}

  /** \brief Parametrized constructor.
   *
   *  An AABB2D is constructed with two 2D points to the minimum and maximum corners.
   */
  AABB(Point2D pmin, Point2D pmax) : minimum(pmin), maximum(pmax) {}

  /** \brief A list initializer constructor.
   *
   *  You can create an AABB2D with two lists of 2 values each (the minimum and maximum corners):
   *
   *        AABB2D b({min1, min2}, {max1, max2})
   *
   *  or
   *
   *        AABB2D b = {{min1, min2}, {max1, max2}}
   *  \param lmin list of coordinates that defines the "minimun" point of the AABB.
   *  \param lmax list of coordinates that defines the "maximum" point of the AABB.
   */
  AABB(std::initializer_list<double> lmin, std::initializer_list<double> lmax) : minimum(lmin), maximum(lmax) {}

  Point2D minimum;  //!< minimum corner.
  Point2D maximum;  //!< maximum corner.
};

using AABB2D = AABB<2>;  //!< An alias to AABB<2>.

/** \brief A class ZBEAPI that represent an Axis Aligned Bounding Box (AABB).
 *
 *  An AABB is defined by two opposite corners. This corners are obtained with the minimum and maximum values of x and y and z.
 *
 *  AABB3D is an alias of AABB<3>.
 *
 *  This specialization let you access with the alias .x, .y and .z to the first, second and third dimension of the AABB corners.
 */
template <>
struct AABB<3> {
  /** \brief Void constructor, the AABB3D's values are unknown.
   */
  AABB() : minimum(), maximum() {}

  /** \brief Parametrized constructor.
   *
   *  An AABB3D is constructed with two 3D points to the minimum and maximum corners.
   */
  AABB(Point3D pmin, Point3D pmax) : minimum(pmin), maximum(pmax) {}

  /** \brief A list initializer constructor.
   *
   *  You can create an AABB3D with two lists of 3 values each (the minimum and maximum corners):
   *
   *        AABB2D b({min1, min2, min3}, {max1, max2, max3})
   *
   *  or
   *
   *        AABB2D b = {{min1, min2, min3}, {max1, max2, max3}}
   *  \param lmin list of coordinates that defines the "minimun" point of the AABB.
   *  \param lmax list of coordinates that defines the "maximum" point of the AABB.
   */
  AABB(std::initializer_list<double> lmin, std::initializer_list<double> lmax) : minimum(lmin), maximum(lmax) {}

  Point3D minimum;  //!< minimum corner.
  Point3D maximum;  //!< maximum corner.
};

using AABB3D = AABB<3>;  //!< An alias to AABB<3>.

template<unsigned dim>
struct Triangle {
  Point<dim> a, b, c;
};

template<>
struct Triangle<2> {
  Point2D a, b, c;
};

using Triangle2D = Triangle<2>;

template<>
struct Triangle<3> {
  Point3D a, b, c;
};

using Triangle3D = Triangle<3>;

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_OBJECTS_H_
