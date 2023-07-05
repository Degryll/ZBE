/**
 * Copyright 2012 Batis Degryll Ludo
 * @file intersection.cpp
 * @since 2017-03-04
 * @date 2017-03-04
 * @author Degryll Ludo Batis
 * @brief Functions for detect time and point of collision.
 */

#include "ZBE/core/tools/math/collisions/intersections.h"
#include "ZBE/core/system/system.h"

namespace zbe {

bool IntersectionMovingSphereOutsideAABB3D(Sphere, Vector3D, AABB3D, int64_t&, Point3D&) {SysError::setError("IntersectionMovingSphereOutsideAABB3D: Not implemented yet."); return false;}

bool intersectionCircleCircle(Circle circlea, Circle circleb) {return intersectionNSphereNSphere<2>(circlea, circleb);}
bool intersectionSphereSphere(Sphere spherea, Sphere sphereb) {return intersectionNSphereNSphere<3>(spherea, sphereb);}

bool intersectionCircleAABB2D(Circle circle, AABB<2> box) {return intersectionNSphereAABB<2>(circle, box);}
bool intersectionSphereAABB3D(Sphere sphere, AABB<3> box) {return intersectionNSphereAABB<3>(sphere, box);}

bool intersectionPoint2DAABB2D(Point2D point, AABB<2> box) {return intersectionPointAABB<2>(point, box);}
bool intersectionPoint3DAABB3D(Point3D point, AABB<3> box) {return intersectionPointAABB<3>(point, box);}

bool intersectionPoint2DCircle(Point2D point, Circle circle) {return intersectionPointNSphere<2>(point, circle);}
bool intersectionPoint3DSphere(Point3D point, Sphere sphere) {return intersectionPointNSphere<3>(point, sphere);}

bool intersectionRayCircle(Ray2D ray, Circle circle, int64_t &time, Point2D& point) {return (intersectionRayNSphere<2>(ray,circle,time,point));}
bool intersectionRaySphere(Ray3D ray, Sphere sphere, int64_t &time, Point3D& point) {return (intersectionRayNSphere<3>(ray,sphere,time,point));}

bool intersectionNormalRayCircle(Ray2D ray, Circle circle, int64_t &time, Point2D& point) {return (intersectionNormalRayNSphere<2>(ray,circle,time,point));}
bool intersectionNormalRaySphere(Ray3D ray, Sphere sphere, int64_t &time, Point3D& point) {return (intersectionNormalRayNSphere<3>(ray,sphere,time,point));}

bool intersectionBeamInsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionBeamInsideAABB<2>(ray, box, time, point));}
bool intersectionBeamInsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionBeamInsideAABB<3>(ray, box, time, point));}

bool intersectionSegmentOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionSegmentOutsideAABB<2>(ray,box,time,point));}
bool intersectionSegmentOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionSegmentOutsideAABB<3>(ray,box,time,point));}

bool intersectionBeamOutsideAABB2D(Ray2D ray, AABB2D box, int64_t &time, Point2D& point) {return (intersectionBeamOutsideAABB<2>(ray,box,time,point));}
bool intersectionBeamOutsideAABB3D(Ray3D ray, AABB3D box, int64_t &time, Point3D& point) {return (intersectionBeamOutsideAABB<3>(ray,box,time,point));}

bool IntersectionMovingCircleInsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point, Vector<2>& normal) {return (intersectionMovingNSphereInsideAABB<2>(circle,direction,box, time,point, normal));}
bool IntersectionMovingSphereInsideAABB3D(Sphere sphere, Vector3D direction, AABB3D box, int64_t& time, Point3D& point, Vector<3>& normal) {return (intersectionMovingNSphereInsideAABB<3>(sphere,direction,box, time,point, normal));}

/** \brief Computes the collision of a moving circle with an AABB. Outside approach.
 *
 * \param Circle The moving circle.
 * \param direction The velocity of the moving sphere.
 * \param box The static AABB.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 */
bool ZBEAPI IntersectionMovingCircleOutsideAABB2D(Circle circle, Vector2D direction, AABB2D box, int64_t& time, Point2D& point, Vector2D& normal) {
  double r = circle.r;
  AABB2D e = box;
  e.minimum[0] -= r;
  e.minimum[1] -= r;
  e.maximum[0] += r;
  e.maximum[1] += r;

  int64_t t = time;
  Point2D c;
  Ray2D ray(circle.c, direction);

  if (intersectionBeamOutsideAABB2D(ray, e, t, point)) {
    if (t > time) {return (false);}
    normal = {.0,.0};
    int m=0;
    for(unsigned i = 0; i < 2; i++) {
      if (point[i] < box.minimum[i]) {m++; c[i] = box.minimum[i]; point[i] += r; normal[i] = -1.0;}
      if (point[i] > box.maximum[i]) {m++; c[i] = box.maximum[i]; point[i] -= r; normal[i] = 1.0;}
    }

    // The collision happens at the corner of the expansion box
    // Check if there is an intersection with the vertex.
    if (m == 2) {
      t = time;
      point = c;
      normal = circle.c - c;
      if(!intersectionRayCircle(ray, Circle(c,r), t, c) || (t > time)) return (false);
    }
    time = t;
    // The intersection with the expanded AABB e is the correct.
    return (true);

  } else {  // No extended box collision
    int m=0;
    for(unsigned i = 0; i < 2; i++) {
      if (circle.c[i] < box.minimum[i]) {m++; c[i] = box.minimum[i];}
      if (circle.c[i] > box.maximum[i]) {m++; c[i] = box.maximum[i];}
    }

    if (m == 2) {
      t = time;
      point = c;
      normal = circle.c - c;
      if(!intersectionRayCircle(ray, Circle(c,r), t, c) || (t > time)) return (false);
      time = t;
      return (true);
    } else {  // 4 vertex collision
      c[0] = box.minimum[0];
      c[1] = box.minimum[1];
      if(intersectionRayCircle(ray, Circle(c,r), t, c) && (t > time)) {
        point = c;
        time = t;
        normal = circle.c - c;
        return (true);
      }
      c[0] = box.minimum[0];
      c[1] = box.maximum[1];
      if(intersectionRayCircle(ray, Circle(c,r), t, c) && (t > time)) {
        point = c;
        time = t;
        normal = circle.c - c;
        return (true);
      }
      c[0] = box.maximum[0];
      c[1] = box.minimum[1];
      if(intersectionRayCircle(ray, Circle(c,r), t, c) && (t > time)) {
        point = c;
        time = t;
        normal = circle.c - c;
        return (true);
      }
      c[0] = box.maximum[0];
      c[1] = box.maximum[1];
      if(intersectionRayCircle(ray, Circle(c,r), t, c) && (t > time)) {
        point = c;
        time = t;
        normal = circle.c - c;
        return (true);
      }
    }  // if m == 2
        return (false);
  }  // if extended box collision
}

bool ZBEAPI intersectionMovingRay2DRay2D(Ray2D r1, Ray2D r2, int64_t& time, Point2D& point, Vector2D& normal) {
    Vector2D d1 = r1.d;
    Vector2D d2 = r2.d;
    Vector2D n2 = Vector2D{d2.y, -d2.x};
    n2.normalize();

    double h = dot((r1.o - r2.o), n2); // height of the first point of l1 on vector l2
    double hd = dot(d1, n2);  // height differential of the vector that defines l1

    // const double threshold = 0.0f;  // A threshold where height differential is considered to correspond to parallel lines
    // if(std::abs(hd) <= threshold) {
    //     return false;
    // }
    if(almost_equal(hd, 0.0)) {
        return false;
    }
    double t = (h/ -hd);
    point = r1.o + (d1 * t);
    auto intersectTime = quantizeTime(t);

    if(intersectTime <= time) {
      time = intersectTime;
      normal = n2;
      return time > 0;  // Only if time > 0
  } else {
      return false;
  }
}

}  // namespace zbe
