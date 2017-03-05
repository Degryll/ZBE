/**
 * Copyright 2012 Batis Degryll Ludo
 * @file intersection.h
 * @since 2015-05-17
 * @date 2015-05-22
 * @author Degryll Ludo Batis
 * @brief Functions for detect time and point of collision.
 */

#ifndef ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_
#define ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_

#include <utility>
#include <limits>
#include <cstdint>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"

namespace zbe {

template <unsigned dim>
bool intersectionRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, int64_t &time, Point<dim>& point);
inline bool intersectionRayCircle(Ray2D ray, Circle circle, int64_t &time, Point2D& point) {return (intersectionRayNSphere<2>(ray,circle,time,point));}  //!< 2D allias of intersectionRayNSphere.
inline bool intersectionRaySphere(Ray3D ray, Sphere sphere, int64_t &time, Point3D& point) {return (intersectionRayNSphere<3>(ray,sphere,time,point));}  //!< 3D allias of intersectionRayNSphere.

template <unsigned dim>
bool intersectionNormalRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, int64_t &time, Point<dim>& point);
inline bool intersectionNormalRayCircle(Ray2D ray, Circle circle, int64_t &time, Point2D& point) {return (intersectionNormalRayNSphere<2>(ray,circle,time,point));}  //!< 2D allias of intersectionNormalRayNSphere.
inline bool intersectionNormalRaySphere(Ray3D ray, Sphere sphere, int64_t &time, Point3D& point) {return (intersectionNormalRayNSphere<3>(ray,sphere,time,point));}  //!< 3D allias of intersectionNormalRayNSphere.

template <unsigned dim>
bool intersectionBeamInsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);
inline bool intersectionBeamInsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionBeamInsideAABB<2>(ray, box, time, point));} //!< 2D allias of intersectionRayInsideAABB.
inline bool intersectionBeamInsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionBeamInsideAABB<3>(ray, box, time, point));} //!< 3D allias of intersectionRayInsideAABB.

/************************************/
/* EL QUANTIZER DE TIEMPO NO FUNCIONA CON NEGATIVOS*/
/*************************************/
//template <unsigned dim>
//bool intersectionRayOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);
//inline bool intersectionRayOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionRayOutsideAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionRayOutsideAABB.
//inline bool intersectionRayOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionRayOutsideAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionRayOutsideAABB.

template <unsigned dim>
bool intersectionSegmentOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);
inline bool intersectionSegmentOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionSegmentOutsideAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionSegmentOutsideAABB.
inline bool intersectionSegmentOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionSegmentOutsideAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionSegmentOutsideAABB.

template <unsigned dim>
bool intersectionBeamOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);
inline bool intersectionBeamOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionBeamOutsideAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionBeamOutsideAABB.
inline bool intersectionBeamOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionBeamOutsideAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionBeamOutsideAABB.

template <unsigned dim>
bool intersectionMovingNSphereInsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point);
inline bool IntersectionMovingCircleInsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point) {return (intersectionMovingNSphereInsideAABB<2>(circle,direction,box, time,point));}  //!< 2D allias of IntersectionMovingNSphereInsideAABB.
inline bool IntersectionMovingSphereInsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t& time, Point3D& point) {return (intersectionMovingNSphereInsideAABB<3>(sphere,direction,box, time,point));}  //!< 3D allias of IntersectionMovingNSphereInsideAABB.


template <unsigned dim>
bool intersectionMovingNSphereOutsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point);
//inline bool IntersectionMovingCircleOutsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point) {return (intersectionMovingNSphereOutsideAABB<2>(circle,direction,box,time,point));}  //!< 2D allias of IntersectionMovingNSphereOutsideAABB.
inline bool IntersectionMovingSphereOutsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t& time, Point3D& point) {return (intersectionMovingNSphereOutsideAABB<3>(sphere,direction,box,time,point));}  //!< 3D allias of IntersectionMovingNSphereOutsideAABB.

bool IntersectionMovingCircleOutsideAABB2D(NSphere<2> nsphere, Vector<2> direction, AABB<2> box, int64_t& time, Point<2>& point);

/** \brief A template function that compute the time and point of collision (if any) of an N-dimensional ray and a NSphere.
 *
 *  Compute if there is a collision between a ray and a nspehere before the initial value of time.
 *  Time is updated with the time of an early collision.
 *  Point store the point of collision, if any.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param nsphere The nsphere (a circle in 2D or a sphere in 3D) to test against the ray.
 * \param time Initialy it has a limit time, if the collision happend before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision between the ray and the nsphere before the initial value of time, false otherwise.
 * \sa intersectionNormalRayNSphere.
 */
template <unsigned dim>
bool intersectionRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, int64_t &time, Point<dim>& point) {
  Vector<dim> f = ray.o - nsphere.c;

  double a = ray.d * ray.d;
  if(a == 0) return(false);
  double b = (f * ray.d) * 2;
  double c = (f * f) - (nsphere.r * nsphere.r);

  if (c > 0 && b > 0) return (false);

  double discr = b * b - 4 * a * c;

  if (discr < 0) return (false);

  int64_t t = (int64_t)(((-b - sqrt(discr)) / (2 * a)) * zbe::SECOND);
  t = quantizeTime(t);

  if (t <= 0) return (false);
  if (t > time) return (false);

  time = t;
  point = ray.o + (ray.d * time) * zbe::INVERSE_SECOND;

  return (true);
}

/** \brief A template function that compute the time and point of collision (if any) of an N-dimensional ray with its director vector normalized and a NSphere.
 *
 *  This version requires that the director vector of the ray is normalized.
 *
 *  Compute if there is a collision between a ray and a nspehere before the initial value of time.
 *  Time is updated with the time of an early collision.
 *  Point store the point of collision, if any.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param nsphere The nsphere (a circle in 2D or a sphere in 3D) to test against the ray.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision between the ray and the nsphere before the initial value of time, false otherwise.
 * \sa intersectionRayNSphere.
 */
template <unsigned dim>
bool intersectionNormalRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, int64_t &time, Point<dim>& point) {
  Vector<dim> f = ray.o - nsphere.c;

  //  because r.d is a unit vector, r.d dot r.d  = 1
  double b = f * ray.d;
  double c = (f * f) - (nsphere.r * nsphere.r);

  if (c > 0 && b > 0) return (false);

  double discr = b * b - c;

  if (discr < 0) return (false);

  int64_t t = (int64_t)(-b - sqrt(discr));
  t = quantizeTime(t);
  if (t <= 0) return (false);
  if (t > time) return (false);

  time = t;
  point = ray.o + ray.d * time;

  return (true);
}

/** \brief Computes the collision of a N-dimensional Beam inside and AABB.
 *
 *  This function considerate the ray an infinite ray with an origin.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param box An AABB defined by its minimum and maximum corners.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 * \sa intersectionRayOutsideAABB and intersectionSegmentOutsideAABB.
 */
template <unsigned dim>
bool intersectionBeamInsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point) {
  int64_t taux = std::numeric_limits<int64_t>::max();
  for(unsigned i = 0; i < dim; i++) {
    if (ray.d[i] == 0) continue;
    double d = (SECOND / ray.d[i]);
  	int64_t t1 = (box.minimum[i] - ray.o[i]) * d;
    int64_t t2 = (box.maximum[i] - ray.o[i]) * d;

    int64_t t = quantizeTime(std::max(t1, t2));
    taux = std::min(taux, t);
  }

  if((taux > time) || (taux <= 0)) return (false);

  time = taux;
  point = ray.o + ((ray.d * time) * INVERSE_SECOND);
  return true;
}

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  This function considerate the ray an infinite ray.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param box An AABB defined by its minimum and maximum corners.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision between tmin and tmax, false otherwise.
 * \sa intersectionBeamOutsideAABB and intersectionSegmentOutsideAABB.
 */

/************************************/
/* EL QUANTIZER DE TIEMPO NO FUNCIONA CON NEGATIVOS*/
/*************************************/

//template <unsigned dim>
//inline bool intersectionRayOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim> &point) {
//  int64_t tmin = std::numeric_limits<int64_t>::min();
//  int64_t tmax = std::numeric_limits<int64_t>::max();
//  return (rayOutsideAABB(ray, box, tmin, tmax, time, point));
//}

/** \brief Computes the collision of a N-dimensional Segment and AABB.
 *
 *  This function considerate the ray a finite segment.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param box An AABB defined by its minimum and maximum corners.
 * \param tmin If the collision happens before this time, is discarded.
 * \param tmax If the collision happens after this time, is discarded.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision between tmin and tmax, false otherwise.
 * \sa intersectionRayOutsideAABB and intersectionBeamOutsideAABB.
 */
template <unsigned dim>
inline bool intersectionSegmentOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim> &point) {
  int64_t tmin = 0;
  int64_t tmax = SECOND;
  return (rayOutsideAABB(ray, box, tmin, tmax, time, point));
}

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  This function considerate the ray an infinite ray with an origin.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param box An AABB defined by its minimum and maximum corners.
 * \param tmin If the collision happens before this time, is discarded.
 * \param tmax If the collision happens after this time, is discarded.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision between tmin and tmax, false otherwise.
 * \sa intersectionRayOutsideAABB and intersectionSegmentOutsideAABB.
 */
template <unsigned dim>
inline bool intersectionBeamOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim> &point) {
  int64_t tmin = 0;
  int64_t tmax = std::numeric_limits<int64_t>::max();
  return (rayOutsideAABB(ray, box, tmin, tmax, time, point));
}

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  Don't use this function directly, use:
 *    intersectionRayAABB: to test an infinite ray with an AABB
 *    intersectionSegmentAABB: to test a finite segment with an ABB
 *    intersectionBeamOutsideAABB: to test a beam from 0 to infinite.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param box An AABB defined by its minimum and maximum corners.
 * \param tmin If the collision happens before this time, is discarded.
 * \param tmax If the collision happens after this time, is discarded.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision between tmin and tmax, false otherwise.
 * \sa intersectionRayOutsideAABB, intersectionSegmentOutsideAABB and intersectionBeamOutsideAABB.
 */

template <unsigned dim>
bool rayOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t tmin, int64_t tmax, int64_t &time, Point<dim> &point) {
  for (unsigned i = 0; i < dim; i++) {
    if (abs(ray.d[i]) < PRECISION) {
      // Ray is parallel to slab. No hit if origin not within slab
      if (ray.o[i] < box.minimum[i] || ray.o[i] > box.maximum[i]) return (false);
    } else {
      double d = (SECOND / ray.d[i]);
      // Compute intersection t value of ray with near and far plane of slab
      int64_t t1 = quantizeTime((int64_t)((box.minimum[i] - ray.o[i]) * d));
      int64_t t2 = quantizeTime((int64_t)((box.maximum[i] - ray.o[i]) * d));
      // Make t1 be intersection with near plane, t2 with far plane
      if (t1 > t2) std::swap(t1, t2);
      // Compute the intersection of slab intersection intervals
      if (t1 > tmin) tmin = t1;
      if (t2 < tmax) tmax = t2;
      // Exit with no collision as soon as slab intersection becomes empty
      if (tmin > tmax) return (false);
    }
  }

  if ((tmin > time) || (tmin == 0)) return (false);

  time = tmin;
  point = ray.o + ((ray.d * time) * INVERSE_SECOND);
  return (true);
}

/** \brief Computes the collision of a moving circle with an AABB. Inside approaching.
 *
 * \param Circle The moving circle.
 * \param direction The velocity of the moving sphere.
 * \param box The static AABB.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 */
template <unsigned dim>
bool intersectionMovingNSphereInsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point) {
  double r = nsphere.r;
  AABB<dim> e = box;
  for(unsigned i = 0; i < dim; i++) {
    e.minimum[i] += r;
    e.maximum[i] -= r;
  }

  int64_t t = time;
  Ray<dim> ray(nsphere.c, direction);
  if(intersectionBeamInsideAABB<dim>(ray, e, t, point) && (t <= time)) {
    for(unsigned i = 0; i < dim; i++) {
      double minDistance = direction[i] * TIME_QUANTUM_VALUE;
      if((e.minimum[i] - point[i]) >= (minDistance - PRECISION)) {
      	point[i] -= r;
      } else if ((e.maximum[i] - point[i]) <= (minDistance + PRECISION)) {
      	point[i] += r;
      }
    }
    time = t;
    return (true);
  }

  return (false);
}

///** \brief Computes the collision of a moving circle with an AABB. Outside approach.
// *
// * \param NSphere<2> The moving circle.
// * \param direction The velocity of the moving sphere.
// * \param box The static AABB.
// * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
// * \param point Stores the point of collision, if any.
// * \return True if there is a collision before the initial value of time, false otherwise.
// */
//template <unsigned dim>
//bool intersectionMovingNSphereOutsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point) {
//
//  return (false);
//}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_
