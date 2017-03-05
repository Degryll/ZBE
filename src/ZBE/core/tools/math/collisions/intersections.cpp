/**
 * Copyright 2012 Batis Degryll Ludo
 * @file intersection.cpp
 * @since 2017-03-04
 * @date 2017-03-04
 * @author Degryll Ludo Batis
 * @brief Functions for detect time and point of collision.
 */

#include "ZBE/core/tools/math/collisions/intersections.h"

namespace zbe {

/** \brief Computes the collision of a moving circle with an AABB. Outside approach.
 *
 * \param NSphere<2> The moving circle.
 * \param direction The velocity of the moving sphere.
 * \param box The static AABB.
 * \param time Initialy it has a limit time, if the collision happens before that time, its value is updated.
 * \param point Stores the point of collision, if any.
 * \return True if there is a collision before the initial value of time, false otherwise.
 */
bool IntersectionMovingCircleOutsideAABB2D(NSphere<2> nsphere, Vector<2> direction, AABB<2> box, int64_t& time, Point<2>& point) {
  double r = nsphere.r;
  AABB<2> e = box;
  e.minimum[0] -= r;
  e.minimum[1] -= r;
  e.maximum[0] += r;
  e.maximum[1] += r;

  int64_t t = time;
  Point<2> c;
  Ray<2> ray(nsphere.c, direction);

  if ((nsphere.c[0] > e.minimum[0]) && (nsphere.c[0] < e.maximum[0])
  &&  ((nsphere.c[1] > e.minimum[1]) && (nsphere.c[1] < e.maximum[1]))) {
    for(unsigned i = 0; i < 2; i++) {
      if (nsphere.c[i] < box.minimum[i]) {c[i] = box.minimum[i]; point[i] = box.minimum[i];}
      if (nsphere.c[i] > box.maximum[i]) {c[i] = box.maximum[i]; point[i] = box.maximum[i];}
    }

    if(!intersectionRayNSphere<2>(ray, NSphere<2>(c,r), t, c) || (t > time)) {return (false);}

    time = t;
    return (true);
  }

  if (!intersectionBeamOutsideAABB<2>(ray, e, t, point) || t > time) {return (false);}

  int m=0;
  for(unsigned i = 0; i < 2; i++) {
    if (point[i] < box.minimum[i]) {m++; c[i] = box.minimum[i]; point[i] += r;}
    if (point[i] > box.maximum[i]) {m++; c[i] = box.maximum[i]; point[i] -= r;}
  }

  // The collision happens at the corner of the expansion box
  // Check if there is an intersection with the vertex.
  if (m == 2) {
    t = time;
    point = c;
    if(!intersectionRayNSphere<2>(ray, NSphere<2>(c,r), t, c) || (t > time)) return (false);
  }

  time = t;
  // The intersection with the expanded AABB e is the correct.
  return (true);
}

}  // namespace zbe