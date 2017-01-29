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
bool intersectionRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, uint64_t &time, Point<dim>& point);
inline bool intersectionRayCircle(Ray2D ray, Circle circle, uint64_t &time, Point2D& point) {return (intersectionRayNSphere<2>(ray,circle,time,point));}  //!< 2D allias of intersectionRayNSphere.
inline bool intersectionRaySphere(Ray3D ray, Sphere sphere, uint64_t &time, Point3D& point) {return (intersectionRayNSphere<3>(ray,sphere,time,point));}  //!< 3D allias of intersectionRayNSphere.

template <unsigned dim>
bool intersectionNormalRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, uint64_t &time, Point<dim>& point);
inline bool intersectionNormalRayCircle(Ray2D ray, Circle circle, uint64_t &time, Point2D& point) {return (intersectionNormalRayNSphere<2>(ray,circle,time,point));}  //!< 2D allias of intersectionNormalRayNSphere.
inline bool intersectionNormalRaySphere(Ray3D ray, Sphere sphere, uint64_t &time, Point3D& point) {return (intersectionNormalRayNSphere<3>(ray,sphere,time,point));}  //!< 3D allias of intersectionNormalRayNSphere.

template <unsigned dim>
bool intersectionRayAABB(Ray<dim> ray, AABB<dim> box, uint64_t &time, Point<dim>& point);
inline bool intersectionRayAABB2D(Ray2D ray, AABB2D box, uint64_t &time, Point2D& point) {return (intersectionRayAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionRayAABB.
inline bool intersectionRayAABB3D(Ray3D ray, AABB3D box, uint64_t &time, Point3D& point) {return (intersectionRayAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionRayAABB.

template <unsigned dim>
bool intersectionSegmentAABB(Ray<dim> ray, AABB<dim> box, uint64_t &time, Point<dim>& point);
inline bool intersectionSegmentAABB2D(Ray2D ray, AABB2D box, uint64_t &time, Point2D& point) {return (intersectionSegmentAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionSegmentAABB.
inline bool intersectionSegmentAABB3D(Ray3D ray, AABB3D box, uint64_t &time, Point3D& point) {return (intersectionSegmentAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionSegmentAABB.

template <unsigned dim>
bool intersectionMovingNSphereOutsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, uint64_t& time, Point<dim>& point);
inline bool IntersectionMovingCircleOutsideAABB2D(Circle circle, Vector2D direction, AABB2D box, uint64_t& time, Point2D& point) {return (intersectionMovingNSphereOutsideAABB<2>(circle,direction,box,time,point));}  //!< 2D allias of IntersectionMovingNSphereOutsideAABB.
inline bool IntersectionMovingSphereOutsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, uint64_t& time, Point3D& point) {return (intersectionMovingNSphereOutsideAABB<3>(sphere,direction,box,time,point));}  //!< 3D allias of IntersectionMovingNSphereOutsideAABB.

template <unsigned dim>
bool intersectionMovingNSphereInsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, uint64_t& time, Point<dim>& point);
inline bool IntersectionMovingCircleInsideAABB2D(Circle circle, Vector2D direction, AABB2D box, uint64_t& time, Point2D& point) {return (intersectionMovingNSphereInsideAABB<2>(circle,direction,box,time,point));}  //!< 2D allias of IntersectionMovingNSphereInsideAABB.
inline bool IntersectionMovingSphereInsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, uint64_t& time, Point3D& point) {return (intersectionMovingNSphereInsideAABB<3>(sphere,direction,box,time,point));}  //!< 3D allias of IntersectionMovingNSphereInsideAABB.

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
bool intersectionRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, uint64_t &time, Point<dim>& point) {
  Vector<dim> f = ray.o - nsphere.c;

  double a = ray.d * ray.d;
  double b = (f * ray.d) * 2;
  double c = (f * f) - (nsphere.r * nsphere.r);

  if (c > 0 && b > 0) return (false);

  double discr = b * b - 4 * a * c;

  if (discr < 0) return (false);

  double taux = time * TIMETOVELOCITY;
  double t = ((-b - sqrt(discr)) / (2 * a));
  if (t < 0) t = 0;
  if (t > taux) return (false);
  taux = t;

  point = ray.o + ray.d * taux;
  time = (uint64_t)(taux * VELOCITYTOTIME);

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
bool intersectionNormalRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, uint64_t &time, Point<dim>& point) {
  Vector<dim> f = ray.o - nsphere.c;

  //  because r.d is a unit vector, r.d dot r.d  = 1
  double b = f * ray.d;
  double c = (f * f) - (nsphere.r * nsphere.r);

  if (c > 0 && b > 0) return (false);

  double discr = b * b - c;

  if (discr < 0) return (false);

  double taux = time * TIMETOVELOCITY;
  double t = (-b - sqrt(discr));
  if (t < 0) t = 0;
  if (t > taux) return (false);
  taux = t;
  point = ray.o + ray.d * taux;
  time = (uint64_t)(taux * VELOCITYTOTIME);

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
bool RayAABB(Ray<dim> ray, AABB<dim> box, uint64_t tmin, uint64_t tmax, uint64_t &time, Point<dim>& point) {
  double tmind = tmin * TIMETOVELOCITY;
  double tmaxd = tmax * TIMETOVELOCITY;
  double taux  = time * TIMETOVELOCITY;

  for(unsigned i = 0; i < dim; i++) {
    double bmin = box.minimum[i];
    double bmax = box.maximum[i];
    double o    = ray.o[i];
    double d    = ray.d[i];
    double n1 = bmin - o;
    double n2 = bmax - o;

    if((o < bmin && d < n1) || (o > bmax && d > n2)) {return (false);}

    double ood = 1.0 / d;
    double t1 = (n1 * ood);
    double t2 = (n2 * ood);

    if(t1 > t2) {std::swap(t1,t2);}
    if(t1 > tmind) {tmind = t1;}
    if(t2 < tmaxd) {tmaxd = t2;}

    if(tmind > tmaxd) {return (false);}
  }  // for each dimension

  if(tmind > taux) {return (false);}

  point = ray.o + ray.d * tmind;
  time = tmind * VELOCITYTOTIME;
  return (true);
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
bool intersectionRayAABB(Ray<dim> ray, AABB<dim> box, uint64_t &time, Point<dim>& point) {
  uint64_t tmin = 0;
  uint64_t tmax = std::numeric_limits<uint64_t>::max();

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
bool intersectionSegmentAABB(Ray<dim> ray, AABB<dim> box, uint64_t &time, Point<dim>& point) {
  uint64_t tmin = 0;
  uint64_t tmax = VELOCITYTOTIME;

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
bool intersectionMovingNSphereOutsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, uint64_t& time, Point<dim>& point) {
  double r = nsphere.r;
  AABB<dim> e = box;
  for(unsigned i = 0; i < dim; i++) {
    e.minimum[i] -= r;
    e.maximum[i] += r;
  }

  uint64_t t = time;

  Ray<dim> ray(nsphere.c, direction);
  if (!intersectionRayAABB<dim>(ray, e, t, point) || t > time) {return (false);}
  double bmin[dim];
  double bmax[dim];
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
bool intersectionMovingNSphereInsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, uint64_t& time, Point<dim>& point) {
  double r = nsphere.r;
  AABB<dim> e = box;
  for(unsigned i = 0; i < dim; i++) {
    e.minimum[i] += r;
    e.maximum[i] -= r;
  }

  uint64_t t = time;

  Ray<dim> ray(nsphere.c, direction);
  return (intersectionRayAABB<dim>(ray, e, t, point) && t < time);
}

/**************************************************************/
/*                                                            */
/*             OLD 2D IMPLEMENTATION                          */
/*                                                            */
/**************************************************************/
///** \brief Computes the collision of a moving circle with an AABB.
// *
// * \param Circle The moving circle.
// * \param direction The velocity of the moving sphere.
// * \param box The static AABB.
// * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
// * \param point Stores the point of collision, if any.
// * \return True if there is a collision before the initial value of time, false otherwise.
// */
//bool IntersectionMovingCircleAABB2D(Circle circle, Vector2D direction, AABB2D box, uint64_t& time, Point2D& point) {
//  double r = circle.r;
//  AABB2D e = box;
//  e.minimum[0] -= r; e.minimum[1] -= r;
//  e.maximum[0] += r; e.maximum[1] += r;
//
//  uint64_t t = time;
//
//  Ray2D ray(circle.c,direction);
//  if (!intersectionRayAABB2D(ray, e, t, point) || t > time) {return (false);}
//  double bmin0 = box.minimum[0];
//  double bmax0 = box.maximum[0];
//  double bmin1 = box.minimum[1];
//  double bmax1 = box.maximum[1];
//  Point2D c;
//  int m=0;
//  if (point.x < bmin0) {m++; c.x = bmin0; point[0] += r;}
//  if (point.x > bmax0) {m++; c.x = bmax0; point[0] -= r;}
//  if (point.y < bmin1) {m++; c.y = bmin1; point[1] += r;}
//  if (point.y > bmax1) {m++; c.y = bmax1; point[1] -= r;}
//
//  // The collision happens at the corner of the expansion box
//  // Check if there is an intersection with the vertex.
//  if (m == 2) {
//    return (intersectionRayCircle(ray, Circle(c,r), time, point));
//  }
//
//  time = t;
//  // The intersection with the expanded AABB e is the correct.
//  return (true);
//}


//bool IntersectionMovingSphereAABB(Sphere s, Vector d, AABB b, float &t) {
//  // Compute the AABB resulting from expanding b by sphere radius r
//  AABB e = b;
//  e.min.x -= s.r; e.min.y -= s.r; e.min.z -= s.r;
//  e.max.x += s.r; e.max.y += s.r; e.max.z += s.r;
//
//  // Intersect ray against expanded AABB e. Exit with no intersection if ray
//  // misses e, else get intersection point p and time t as result
//  Point p;
//  if (!IntersectRayAABB(s.c, d, e, t, p) || t > 1.0f) {return 0;}
//
//  // Compute which min and max faces of b the intersection point p lies
//  // outside of. Note, u and v cannot have the same bits set and
//  // they must have at least one bit set among them
//  int u = 0, v = 0;
//  if (p.x < b.min.x) u |= 1;
//  if (p.x > b.max.x) v |= 1;
//  if (p.y < b.min.y) u |= 2;
//  if (p.y > b.max.y) v |= 2;
//  if (p.z < b.min.z) u |= 4;
//  if (p.z > b.max.z) v |= 4;
//
//  // ‘Or’ all set bits together into a bit mask (note: here u + v == u | v)
//  int m = u + v;
//
//  // Define line segment [c, c+d] specified by the sphere movement
//  Segment seg(s.c, s.c + d);
//
//  // If all 3 bits set (m == 7) then p is in a vertex region
//  if (m == 7) {
//    // Must now intersect segment [c, c+d] against the capsules of the three
//    // edges meeting at the vertex and return the best time, if one or more hit
//    float tmin = FLT_MAX;
//    if (IntersectSegmentCapsule(seg, Corner(b, v), Corner(b, v ^ 1), s.r, &t)) {tmin = Min(t, tmin);}
//    if (IntersectSegmentCapsule(seg, Corner(b, v), Corner(b, v ^ 2), s.r, &t)) {tmin = Min(t, tmin);}
//    if (IntersectSegmentCapsule(seg, Corner(b, v), Corner(b, v ^ 4), s.r, &t)) {tmin = Min(t, tmin);}
//
//    if (tmin == FLT_MAX) {return 0;} // No intersection
//    t = tmin;
//    return 1; // Intersection at time t == tmin
//  }
//
//  // If only one bit set in m, then p is in a face region
//  if ((m & (m - 1)) == 0) {
//    // Do nothing. Time t from intersection with
//    // expanded box is correct intersection time
//    return 1;
//  }
//
//  // p is in an edge region. Intersect against the capsule at the edge
//  return IntersectSegmentCapsule(seg, Corner(b, u ^ 7), Corner(b, v), s.r, &t);
//}
//
//// Support function that returns the AABB vertex with index n
//Point Corner(AABB b, int n) {
//  Point p;
//  p.x = ((n & 1) ? b.max.x : b.min.x);
//  p.y = ((n & 2) ? b.max.y : b.min.y);
//  p.z = ((n & 4) ? b.max.z : b.min.z);
//  return p;
//}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_
