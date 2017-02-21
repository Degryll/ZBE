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
bool intersectionRayInsideAABB(Ray<dim> ray, AABB<dim> box, int64_t tmax, int64_t &time, Point<dim>& point);
inline bool intersectionRayInsideAABB2D(Ray2D ray, AABB2D box, int64_t tmax, int64_t &time, Point2D& point) {return (intersectionRayInsideAABB<2>(ray, box, tmax, time, point));} //!< 2D allias of intersectionRayInsideAABB.
inline bool intersectionRayInsideAABB3D(Ray3D ray, AABB3D box, int64_t tmax, int64_t &time, Point3D& point) {return (intersectionRayInsideAABB<3>(ray, box, tmax, time, point));} //!< 3D allias of intersectionRayInsideAABB.

template <unsigned dim>
unsigned intersectionRayAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);
inline bool intersectionRayAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionRayAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionRayAABB.
inline bool intersectionRayAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionRayAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionRayAABB.

template <unsigned dim>
bool intersectionSegmentAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);
inline bool intersectionSegmentAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionSegmentAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionSegmentAABB.
inline bool intersectionSegmentAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionSegmentAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionSegmentAABB.

template <unsigned dim>
bool intersectionMovingNSphereOutsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point);
inline bool IntersectionMovingCircleOutsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point) {return (intersectionMovingNSphereOutsideAABB<2>(circle,direction,box,time,point));}  //!< 2D allias of IntersectionMovingNSphereOutsideAABB.
inline bool IntersectionMovingSphereOutsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t& time, Point3D& point) {return (intersectionMovingNSphereOutsideAABB<3>(sphere,direction,box,time,point));}  //!< 3D allias of IntersectionMovingNSphereOutsideAABB.

template <unsigned dim>
bool intersectionMovingNSphereInsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t tmax, int64_t& time, Point<dim>& point);
inline bool IntersectionMovingCircleInsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t tmax, int64_t& time, Point2D& point) {return (intersectionMovingNSphereInsideAABB<2>(circle,direction,box, tmax,time,point));}  //!< 2D allias of IntersectionMovingNSphereInsideAABB.
inline bool IntersectionMovingSphereInsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t tmax, int64_t& time, Point3D& point) {return (intersectionMovingNSphereInsideAABB<3>(sphere,direction,box, tmax,time,point));}  //!< 3D allias of IntersectionMovingNSphereInsideAABB.

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

  int64_t a = ray.d * ray.d;
  if(a == 0) return(false);
  int64_t b = (f * ray.d) * 2;
  int64_t c = (f * f) - (nsphere.r * nsphere.r);

  if (c > 0 && b > 0) return (false);

  int64_t discr = b * b - 4 * a * c;

  if (discr < 0) return (false);

  int64_t taux = time;
  int64_t t = ((-b - (int64_t)sqrt(discr)) / (2 * a));
  if (t < 0) t = 0;
  if (t > taux) return (false);
  taux = t;

  point = ray.o + ray.d * taux;
  time = taux;

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
  int64_t b = f * ray.d;
  int64_t c = (f * f) - (nsphere.r * nsphere.r);

  if (c > 0 && b > 0) return (false);

  int64_t discr = b * b - c;

  if (discr < 0) return (false);

  int64_t taux = time;
  int64_t t = (-b - (int64_t)sqrt(discr));
  if (t < 0) t = 0;
  if (t > taux) return (false);
  taux = t;
  point = ray.o + ray.d * taux;
  time = taux;

  return (true);
}

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  Don't use this function directly, use:
 *    intersectionRayAABB: to test an infinite ray with an AABB
 *    intersectionSegmentAABB: to test a finite segment with an ABB
 *
 * \param ray A ray defined by its origin and a direction.
 * \param nsphere An AABB defined by its minimum and maximum corners.
 * \param tmin If the collision happens before this time, is discarded.
 * \param tmax If the collision happens after this time, is discarded.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 * \sa intersectionRayAABB and intersectionSegmentAABB.
 */
template <unsigned dim>
unsigned RayAABB(Ray<dim> ray, AABB<dim> box, int64_t tmin, int64_t tmax, int64_t &time, Point<dim>& point) {
  //double tmind = tmin * TIMETOVELOCITY;
  //double tmaxd = tmax * TIMETOVELOCITY;
  int64_t taux  = time;
  unsigned collidedFaces = 0;
  bool isZero = true;  // the direction is (0,...,0)
  for(unsigned i = 0; i < dim; i++) {
    int64_t d    = ray.d[i];
    if (d == 0) continue;
    isZero = false;
    int64_t o    = ray.o[i];
    int64_t bmin = box.minimum[i];
    int64_t bmax = box.maximum[i];
    int64_t n1 = (bmin - o);
    int64_t n2 = (bmax - o);

    if((o < bmin && d < n1) || (o > bmax && d > n2)) {return (false);}

    //double ood = 1.0 / d;
    int64_t t1 = ((n1 << PRECISION_DIGITS) / d);
    int64_t t2 = ((n2 << PRECISION_DIGITS) / d);
    int dimState = 0;
    if(t1 > 0) {
      if (t2 < t1) {
        dimState = 1;
      } else {
        dimState = 2;
      }
    }
    collidedFaces = collidedFaces || (dimState << 2*i);

    if(t1 > t2) {std::swap(t1,t2);}
    if(t1 > tmin) {tmin = t1;}
    if(t2 < tmax) {tmax = t2;}


    if(tmin > tmax) {return (false);}
  }  // for each dimension

  if (isZero) return(false);
  if(tmin > taux) {return (false);}

  time = roundPrecision(tmax);

  for(unsigned i = 0; i < dim; i++) {
    point[i] = ray.o[i] + ((ray.d[i] * time) >> PRECISION_DIGITS);
  }
  return (collidedFaces);
}

template <unsigned dim>
bool intersectionRayInsideAABB(Ray<dim> ray, AABB<dim> box, int64_t tmax, int64_t &time, Point<dim>& point) {
  int64_t taux = std::numeric_limits<int64_t>::max();
  for(unsigned i = 0; i < dim; i++) {
    if (ray.d[i] == 0) continue;
  	int64_t t1 = ((box.minimum[i] - ray.o[i]) << PRECISION_DIGITS) / ray.d[i];
    int64_t t2 = ((box.maximum[i] - ray.o[i]) << PRECISION_DIGITS) / ray.d[i];

    int64_t t = roundPrecision(std::max(t1, t2));
    taux = std::min(taux, t);
  }

  time = taux;
  if ((taux <= tmax) && (taux != 0)) {
    for(unsigned i = 0; i < dim; i++) {
      point[i] = ray.o[i] + mult(ray.d[i], time);
    }
    return true;
  }
  return false;
}

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  This function considerate the ray an infinite ray.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param nsphere An AABB defined by its minimum and maximum corners.
 * \param tmin If the collision happens before this time, is discarded.
 * \param tmax If the collision happens after this time, is discarded.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 * \sa intersectionSegmentAABB.
 */
template <unsigned dim>
unsigned intersectionRayAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point) {
  int64_t tmin = 0;
  int64_t tmax = std::numeric_limits<int64_t>::max();

  return (RayAABB<dim>(ray, box, tmin, tmax, time, point));
}

/** \brief Computes the collision of a N-dimensional Ray and AABB.
 *
 *  This function considerate the ray a infinite segment.
 *
 * \param ray A ray defined by its origin and a direction.
 * \param nsphere An AABB defined by its minimum and maximum corners.
 * \param tmin If the collision happens before this time, is discarded.
 * \param tmax If the collision happens after this time, is discarded.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 * \sa intersectionRayAABB.
 */
template <unsigned dim>
bool intersectionSegmentAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point) {
  int64_t tmin = 0;
  int64_t tmax = 1 << PRECISION_DIGITS;

  return (RayAABB<dim>(ray, box, tmin, tmax, time, point));
}

/** \brief Computes the collision of a moving circle with an AABB. Outside approaching.
 *
 * \param Circle The moving circle.
 * \param direction The velocity of the moving sphere.
 * \param box The static AABB.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 */
template <unsigned dim>
bool intersectionMovingNSphereOutsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point) {
  int64_t r = nsphere.r;
  AABB<dim> e = box;
  for(unsigned i = 0; i < dim; i++) {
    e.minimum[i] -= r;
    e.maximum[i] += r;
  }

  int64_t t = time;

  Ray<dim> ray(nsphere.c, direction);
  if (!intersectionRayAABB<dim>(ray, e, t, point) || t > time) {return (false);}
  int64_t bmin[dim];
  int64_t bmax[dim];
  for(unsigned i = 0; i < dim; i++) {
    bmin[i] = box.minimum[i];
    bmax[i] = box.maximum[i];
  }
  Point<dim> c;
  int m=0;
  for(unsigned i = 0; i < dim; i++) {
    if (point[i] < bmin[i]) {m++; c[i] = bmin[i]; point[i] += r;}
    if (point[i] > bmax[i]) {m++; c[i] = bmax[i]; point[i] -= r;}
  }

  // The collision happens at the corner of the expansion box
  // Check if there is an intersection with the vertex.
  if (m == dim) {
    return (intersectionRayNSphere<dim>(ray, NSphere<dim>(c,r), time, point));
  }

  time = t;
  // The intersection with the expanded AABB e is the correct.
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
bool intersectionMovingNSphereInsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t tmax, int64_t& time, Point<dim>& point) {
  int64_t r = nsphere.r;
  AABB<dim> e = box;
  for(unsigned i = 0; i < dim; i++) {
    e.minimum[i] += r;
    e.maximum[i] -= r;
  }

  int64_t t;
  Ray<dim> ray(nsphere.c, direction);
  if(intersectionRayInsideAABB<dim>(ray, e, tmax, t, point) && (t <= tmax)) {
    for(unsigned i = 0; i < dim; i++) {
      int64_t minDistance = mult(direction[i], TIME_QUANTUM);
      if((e.minimum[i] - point[i]) >= minDistance) {
      	point[i] -= r;
      } else if ((e.maximum[i] - point[i]) <= minDistance) {
      	point[i] += r;
      }
    }
    time = t;
    return (true);
  }

  return (false);
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_
