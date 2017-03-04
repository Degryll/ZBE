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

  Ray<2> ray(nsphere.c, direction);
  if (!intersectionBeamOutsideAABB<2>(ray, e, t, point) || t > time) {return (false);}
  double bmin[2];
  double bmax[2];
  for(unsigned i = 0; i < 2; i++) {
    bmin[i] = box.minimum[i];
    bmax[i] = box.maximum[i];
  }
  Point<2> c;
  int m=0;
  for(unsigned i = 0; i < 2; i++) {
    if (point[i] < bmin[i]) {m++; c[i] = bmin[i]; point[i] += r;}
    if (point[i] > bmax[i]) {m++; c[i] = bmax[i]; point[i] -= r;}
  }

  // The collision happens at the corner of the expansion box
  // Check if there is an intersection with the vertex.
  if (m == 2) {
    return (intersectionRayNSphere<2>(ray, NSphere<2>(c,r), time, point));
  }

  time = t;
  // The intersection with the expanded AABB e is the correct.
  return (true);
}

}  // namespace zbe
