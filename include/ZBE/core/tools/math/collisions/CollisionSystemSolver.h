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

#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/collisions/intersections.h"
#include "ZBE/core/entities/avatars/Collisioner.h"

namespace zbe {

template <typename R>
class StaticAABB2D;
template <typename R>
class ConstantMovingCircle;

/** \brief Apply the correct function to solve a collision.
 */
template <typename R>
class CollisionSelector {
  public:
    /** \brief Using the Visitor pattern select the correct collision detection function to use depending of the types of the params.
     *  \param param1 First collision object.
     *  \param param2 Second collision object.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool select(Collisioner<R>& param1, Collisioner<R>& param2, uint64_t& time, Point2D& point) {
      return (param2.getCollisionObject()->accept(*this, *(param1.getCollisionObject()), time, point));
    }

    /** \brief Collision detection for two AABB.
     *  \param param1 First AABB.
     *  \param param2 Second AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool visit(StaticAABB2D<R>& param1, StaticAABB2D<R>& param2, uint64_t& time, Point2D& point);
    /** \brief Collision detection for an AABB and a circle.
     *  \param param1 The AABB.
     *  \param param2 The circle.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool visit(StaticAABB2D<R>& param1, ConstantMovingCircle<R>& param2, uint64_t& time, Point2D& point);
    /** \brief Collision detection for a circle and an AABB.
     *  \param param1 The circle.
     *  \param param2 The AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool visit(ConstantMovingCircle<R>& param1, StaticAABB2D<R>& param2, uint64_t& time, Point2D& point);

    /** \brief Collision detection for two circles.
     *  \param param1 First circle.
     *  \param param2 Second circle.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    inline bool visit(ConstantMovingCircle<R>& param1, ConstantMovingCircle<R>& param2, uint64_t& time, Point2D& point);
};

// You must add to this class a new "accept" function for any new derived CollisionObject
// This class is used to avoid repeated code
template <typename T, typename R>
class CollisionObjectCommon : public CollisionObject<R> {
public:
  CollisionObjectCommon(const CollisionObjectCommon&) = delete;
  void operator=(const CollisionObjectCommon&) = delete;

  CollisionObjectCommon(T* collisionObject) : c(collisionObject) {}

  bool accept(CollisionSelector<R> &visitor, CollisionObject<R>& param1, uint64_t& time, Point2D& point) {
    return (param1.accept(visitor, *c, time, point));
  }

  bool accept(CollisionSelector<R> &visitor, StaticAABB2D<R>& param2, uint64_t& time, Point2D& point) {
    return (visitor.visit(*c, param2, time, point));
  }

  bool accept(CollisionSelector<R> &visitor, ConstantMovingCircle<R>& param2, uint64_t& time, Point2D& point) {
    return (visitor.visit(*c, param2, time, point));
  }

private:
  T* c;
};


/** \brief A collision object defined by a 2D AABB
 */
template <typename R>
class StaticAABB2D: public CollisionObjectCommon<StaticAABB2D<R>, R> {
public:

  StaticAABB2D() : CollisionObjectCommon<StaticAABB2D<R>, R>(this), box() {}
  StaticAABB2D(AABB2D box) : CollisionObjectCommon<StaticAABB2D<R>, R>(this), box(box) {}

  /** \brief Return the 2D AABB.
   *  \return A 2D AABB.
   */
  inline AABB2D& getAABB2D() {return (box);}

private:
  AABB2D box;  //!< The 2D AABB.
};

/** \brief A collision object defined by a circle moving with a constant speed.
 */
template <typename R>
class ConstantMovingCircle: public CollisionObjectCommon<ConstantMovingCircle<R>, R> {
public:

  ConstantMovingCircle() : CollisionObjectCommon<ConstantMovingCircle<R>, R>(this), circle(), direction() {}
  ConstantMovingCircle(Circle circle, Vector2D direction) : CollisionObjectCommon<ConstantMovingCircle<R>, R>(this), circle(circle), direction(direction) {}

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
template <typename R>
bool CollisionSelector<R>::visit(StaticAABB2D<R>& , StaticAABB2D<R>& , uint64_t& , Point2D& ) {
  // TODO Degryll implementar AABB contra AABB
  return (false);
}

template <typename R>
bool CollisionSelector<R>::visit(StaticAABB2D<R>& param1, ConstantMovingCircle<R>& param2, uint64_t& time, Point2D& point) {
  return(IntersectionMovingCircleAABB2D(param2.getCircle(), param2.getDirection(), param1.getAABB2D(), time, point));
}

template <typename R>
bool CollisionSelector<R>::visit(ConstantMovingCircle<R>& param1, StaticAABB2D<R>& param2, uint64_t& time, Point2D& point) {
  return(IntersectionMovingCircleAABB2D(param1.getCircle(), param1.getDirection(), param2.getAABB2D(), time, point));
}

//bool CollisionSelector::visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, uint64_t& time, Point2D& point) {
template <typename R>
bool CollisionSelector<R>::visit(ConstantMovingCircle<R>& , ConstantMovingCircle<R>& , uint64_t& , Point2D& ) {
  // TODO Degryll implementar ConstantMovingSphere contra ConstantMovingSphere
  return (false);
}

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_MATH_COLLISIONS_COLLISIONSYSTEMSOLVER_H_
