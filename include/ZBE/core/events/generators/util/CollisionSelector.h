/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionSelector.h
 * @since 2016-05-01
 * @date 2018-08-07
 * @author Degryll Ludo
 * @brief Apply the correct function to solve a collision.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONSELECTOR_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONSELECTOR_H_

#include <cstdint>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/collisions/intersections.h"
#include "ZBE/core/entities/avatars/Interactioner.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI CollisionObject;
class ZBEAPI StaticSolidAABB2D;
class ZBEAPI StaticLimiterAABB2D;
class ZBEAPI ConstantMovingCircle;

/** \brief Apply the correct function to solve a collision.
 */
class ZBEAPI CollisionSelector {
  public:
    virtual ~CollisionSelector() {}

    /** \brief Using the Visitor pattern select the correct collision detection function to use depending of the types of the params.
     *  \param param1 First collision object.
     *  \param param2 Second collision object.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    bool select(std::shared_ptr<CollisionObject> param1, std::shared_ptr<CollisionObject> param2, uint64_t& time, OldCollisionData *data);

    /** \brief Dont move, wont collide.
     *  \param param1 First AABB.
     *  \param param2 Second AABB.
     *  \param time Unaltered.
     *  \param point Unaltered.
     *  \return False.
     */
    virtual bool visit(StaticSolidAABB2D& param1, StaticSolidAABB2D& param2, uint64_t& time, OldCollisionData *data) = 0;

    /** \brief Dont move, wont collide.
     *  \param param1 First AABB.
     *  \param param2 Second AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return False.
     */
    virtual bool visit(StaticLimiterAABB2D& param1, StaticLimiterAABB2D& param2, uint64_t& time, OldCollisionData *data) = 0;

    /** \brief Dont move, wont collide.
     *  \param param1 First AABB.
     *  \param param2 Second AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return False.
     */
    virtual bool visit(StaticSolidAABB2D& param1, StaticLimiterAABB2D& param2, uint64_t& time, OldCollisionData *data) = 0;

    /** \brief Dont move, wont collide.
     *  \param param1 First AABB.
     *  \param param2 Second AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return False.
     */
    virtual bool visit(StaticLimiterAABB2D& param1, StaticSolidAABB2D& param2, uint64_t& time, OldCollisionData *data) = 0;

    /** \brief Collision detection for an AABB and a circle.
     *  \param param1 The AABB.
     *  \param param2 The circle.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    virtual bool visit(StaticSolidAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, OldCollisionData *data) = 0;

    /** \brief Collision detection for an AABB and a circle.
     *  \param param1 The AABB.
     *  \param param2 The circle.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    virtual bool visit(StaticLimiterAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, OldCollisionData *data) = 0;

    /** \brief Collision detection for a circle and an AABB.
     *  \param param1 The circle.
     *  \param param2 The AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    virtual bool visit(ConstantMovingCircle& param1, StaticSolidAABB2D& param2, uint64_t& time, OldCollisionData *data) = 0;

    /** \brief Collision detection for a circle and an AABB.
     *  \param param1 The circle.
     *  \param param2 The AABB.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    virtual bool visit(ConstantMovingCircle& param1, StaticLimiterAABB2D& param2, uint64_t& time, OldCollisionData *data) = 0;

    /** \brief Collision detection for two circles.
     *  \param param1 First circle.
     *  \param param2 Second circle.
     *  \param time Timeslot to search for a collision. If there is a collision the time is updated with the time of the collision.
     *  \param point Point of collision if any.
     *  \return True if there is a collision in the timeslot set by time, false otherwise.
     */
    virtual bool visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, uint64_t& time, OldCollisionData *data) = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_COLLISIONSELECTOR_H_
