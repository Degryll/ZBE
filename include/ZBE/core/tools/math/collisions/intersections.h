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

#include <utility>
#include <limits>
#include <cstdint>

#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"

namespace zbe {

/** \brief Tells if two AABB intersects.
 *  \param boxa AABB a.
 *  \param boxb AABB b.
 */
template <unsigned dim>
bool intersectionAABBAABB(AABB<dim> boxa, AABB<dim> boxb);

/** \brief Tells if two n-dimensional spheres intersects.
 *  \param NSpherea Sphere a.
 *  \param NSphereb Sphere b.
 */
template <unsigned dim>
bool intersectionNSphereNSphere(NSphere<dim> nspherea, NSphere<dim> nsphereb);

/** \brief Tells if two circles (2d sphere) intersects.
 *  \param circlea Circle a.
 *  \param circleb Circle b.
 */
inline bool intersectionCircleCircle(Circle circlea, Circle circleb) {return intersectionNSphereNSphere<2>(circlea, circleb);}

/** \brief Tells if two 3d spheres intersects.
 *  \param spherea Sphere a.
 *  \param sphereb Sphere b.
 */
inline bool intersectionSphereSphere(Sphere spherea, Sphere sphereb) {return intersectionNSphereNSphere<3>(spherea, sphereb);}


/** \brief Tells if a n-dimensional sphere and a AABB intersects.
 *  \param sphere Sphere.
 *  \param box AABB.
 */
template <unsigned dim>
bool intersectionNSphereAABB(NSphere<dim> sphere, AABB<dim> box);

/** \brief Tells if a circle and a 2d AABB intersects.
 *  \param circle Circle.
 *  \param box AABB.
 */
inline bool intersectionCircleAABB2D(Circle circle, AABB<2> box) {return intersectionNSphereAABB<2>(circle, box);}

/** \brief Tells if a 3d sphere and a 3d AABB intersects.
 *  \param sphere Sphere.
 *  \param box AABB.
 */
inline bool intersectionSphereAABB3D(Sphere sphere, AABB<3> box) {return intersectionNSphereAABB<3>(sphere, box);}


/** \brief Tells if a n-dimensional point is into a n-dimensional AABB.
 *  \param point Point.
 *  \param box AABB.
 */
template <unsigned dim>
bool intersectionPointAABB(Point<dim> point, AABB<dim> box);

/** \brief Tells if a 2d point is into a 2d AABB.
 *  \param point Point.
 *  \param box AABB.
 */
inline bool intersectionPoint2DAABB2D(Point2D point, AABB<2> box) {return intersectionPointAABB<2>(point, box);}

/** \brief Tells if a 3d point is into a 3d AABB.
 *  \param point Point.
 *  \param box AABB.
 */
inline bool intersectionPoint3DAABB3D(Point3D point, AABB<3> box) {return intersectionPointAABB<3>(point, box);}


/** \brief Tells if a n-dimensional point is into a n-dimensional sphere.
 *  \param point Point.
 *  \param nsphere Sphere.
 */
template <unsigned dim>
bool intersectionPointNSphere(Point<dim> point, NSphere<dim> nsphere);

/** \brief Tells if a 2d point is into a circle.
 *  \param point Point.
 *  \param circle Circle.
 */
inline bool intersectionPoint2DCircle(Point2D point, Circle circle) {return intersectionPointNSphere<2>(point, circle);}

/** \brief Tells if a 3d point is into a 3d sphere.
 *  \param point Point.
 *  \param nsphere Sphere.
 */
inline bool intersectionPoint3DSphere(Point3D point, Sphere sphere) {return intersectionPointNSphere<3>(point, sphere);}


/** \brief Tells if a n-dimensional ray and a n-dimensional sphere intersects and
 * stores the time of the "collision" and the coordinates where it occured into
 * two parameters.
 *  \param ray Ray.
 *  \param sphere Sphere.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
template <unsigned dim>
bool intersectionRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, int64_t &time, Point<dim>& point);

/** \brief Tells if a 2d ray and a circle intersects and stores the time of the
 "collision" and the coordinates where it occured into two parameters.
 *  \param ray Ray.
 *  \param circle Circle.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionRayCircle(Ray2D ray, Circle circle, int64_t &time, Point2D& point) {return (intersectionRayNSphere<2>(ray,circle,time,point));}

/** \brief Tells if a 3d ray and a 3d sphere intersects and stores the time of
 the "collision" and the coordinates where it occured into two parameters.
 *  \param ray Ray.
 *  \param sphere Sphere.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionRaySphere(Ray3D ray, Sphere sphere, int64_t &time, Point3D& point) {return (intersectionRayNSphere<3>(ray,sphere,time,point));}


/** \brief Tells if a normalized n-dimensional ray and a n-dimensional sphere
intersects and stores the time of the "collision" and the coordinates where it
occured into two parameters.
 *  \param ray Ray.
 *  \param sphere Sphere.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
template <unsigned dim>
bool intersectionNormalRayNSphere(Ray<dim> ray, NSphere<dim> nsphere, int64_t &time, Point<dim>& point);

/** \brief Tells if a normalized 2d ray and a circle intersects and stores the
time of the "collision" and the coordinates where it occured into two parameters.
 *  \param ray Ray.
 *  \param circle Circle.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionNormalRayCircle(Ray2D ray, Circle circle, int64_t &time, Point2D& point) {return (intersectionNormalRayNSphere<2>(ray,circle,time,point));}

/** \brief Tells if a normalized 3d ray and a 3d sphere intersects and stores the
time of the "collision" and the coordinates where it occured into two parameters.
 *  \param ray Ray.
 *  \param sphere Sphere.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionNormalRaySphere(Ray3D ray, Sphere sphere, int64_t &time, Point3D& point) {return (intersectionNormalRayNSphere<3>(ray,sphere,time,point));}


/** \brief Tells if a n-dimensional beam and a AABB intersects (ray moving inside
 AABB) and stores the time of the "collision" and the coordinates where it occured
 into two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
template <unsigned dim>
bool intersectionBeamInsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);

/** \brief Tells if a 2d beam and a 2d AABB intersects and (ray moving inside
AABB) stores the time of the "collision" and the coordinates where it occured
into two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionBeamInsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionBeamInsideAABB<2>(ray, box, time, point));}

/** \brief Tells if a 3d beam and a 3d AABB intersects (ray moving inside AABB)
and stores the time of the "collision" and the coordinates where it occured into
two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionBeamInsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionBeamInsideAABB<3>(ray, box, time, point));}


/************************************/
/* EL QUANTIZER DE TIEMPO NO FUNCIONA CON NEGATIVOS TODO: Esto parece que afecta a cosas. O no.*/
/*************************************/
//template <unsigned dim>
//bool intersectionRayOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);
//inline bool intersectionRayOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionRayOutsideAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionRayOutsideAABB.
//inline bool intersectionRayOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionRayOutsideAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionRayOutsideAABB.


/** \brief Tells if a n-dimensional segment and a AABB intersects (ray moving
outside AABB) and stores the time of the "collision" and the coordinates
where it occured into two parameters.
 *  \param ray Segment.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
template <unsigned dim>
bool intersectionSegmentOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);

/** \brief Tells if a 2d segment and a 2d AABB intersects (ray moving outside
AABB) and stores the time of the "collision" and the coordinates where it occured
into two parameters.
 *  \param ray Segment.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionSegmentOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionSegmentOutsideAABB<2>(ray,box,time,point));}  //!< 2D allias of intersectionSegmentOutsideAABB.

/** \brief Tells if a 3d segment and a 3d AABB intersects (ray moving outside
AABB) and stores the time of the "collision" and the coordinates where it occured
into two parameters.
 *  \param ray Segment.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionSegmentOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionSegmentOutsideAABB<3>(ray,box,time,point));}  //!< 3D allias of intersectionSegmentOutsideAABB.


/** \brief Tells if a n-dimensional beam and a AABB intersects (ray moving outside
AABB) and stores the time of the "collision" and the coordinates where it occured
into two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
template <unsigned dim>
bool intersectionBeamOutsideAABB(Ray<dim> ray, AABB<dim> box, int64_t &time, Point<dim>& point);

/** \brief Tells if a 2d beam and a 2d AABB intersects (ray moving outside AABB)
and stores the time of the "collision" and the coordinates where it occured into
two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionBeamOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionBeamOutsideAABB<2>(ray,box,time,point));}

/** \brief Tells if a 3d beam and a 3d AABB intersects (ray moving outside AABB)
and stores the time of the "collision" and the coordinates where it occured into
two parameters.
 *  \param ray Beam.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 */
inline bool intersectionBeamOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionBeamOutsideAABB<3>(ray,box,time,point));}


/** \brief Tells if a n-dimensional moving sphere and a AABB intersects (sphere
moving inside AABB) and stores the time of the "collision", the coordinates where
it occured, and the normal into parameters.
 *  \param nsphere Sphere.
 *  \param direction Sphere's moving direction vector.
 *  \param box AABB.
 *  \param time Initialy it has a limit time, if the collision happens before that time, this value is updated to the collision time.
 *  \param point Intersection location.
 *  \param normal Stores the collision point's normal.
 */
template <unsigned dim>
bool intersectionMovingNSphereInsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point, Vector<dim>& normal);

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
inline bool IntersectionMovingCircleInsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point, Vector<2>& normal) {return (intersectionMovingNSphereInsideAABB<2>(circle,direction,box, time,point, normal));}

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
inline bool IntersectionMovingSphereInsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t& time, Point3D& point, Vector<3>& normal) {return (intersectionMovingNSphereInsideAABB<3>(sphere,direction,box, time,point, normal));}  //!< 3D allias of IntersectionMovingNSphereInsideAABB.


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
bool intersectionMovingNSphereOutsideAABB(NSphere<dim> nsphere, Vector<dim> direction, AABB<dim> box, int64_t& time, Point<dim>& point);
//inline bool IntersectionMovingCircleOutsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point) {return (intersectionMovingNSphereOutsideAABB<2>(circle,direction,box,time,point));}  //!< 2D allias of IntersectionMovingNSphereOutsideAABB.
inline bool IntersectionMovingSphereOutsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t& time, Point3D& point) {return (intersectionMovingNSphereOutsideAABB<3>(sphere,direction,box,time,point));}  //!< 3D allias of IntersectionMovingNSphereOutsideAABB.

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
bool IntersectionMovingCircleOutsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point, Vector2D& normal);

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
bool intersectionNSphereNSphere(NSphere<dim> nspherea, NSphere<dim> nsphereb){
  double rsum = nspherea.r + nsphereb.r;
  double r2 = rsum * rsum;
  return sqrPointDist(nspherea.c, nsphereb.c) < r2;
}

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
}

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

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_COLLISIONS_INTERSECTIONS_H_
