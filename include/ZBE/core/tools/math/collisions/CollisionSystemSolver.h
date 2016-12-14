/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionSystemSolver.h
 * @since 2016-05-01
 * @date 2016-08-04
 * @author Degryll
 * @brief Apply the correct function to solve a collision.
 */

#ifndef ZBE_CORE_TOOLS_MATH_COLLISIONS_COLLISIONSYSTEMSOLVER_H_
#define ZBE_CORE_TOOLS_MATH_COLLISIONS_COLLISIONSYSTEMSOLVER_H_

#include <cstdint>

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/collisions/intersections.h"

namespace zbe {

class StaticAABB2D;
class ConstantMovingCircle;

/** \brief Apply the correct function to solve a collision.
 */
class CollisionSelector {
  public:
    /** \brief Using the Visitor pattern select the correct collision detection function to use depending of the types of the params.
     *  \param param1 First collision object.
     *  \param param2 Second collision object.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool select(Collisioner& param1, Collisioner& param2, uint64_t& time, Point2D& point) {
      return (param2.getCollisionObject()->accept(*this, *(param1.getCollisionObject()), time, point));
    }

    /** \brief Collision detection for two AABB.
     *  \param param1 First AABB.
     *  \param param2 Second AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool visit(StaticAABB2D& param1, StaticAABB2D& param2, uint64_t& time, Point2D& point);
    /** \brief Collision detection for an AABB and a circle.
     *  \param param1 The AABB.
     *  \param param2 The circle.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool visit(StaticAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point);
    /** \brief Collision detection for a circle and an AABB.
     *  \param param1 The circle.
     *  \param param2 The AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool visit(ConstantMovingCircle& param1, StaticAABB2D& param2, uint64_t& time, Point2D& point);

    /** \brief Collision detection for two circles.
     *  \param param1 First circle.
     *  \param param2 Second circle.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point);
};

// You must add to this class a new "accept" function for any new derived CollisionObject
// This class is used to avoid repeated code
template <typename T>
class CollisionObjectCommon : public CollisionObject {
public:
  CollisionObjectCommon(const CollisionObjectCommon&) = delete;
  void operator=(const CollisionObjectCommon&) = delete;

  CollisionObjectCommon(T* collisionObject) : c(collisionObject) {}

  bool accept(CollisionSelector &visitor, CollisionObject& param1, uint64_t& time, Point2D& point) {
    return (param1.accept(visitor, *c, time, point));
  }

  bool accept(CollisionSelector &visitor, StaticAABB2D& param2, uint64_t& time, Point2D& point) {
    return (visitor.visit(*c, param2, time, point));
  }

  bool accept(CollisionSelector &visitor, ConstantMovingCircle& param2, uint64_t& time, Point2D& point) {
    return (visitor.visit(*c, param2, time, point));
  }

private:
  T* c;
};

// You must add to this macro a new "accept" function for any new derived CollisionObject
// This macro is used to avoid repeated code
//define DERIVEDCOLLISIONOBJECT \
//  bool accept(CollisionSelector &visitor, CollisionObject& param1, uint64_t& time, Point2D& point) { \
//    return (param1.accept(visitor, *this, time, point)); \
//  } \
// \
//  bool accept(CollisionSelector &visitor, StaticAABB2D& param2, uint64_t& time, Point2D& point) { \
//    return (visitor.visit(*this, param2, time, point)); \
//  } \
// \
//  bool accept(CollisionSelector &visitor, ConstantMovingCircle& param2, uint64_t& time, Point2D& point) { \
//    return (visitor.visit(*this, param2, time, point)); \
//  } \

/** \brief A collision object defined by a 2D AABB
 */
class StaticAABB2D: public CollisionObjectCommon<StaticAABB2D> {
public:
  //DERIVEDCOLLISIONOBJECT

  StaticAABB2D() : CollisionObjectCommon(this), box() {}
  StaticAABB2D(AABB2D box) : CollisionObjectCommon(this), box(box) {}

  /** \brief Return the 2D AABB.
   *  \return A 2D AABB.
   */
  inline AABB2D& getAABB2D() {return (box);}

private:
  AABB2D box;  //!< The 2D AABB.
};

/** \brief A collision object defined by a circle moving with a constant speed.
 */
class ConstantMovingCircle: public CollisionObjectCommon<ConstantMovingCircle> {
public:
  //DERIVEDCOLLISIONOBJECT

  ConstantMovingCircle() : CollisionObjectCommon(this), circle(), direction() {}
  ConstantMovingCircle(Circle circle, Vector2D direction) : CollisionObjectCommon(this), circle(circle), direction(direction) {}

  /** \brief Return the circle.
   *  \return A circle.
   */
  inline Circle& getCircle() {return (circle);}
  /** \brief Return the circle's movement direction.
   *  \return The direction of movement.
   */
  inline Vector2D& getDirection() {return (direction);}

private:
  Circle circle;       //!< The circle.
  Vector2D direction;  //!< The direction of movement.
};

//bool CollisionSelector::visit(StaticAABB2D& param1, StaticAABB2D& param2, uint64_t& time, Point2D& point) {
bool CollisionSelector::visit(StaticAABB2D& , StaticAABB2D& , uint64_t& , Point2D& ) {
  // TODO Degryll implementar AABB contra AABB
  return (false);
}

bool CollisionSelector::visit(StaticAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point) {
  return(IntersectionMovingCircleAABB2D(param2.getCircle(), param2.getDirection(), param1.getAABB2D(), time, point));
}

bool CollisionSelector::visit(ConstantMovingCircle& param1, StaticAABB2D& param2, uint64_t& time, Point2D& point) {
  return(IntersectionMovingCircleAABB2D(param1.getCircle(), param1.getDirection(), param2.getAABB2D(), time, point));
}

//bool CollisionSelector::visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point) {
bool CollisionSelector::visit(ConstantMovingCircle& , ConstantMovingCircle& , uint64_t& , Point2D& ) {
  // TODO Degryll implementar ConstantMovingSphere contra ConstantMovingSphere
  return (false);
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_COLLISIONS_COLLISIONSYSTEMSOLVER_H_
