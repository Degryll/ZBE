/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionSystemSolver.h
 * @since 2016-05-01
 * @date 2016-06-05
 * @author Degryll
 * @brief Apply the correct function to solve a collision.
 */

#ifndef ZBE_CORE_TOOLS_MATH_COLLISIONS_COLLISIONSYSTEMSOLVER_H_
#define ZBE_CORE_TOOLS_MATH_COLLISIONS_COLLISIONSYSTEMSOLVER_H_

#include <cstdint>

#include "ZBE/core/entities/CollisionerEntity.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/collisions/intersections.h"

namespace zbe {

class StaticAABB2D;
class ConstantMovingCircle;

/** \brief Apply the correct function to solve a collision.
 */
class CollisionSelector {
  public:
    inline bool select(CollisionerEntity& param1, CollisionerEntity& param2, uint64_t& time, Point2D& point) {
      return (param2.getCollisionObject().accept(*this, param1.getCollisionObject(), time, point));
    }

    inline bool visit(StaticAABB2D& param1, StaticAABB2D& param2, uint64_t& time, Point2D& point);
    inline bool visit(StaticAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point);
    inline bool visit(ConstantMovingCircle& param1, StaticAABB2D& param2, uint64_t& time, Point2D& point);
    inline bool visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point);
};

// You must add to this macro a new "accept" function for any new derived CollisionObject
// This macro is used to avoid repeated code
#define DERIVEDCOLLISIONOBJECT \
  bool accept(CollisionSelector &visitor, CollisionObject& param1, uint64_t& time, Point2D& point) { \
    return (param1.accept(visitor, *this, time, point)); \
  } \
 \
  bool accept(CollisionSelector &visitor, StaticAABB2D& param2, uint64_t& time, Point2D& point) { \
    return (visitor.visit(*this, param2, time, point)); \
  } \
 \
  bool accept(CollisionSelector &visitor, ConstantMovingCircle& param2, uint64_t& time, Point2D& point) { \
    return (visitor.visit(*this, param2, time, point)); \
  } \

class StaticAABB2D: public CollisionObject {
public:
  DERIVEDCOLLISIONOBJECT

  inline AABB2D& getAABB2D() {return (box);}

private:
  AABB2D box;
};

class ConstantMovingCircle: public CollisionObject {
public:
  DERIVEDCOLLISIONOBJECT

  inline Circle& getCircle() {return (circle);}
  inline Vector2D& getDirection() {return (direction);}

private:
  Circle circle;
  Vector2D direction;
};

bool CollisionSelector::visit(StaticAABB2D& param1, StaticAABB2D& param2, uint64_t& time, Point2D& point) {
  // TODO Degryll implementar AABB contra AABB
  return (false);
}

bool CollisionSelector::visit(StaticAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point) {
  return(IntersectionMovingCircleAABB2D(param2.getCircle(), param2.getDirection(), param1.getAABB2D(), time, point));
}

bool CollisionSelector::visit(ConstantMovingCircle& param1, StaticAABB2D& param2, uint64_t& time, Point2D& point) {
  return(IntersectionMovingCircleAABB2D(param1.getCircle(), param1.getDirection(), param2.getAABB2D(), time, point));
}

bool CollisionSelector::visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point) {
  // TODO Degryll implementar ConstantMovingSphere contra ConstantMovingSphere
  return (false);
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_COLLISIONS_COLLISIONSYSTEMSOLVER_H_
