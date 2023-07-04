/**
 * Copyright 2012 Batis Degryll Ludo
 * @file intersection.h
 * @since 2015-05-17
 * @date 2018-03-25
 * @author Degryll Ludo Batis
 * @brief Functions for detect time and point of collision.
 */

#ifndef ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_
#define ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_

#include <algorithm>
#include <utility>
#include <limits>
#include <cstdint>
#include <iostream>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

/** \brief Tells if a n-dimensional moving sphere and a AABB intersects (sphere
moving outside AABB) and stores the time of the "collision", the coordinates where
it occured, and the normal into parameters.
 *  \param nsphere Sphere.
 *  \param direction Sphere's moving direction vector.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 *  \param normal Stores the collision point's normal.
 */
template <unsigned dim>
bool intersectionMovingNSphereOutsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point) {SysError::setError("intersectionMovingNSphereOutsideAABB: Not implemented yet."); return false;}
//inline bool IntersectionMovingCircleOutsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point) {return (intersectionMovingNSphereOutsideAABB<2>(circle,direction,box,time,point));}  //!< 2D allias of IntersectionMovingNSphereOutsideAABB.
ZBEAPI bool IntersectionMovingSphereOutsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t& time, Point3D& point);  //!< 3D allias of IntersectionMovingNSphereOutsideAABB.

/** \brief Tells if a moving circle and a 2d AABB intersects (circle moving outside
AABB) and stores the time of the "collision", the coordinates where it occured,
and the normal into parameters.
 *  \param nsphere Sphere.
 *  \param direction Sphere's moving direction vector.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 *  \param normal Stores the collision point's normal.
 */
ZBEAPI bool IntersectionMovingCircleOutsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point, Vector2D& normal);

/** \brief A template function that tell if two AABB boxes intersects.
 *
 *  \param boxa The box A.
 *  \param boxb The box B.
 * \return True if the boxes intersects, false otherwise.
 * \sa intersectionAABBAABB.
 */
template <unsigned dim>
bool intersectionAABBAABB(AABB<dim> boxa, AABB<dim> boxb) {
  for(unsigned i = 0; i < dim; i++) {
    if(abs(boxa.minimum[i] - boxb.minimum[i]) * 2 >= ((boxa.maximum[i] - boxa.minimum[i]) + (boxb.maximum[i] - boxb.minimum[i]))) {
        return false;
    }
  }
  return true;
}

/** \brief A template function that tell if two N-dimensional Spheres intersects.
 *
 *  \param spherea The sphere A.
 *  \param sphereb The sphere B.
 * \return True if the spheres intersects, false otherwise.
 * \sa intersectionNSphereNSphere.
 */
template <unsigned dim>
bool intersectionNSphereNSphere(NSphere<dim> nspherea, NSphere<dim> nsphereb) {
  double rsum = nspherea.r + nsphereb.r;
  double r2 = rsum * rsum;
  return sqrPointDist(nspherea.c, nsphereb.c) < r2;
}

/** \brief Tells if two circles (2d sphere) intersects.
 *  \param circlea Circle a.
 *  \param circleb Circle b.
 */
ZBEAPI bool intersectionCircleCircle(Circle circlea, Circle circleb);

/** \brief Tells if two 3d spheres intersects.
 *  \param spherea Sphere a.
 *  \param sphereb Sphere b.
 */
ZBEAPI bool intersectionSphereSphere(Sphere spherea, Sphere sphereb);

/** \brief A template function that tell if an N-dimensional Sphere intersects an AABB.
 *
 *  \param sphere The sphere.
 *  \param box The AABB to test intersection.
 * \return True if the sphere intersects the AABB, false otherwise.
 * \sa intersectionNSphereAABB.
 */
template <unsigned dim>
bool intersectionNSphereAABB(NSphere<dim> sphere, AABB<dim> box) {
  double r2 = sphere.r * sphere.r;
  double mins_dist = 0;
  for(unsigned i = 0; i < dim; i++) {
    if( sphere.c[i] < box.minimum[i] ) {
      double dist = sphere.c[i] - box.minimum[i];
      mins_dist += (dist * dist);
    } else if( sphere.c[i] > box.maximum[i] ) {
      double dist = sphere.c[i] - box.maximum[i];
      mins_dist += (dist * dist);
    }
  }
  return mins_dist <= r2;
}

/** \brief Tells if a circle and a 2d AABB intersects.
 *  \param circle Circle.
 *  \param box AABB.
 */
ZBEAPI bool intersectionCircleAABB2D(Circle circle, AABB<2> box);

/** \brief Tells if a 3d sphere and a 3d AABB intersects.
 *  \param sphere Sphere.
 *  \param box AABB.
 */
ZBEAPI bool intersectionSphereAABB3D(Sphere sphere, AABB<3> box);

/** \brief A template function that tell if an N-dimensional Point is inside an AABB.
 *
 *  \param point The point.
 *  \param box The AABB to test intersection.
 * \return True if the point is inside the AABB, false otherwise.
 * \sa intersectionPointAABB.
 */
template <unsigned dim>
bool intersectionPointAABB(Point<dim> point, AABB<dim> box) {
  for(unsigned i = 0; i < dim; i++) {
    if (point[i]<box.minimum[i] || point[i]>box.maximum[i]){
      return false;
    }
  }
  return true;
}

/** \brief Tells if a 2d point is into a 2d AABB.
 *  \param point Point.
 *  \param box AABB.
 */
ZBEAPI bool intersectionPoint2DAABB2D(Point2D point, AABB<2> box);

/** \brief Tells if a 3d point is into a 3d AABB.
 *  \param point Point.
 *  \param box AABB.
 */
ZBEAPI bool intersectionPoint3DAABB3D(Point3D point, AABB<3> box);

/** \brief A template function that tell if an N-dimensional Point is inside an NSphere.
 *
 *  \param point The point.
 *  \param nsphere The nsphere (a circle in 2D or a sphere in 3D) to test intersection.
 * \return True if the point is inside the NSphere, false otherwise.
 * \sa intersectionPointNSphere.
 */
template <unsigned dim>
bool intersectionPointNSphere(Point<dim> point, NSphere<dim> nsphere) {
    double sqrRadius = nsphere.r * nsphere.r;
    return sqrPointDist(point, nsphere.c) < sqrRadius;
}

/** \brief Tells if a 2d point is into a circle.
 *  \param point Point.
 *  \param circle Circle.
 */
ZBEAPI bool intersectionPoint2DCircle(Point2D point, Circle circle);

/** \brief Tells if a 3d point is into a 3d sphere.
 *  \param point Point.
 *  \param nsphere Sphere.
 */
ZBEAPI bool intersectionPoint3DSphere(Point3D point, Sphere sphere);

/** \brief A template function that compute the time and point of collision (if any) of an N-dimensional ray and a NSphere.
 *
 *  \param ray A ray defined by its origin and a direction.
 *  \param nsphere The nsphere (a circle in 2D or a sphere in 3D) to test against the ray.
 *  \param time Initialy it has a limit time, if the collision happend before that time, this value is updated to the collision time.
 *  \param point Stores the point of collision, if any.
 * \return True if there is a collision between the ray and the nsphere before the initial value of time, false otherwise.
 * \sa intersectionNormalRayNSphere.
 */
template <unsigned dim>
bool intersectionRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, int64_t &time, Point<dim>& point) {
  Vector<dim> f = ray.o - nsphere.c;

  double a = ray.d * ray.d;
  if(isNearlyEqual(a, 0.0, 0.0)) return(false);
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

/** \brief Tells if a 2d ray and a circle intersects and stores the time of the
 "collision" and the coordinates where it occured into two parameters.
 *  \param ray Ray.
 *  \param circle Circle.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionRayCircle(Ray2D ray, Circle circle, int64_t &time, Point2D& point);

/** \brief Tells if a 3d ray and a 3d sphere intersects and stores the time of
 the "collision" and the coordinates where it occured into two parameters.
 *  \param ray Ray.
 *  \param sphere Sphere.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionRaySphere(Ray3D ray, Sphere sphere, int64_t &time, Point3D& point);

/** \brief A template function that compute the time and point of collision (if any) of an N-dimensional ray with its director vector normalized and a NSphere.
 *
 *  \param ray A ray defined by its origin and a direction.
 *  \param nsphere The nsphere (a circle in 2D or a sphere in 3D) to test against the ray.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Stores the point of collision, if any.
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

/** \brief Tells if a normalized 2d ray and a circle intersects and stores the
time of the "collision" and the coordinates where it occured into two parameters.
 *  \param ray Ray.
 *  \param circle Circle.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionNormalRayCircle(Ray2D ray, Circle circle, int64_t &time, Point2D& point);

/** \brief Tells if a normalized 3d ray and a 3d sphere intersects and stores the
time of the "collision" and the coordinates where it occured into two parameters.
 *  \param ray Ray.
 *  \param sphere Sphere.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionNormalRaySphere(Ray3D ray, Sphere sphere, int64_t &time, Point3D& point);

/** \brief Computes the collision of a N-dimensional Beam inside and AABB.
 *
 *  This function considerate the ray an infinite ray with an origin.
 *
 *  \param ray A ray defined by its origin and a direction.
 *  \param box An AABB defined by its minimum and maximum corners.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 * \sa intersectionRayOutsideAABB and intersectionSegmentOutsideAABB.
 */
template <unsigned dim>
bool intersectionBeamInsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point) {
  int64_t taux = std::numeric_limits<int64_t>::max();
  for(unsigned i = 0; i < dim; i++) {
    if (abs(ray.d[i]) < PRECISION) continue;
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

/** \brief Tells if a 2d beam and a 2d AABB intersects and (ray moving inside
AABB) stores the time of the "collision" and the coordinates where it occured
into two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionBeamInsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point);

/** \brief Tells if a 3d beam and a 3d AABB intersects (ray moving inside AABB)
and stores the time of the "collision" and the coordinates where it occured into
two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionBeamInsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point);

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  This function considerate the ray an infinite ray.
 *
 *  \param ray A ray defined by its origin and a direction.
 *  \param box An AABB defined by its minimum and maximum corners.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Stores the point of collision, if any.
 * \return True if there is a collision between tmin and tmax, false otherwise.
 * \sa intersectionBeamOutsideAABB and intersectionSegmentOutsideAABB.
 */

/************************************/
/* EL QUANTIZER DE TIEMPO NO FUNCIONA CON NEGATIVOS*/
/*************************************/

/** \brief Computes the collision of a N-dimensional Segment and AABB.
 *
 *  This function considerate the ray a finite segment.
 *
 *  \param ray A ray defined by its origin and a direction.
 *  \param box An AABB defined by its minimum and maximum corners.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Stores the point of collision, if any.
 * \return True if there is a collision between tmin and tmax, false otherwise.
 * \sa intersectionRayOutsideAABB and intersectionBeamOutsideAABB.
 */
template <unsigned dim>
inline bool intersectionSegmentOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim> &point) {
  int64_t tmin = 0;
  int64_t tmax = SECOND;
  return (rayOutsideAABB(ray, box, tmin, tmax, time, point));
}

/** \brief Tells if a 2d segment and a 2d AABB intersects (ray moving outside
AABB) and stores the time of the "collision" and the coordinates where it occured
into two parameters.
 *  \param ray Segment.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionSegmentOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point);  //!< 2D allias of intersectionSegmentOutsideAABB.

/** \brief Tells if a 3d segment and a 3d AABB intersects (ray moving outside
AABB) and stores the time of the "collision" and the coordinates where it occured
into two parameters.
 *  \param ray Segment.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionSegmentOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point);  //!< 3D allias of intersectionSegmentOutsideAABB.

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  This function considerate the ray an infinite ray with an origin.
 *
 *  \param ray A ray defined by its origin and a direction.
 *  \param box An AABB defined by its minimum and maximum corners.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Stores the point of collision, if any.
 * \return True if there is a collision between tmin and tmax, false otherwise.
 * \sa intersectionRayOutsideAABB and intersectionSegmentOutsideAABB.
 */
template <unsigned dim>
inline bool intersectionBeamOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim> &point) {
  int64_t tmin = 0;
  int64_t tmax = std::numeric_limits<int64_t>::max();
  return (rayOutsideAABB(ray, box, tmin, tmax, time, point));
}

/** \brief Tells if a 2d beam and a 2d AABB intersects (ray moving outside AABB)
and stores the time of the "collision" and the coordinates where it occured into
two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionBeamOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point);

/** \brief Tells if a 3d beam and a 3d AABB intersects (ray moving outside AABB)
and stores the time of the "collision" and the coordinates where it occured into
two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
ZBEAPI bool intersectionBeamOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point);

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  Don't use this function directly, use:
 *    intersectionRayAABB: to test an infinite ray with an AABB
 *    intersectionSegmentAABB: to test a finite segment with an ABB
 *    intersectionBeamOutsideAABB: to test a beam from 0 to infinite.
 *
 *  \param ray A ray defined by its origin and a direction.
 *  \param box An AABB defined by its minimum and maximum corners.
 *  \param tmin If the collision happens before this time, is discarded.
 *  \param tmax If the collision happens after this time, is discarded.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Stores the point of collision, if any.
 * \return True if there is a collision between tmin and tmax, false otherwise.
 * \sa intersectionRayOutsideAABB, intersectionSegmentOutsideAABB and intersectionBeamOutsideAABB.
 */

template <unsigned dim>
bool rayOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t tmin, int64_t tmax, int64_t &time, Point<dim> &point) {
  for (unsigned i = 0; i < dim; i++) {
    if (abs(ray.d[i]) < PRECISION) {
      if (ray.o[i] < box.minimum[i] || ray.o[i] > box.maximum[i]) return (false);
    } else {
      double d = (SECOND / ray.d[i]);
      int64_t t1 = quantizeTime((int64_t)((box.minimum[i] - ray.o[i]) * d));
      int64_t t2 = quantizeTime((int64_t)((box.maximum[i] - ray.o[i]) * d));
      if (t1 > t2) std::swap(t1, t2);
      if (t1 > tmin) tmin = t1;
      if (t2 < tmax) tmax = t2;
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
 *  \param Circle The moving NSphere.
 *  \param direction The velocity of the moving NSphere.
 *  \param box The static AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Stores the collision point, if any.
 *  \param normal Stores the collision point's normal, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 */
template <unsigned dim>
bool intersectionMovingNSphereInsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point, Vector<dim>& normal) {
  double r = nsphere.r;
  AABB<dim> e = box;
  for(unsigned i = 0; i < dim; i++) {
    e.minimum[i] += r;
    e.maximum[i] -= r;
  }

  int64_t t = time;
  normal = {.0,.0};
  Ray<dim> ray(nsphere.c, direction);
  if(intersectionBeamInsideAABB<dim>(ray, e, t, point) && (t <= time)) {
    for(unsigned i = 0; i < dim; i++) {
      double minDistance = direction[i] * TIME_QUANTUM_VALUE;
      if((e.minimum[i] - point[i]) >= (minDistance - PRECISION)) {
        point[i] = box.minimum[i];
        normal[i] = 1.0;
      } else if ((e.maximum[i] - point[i]) <= (minDistance + PRECISION)) {
        point[i] = box.maximum[i];
        normal[i] = -1.0;
      }
    }
    time = t;
    return (true);
  }

  return (false);
}

/** \brief Tells if a moving circle and a 2d AABB intersects (circle moving inside
AABB) and stores the time of the "collision", the coordinates where it occured,
and the normal into parameters.
 *  \param nsphere Sphere.
 *  \param direction Sphere's moving direction vector.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 *  \param normal Stores the collision point's normal.
 */
ZBEAPI bool IntersectionMovingCircleInsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point, Vector<2>& normal);

/** \brief Tells if a moving 3d sphere and a 3d AABB intersects (sphere moving
outside AABB) and stores the time of the "collision", the coordinates where it
occured, and the normal into parameters.
 *  \param nsphere Sphere.
 *  \param direction Sphere's moving direction vector.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 *  \param normal Stores the collision point's normal.
 */
ZBEAPI bool IntersectionMovingSphereInsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t& time, Point3D& point, Vector<3>& normal);  //!< 3D allias of IntersectionMovingNSphereInsideAABB.

/** \brief Tells if a moving 3d sphere and a another moving 3d sphere intersects (sphere moving
outside sphere) and stores the time of the "collision", the coordinates where it
occured, and the normal into parameters.
 *  \param sphere1 Sphere.
 *  \param velocity1 moving velocity of s1.
 *  \param sphere2 Sphere.
 *  \param velocity2 moving velocity of s2.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 *  \param normal Stores the collision point's normal.
 */
template<unsigned dim>
bool intersectionMovingNSphereOutsideMovingNSphere(NSphere<dim> sphere1, Vector<dim> velocity1, NSphere<dim> sphere2, Vector<dim> velocity2, int64_t& time, Point<dim>& point, Vector<dim>& normal) {
  Vector<dim> velocity =  velocity1 - velocity2;
  bool result = intersectionMovingNSphereOutsideNSphere(sphere1, velocity, sphere2, time, point, normal);
  if(result) {
    point = point + (velocity2 * time);
  }
  return result;
}

/** \brief Tells if a moving 3d sphere and a another sphere intersects (sphere moving
outside sphere) and stores the time of the "collision", the coordinates where it
occured, and the normal into parameters.
 *  \param sphere1 Sphere.
 *  \param velocity1 moving velocity of s1.
 *  \param sphere2 Sphere.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 *  \param normal Stores the collision point's normal.
 */
template<unsigned dim>
bool intersectionMovingNSphereOutsideNSphere(NSphere<dim> sphere1, Vector<dim> velocity1, NSphere<dim> sphere2, int64_t& time, Point<dim>& point, Vector<dim>& normal) {
  Ray<dim> ray{sphere1.c, velocity1};
  sphere2.r += sphere1.r;
  bool result = intersectionRayNSphere(ray, sphere2, time, point);
  if(result) {
    point += sphere1.r * (sphere2.c - point).normalize();
    normal = point - sphere2.c;
  }
  return result;
}

template<unsigned dim>
double distancePointTriangle(Point<dim>& point, Triangle<dim> triangle, Point<dim>& closestpoint,  Vector<dim>& normal, double& sqrDistance) {
  const double ZERO = 0.0;
  const double ONE = 1.0;
  const double TWO = 2.0;

  Vector<dim> diff = triangle.a - point;
  Vector<dim> edge0 = triangle.b - triangle.a;
  Vector<dim> edge1 = triangle.c - triangle.a;


  double a00 = dot(edge0, edge0);
  double a01 = dot(edge0, edge1);
  double a11 = dot(edge1, edge1);
  double b0 = dot(diff, edge0);
  double b1 = dot(diff, edge1);
  double det = std::max(a00 * a11 - a01 * a01, ZERO);
  double s = a01 * b1 - a11 * b0;
  double t = a01 * b0 - a00 * b1;

  if (s + t <= det) {
    if (s < ZERO) {
        if (t < ZERO) { // region 4
            if (b0 < ZERO) {
                t = ZERO;
                if (-b0 >= a00){
                    s = ONE;
                } else {
                    s = -b0 / a00;
                }
            } else {
                s = ZERO;
                if (b1 >= ZERO) {
                    t = ZERO;
                }
                else if (-b1 >= a11) {
                    t = ONE;
                } else {
                    t = -b1 / a11;
                }
            }
        } else { // region 3
            s = ZERO;
            if (b1 >= ZERO) {
                t = ZERO;
            } else if (-b1 >= a11) {
                t = ONE;
            } else {
                t = -b1 / a11;
            }
        }
    } else if (t < ZERO) { // region 5
        t = ZERO;
        if (b0 >= ZERO) {
            s = ZERO;
        } else if (-b0 >= a00) {
            s = ONE;
        } else {
            s = -b0 / a00;
        }
    } else { // region 0
        // minimum at interior point
        s /= det;
        t /= det;
    }
} else {
    double tmp0, tmp1, numer, denom;

    if (s < ZERO) {
        tmp0 = a01 + b0;
        tmp1 = a11 + b1;
        if (tmp1 > tmp0) {
            numer = tmp1 - tmp0;
            denom = a00 - TWO * a01 + a11;
            if (numer >= denom) {
                s = ONE;
                t = ZERO;
            } else {
                s = numer / denom;
                t = ONE - s;
            }
        } else {
            s = ZERO;
            if (tmp1 <= ZERO) {
                t = ONE;
            } else if (b1 >= ZERO) {
                t = ZERO;
            } else {
                t = -b1 / a11;
            }
        }
    }
    else if (t < ZERO) { // region 6
        tmp0 = a01 + b1;
        tmp1 = a00 + b0;
        if (tmp1 > tmp0) {
            numer = tmp1 - tmp0;
            denom = a00 - TWO * a01 + a11;
            if (numer >= denom) {
                t = ONE;
                s = ZERO;
            } else {
                t = numer / denom;
                s = ONE - t;
            }
        } else {
            t = ZERO;
            if (tmp1 <= ZERO) {
                s = ONE;
            } else if (b0 >= ZERO) {
                s = ZERO;
            } else {
                s = -b0 / a00;
            }
        }
    } else { // region 1
        numer = a11 + b1 - a01 - b0;
        if (numer <= ZERO) {
            s = ZERO;
            t = ONE;
        } else {
            denom = a00 - TWO * a01 + a11;
            if (numer >= denom) {
                s = ONE;
                t = ZERO;
            } else {
                s = numer / denom;
                t = ONE - s;
            }
        }
    }
  }
  // TODO quizas podamos usar normales cacheadas dentro del propio objeto del trinagulo.

  closestpoint = triangle.a + s * edge0 + t * edge1;
  diff = point - closestpoint;
  sqrDistance = dot(diff, diff);
  normal = - diff.normalize();
  return sqrDistance == ZERO;
}

// ----------------------------- Triangles

template<unsigned dim>
bool intersectionMovingNSphereOutsideMovingNTriangle(NSphere<dim> sphere, Vector<dim> sVelocity, Triangle<dim> triangle, Vector<dim> tVelocity, int64_t& time, Point<dim>& point, Vector<dim>& normal) {
    // Test for initial overlap or contact.
    double sqrDistance;
    distancePointTriangle<dim>(sphere.c, triangle, point, normal, sqrDistance);

    double rsqr = sphere.r * sphere.r;
    if (sqrDistance <= rsqr) {
        //time = 0;
        return false;
    }

    //-------
    // To reach here, the sphere and triangle are initially separated.
    // Compute the velocity of the sphere relative to the triangle.
    //-------

    Vector<dim> V = sVelocity - tVelocity;
    double sqrLenV = dot(V, V);
    if (sqrLenV == 0.0) {
        // The sphere and triangle are separated and the sphere is not
        // moving relative to the triangle, so there is no contact.
        // The 'result' is already set to the correct state for this
        // case.
        return false;
    }

    // Compute the triangle edge directions E[], the vector U normal
    // to the plane of the triangle,  and compute the normals to the
    // edges in the plane of the triangle.  TODO: For a nondeforming
    // triangle (or mesh of triangles), these quantities can all be
    // precomputed to reduce the computational cost of the query.  Add
    // another operator()-query that accepts the precomputed values.
    // TODO: When the triangle is deformable, these quantities must be
    // computed, either by the caller or here.  Optimize the code to
    // compute the quantities on-demand (i.e. only when they are
    // needed, but cache them for later use).
    //-------

    std::array<Vector<dim>, 3> E = {
        triangle.b - triangle.a,
        triangle.c - triangle.b,
        triangle.a - triangle.c
    };
    std::array<double, 3> sqrLenE = {
        dot(E[0], E[0]),
        dot(E[1], E[1]),
        dot(E[2], E[2])
    };
    Vector<dim> U = cross(E[0], E[1]).normalize();
    std::array<Vector<dim>, 3> ExU = {
        cross(E[0], U),
        cross(E[1], U),
        cross(E[2], U)
    };

  // Compute the vectors from the triangle vertices to the sphere
  // center.
  //-------
    std::array<Vector<dim>, 3> Delta = {
        sphere.c - triangle.a,
        sphere.c - triangle.b,
        sphere.c - triangle.c
    };

  // Determine where the sphere center is located relative to the
  // planes of the triangle offset faces of the sphere-swept volume.
  //-------
    double dotUDelta0 = dot(U, Delta[0]);
    if (dotUDelta0 >= sphere.r) {
        // The sphere is on the positive side of Dot(U,X-C) = r.  If
        // the sphere will contact the sphere-swept volume at a
        // triangular face, it can do so only on the face of the
        // aforementioned plane.
        double dotUV = dot(U, V);
        if (dotUV >= 0.0) {
            // The sphere is moving away from, or parallel to, the
            // plane of the triangle.  The 'result' is already set to
            // the correct state for this case.
            return false;
        }

        double tbar = (sphere.r - dotUDelta0) / dotUV;
        bool foundContact = true;
        for (int32_t i = 0; i < 3; ++i) {
            double phi = dot(ExU[i], Delta[i]);
            double psi = dot(ExU[i], V);
            if (phi + psi * tbar > 0.0) {
                foundContact = false;
                break;
            }
        }
        if (foundContact) {
            auto intersectTime = quantizeTime(tbar);
            if(intersectTime<=time) {
                time = intersectTime;
                point = sphere.c + time * sVelocity;
                return true && time;
            } else {
                return false;
            }
        }
    } else if (dotUDelta0 <= -sphere.r) {
        // The sphere is on the positive side of Dot(-U,X-C) = r.  If
        // the sphere will contact the sphere-swept volume at a
        // triangular face, it can do so only on the face of the
        // aforementioned plane.
        double dotUV = dot(U, V);
        if (dotUV <= 0.0) {
            // The sphere is moving away from, or parallel to, the
            // plane of the triangle.  The 'result' is already set to
            // the correct state for this case.
            return false;
        }

        double tbar = (-sphere.r - dotUDelta0) / dotUV;
        bool foundContact = true;
        for (int32_t i = 0; i < 3; ++i) {
            double phi = dot(ExU[i], Delta[i]);
            double psi = dot(ExU[i], V);
            if (phi + psi * tbar > 0.0) {
                foundContact = false;
                break;
            }
        }
        if (foundContact) {
            auto intersectTime = quantizeTime(tbar);
            if(intersectTime<=time) {
                time = intersectTime;
                point = sphere.c + time * sVelocity;
                return true && time;
            } else {
                return false;
            }
        }
    }

  // else: The ray-sphere-swept-volume contact point (if any) cannot
  // be on a triangular face of the sphere-swept-volume.

  // The sphere is moving towards the slab between the two planes
  // of the sphere-swept volume triangular faces.  Determine whether
  // the ray intersects the half cylinders or sphere wedges of the
  // sphere-swept volume.

  // Test for contact with half cylinders of the sphere-swept
  // volume.  First, precompute some dot products required in the
  // computations.  TODO: Optimize the code to compute the quantities
  // on-demand (i.e. only when they are needed, but cache them for
  // later use).
  //-------
    //TODO: cambiar estos tipos por vectores.

    std::array<double, 3> del{}, delp{}, nu{};
    for (int32_t im1 = 2, i = 0; i < 3; im1 = i++) {
        del[i] = dot(E[i], Delta[i]);
        delp[im1] = dot(E[im1], Delta[i]);
        nu[i] = dot(E[i], V);
    }

    for (int32_t i = 2, ip1 = 0; ip1 < 3; i = ip1++) {//Vector3<T> hatV = V - E[i] * nu[i] / sqrLenE[i];
        Vector<dim> hatV = V - E[i] * nu[i]/ sqrLenE[i];
        double sqrLenHatV = dot(hatV, hatV);
        if (sqrLenHatV > 0.0) {
            Vector<dim> hatDelta = Delta[i] - E[i] * del[i] / sqrLenE[i];
            double alpha = - dot(hatV, hatDelta);
            if (alpha >= 0.0) {
                double sqrLenHatDelta = dot(hatDelta, hatDelta);
                double beta = alpha * alpha - sqrLenHatV * (sqrLenHatDelta - rsqr);
                if (beta >= 0.0) {
                    double tbar = (alpha - std::sqrt(beta)) / sqrLenHatV;
                    double mu = dot(ExU[i], Delta[i]);
                    double omega = dot(ExU[i], hatV);
                    if (mu + omega * tbar >= 0.0) {
                        if (del[i] + nu[i] * tbar >= 0.0) {
                            if (delp[i] + nu[i] * tbar <= 0.0) {
                                // The constraints are satisfied, so
                                // tbar is the first time of contact.
                                // result.intersectionType = 1;
                                // result.contactTime = tbar;
                                // result.contactPoint = sphere.center + tbar * sphereVelocity;
                                // return result;
                                auto intersectTime = quantizeTime(tbar);
                                if(intersectTime<=time) {
                                    time = intersectTime;
                                    point = sphere.c + time * sVelocity;
                                    return true && time;
                                } else {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

  // Test for contact with sphere wedges of the sphere-swept
  // volume.  We know that |V|^2 > 0 because of a previous
  // early-exit test.

    for (int32_t im1 = 2, i = 0; i < 3; im1 = i++) {
        double alpha = - dot(V, Delta[i]);
        if (alpha >= 0.0)
        {
            double sqrLenDelta = dot(Delta[i], Delta[i]);
            double beta = alpha * alpha - sqrLenV * (sqrLenDelta - rsqr);
            if (beta >= 0.0) {
                double tbar = (alpha - std::sqrt(beta)) / sqrLenV;
                if (delp[im1] + nu[im1] * tbar >= 0.0) {
                    if (del[i] + nu[i] * tbar <= 0.0) {
                        // The constraints are satisfied, so tbar
                        // is the first time of contact.
                        // result.intersectionType = 1;
                        // result.contactTime = tbar;
                        // result.contactPoint = sphere.center + tbar * sphereVelocity;
                        // return result;
                        auto intersectTime = quantizeTime(tbar);
                        if(intersectTime<=time) {
                            time = intersectTime;
                            point = sphere.c + time * sVelocity;
                            return true && time;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return false;
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_
