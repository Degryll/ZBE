/**
 * Copyright 2012 Batis Degryll Ludo
 * @file IntersectionCollisionSelector.h
 * @since 2017-04-23
 * @date 2017-04-23
 * @author Ludo Degryll Batis
 * @brief Apply the correct function to solve intersections.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_INTERSECTIONCOLLISIONSELECTOR_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_INTERSECTIONCOLLISIONSELECTOR_H_

#include <cstdint>

#include "ZBE/core/tools/math/collisions/intersections.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/events/generators/util/CollisionData.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"

namespace zbe {

/** \brief Apply the correct function to solve a collision.
 */
class IntersectionCollisionSelector : public CollisionSelector {

    /** \brief Solve an intersection between a StaticSolidAABB2D and a StaticSolidAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    bool visit(StaticSolidAABB2D& param1, StaticSolidAABB2D& param2, int64_t& time, CollisionData* data);

    /** \brief Solve an intersection between a StaticLimiterAABB2D and a StaticLimiterAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    inline bool visit(StaticLimiterAABB2D&, StaticLimiterAABB2D&, int64_t&, CollisionData*);

    /** \brief Solve an intersection between a StaticSolidAABB2D and a StaticLimiterAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    inline bool visit(StaticSolidAABB2D&, StaticLimiterAABB2D&, int64_t&, CollisionData*);

    /** \brief Solve an intersection between a StaticLimiterAABB2D and a StaticSolidAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    inline bool visit(StaticLimiterAABB2D&, StaticSolidAABB2D&, int64_t&, CollisionData*);

    /** \brief Solve an intersection between a StaticSolidAABB2D and a ConstantMovingCircle.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    inline bool visit(StaticSolidAABB2D& param1, ConstantMovingCircle& param2, int64_t& time, CollisionData* data);

    /** \brief Solve an intersection between a StaticLimiterAABB2D and a ConstantMovingCircle.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    inline bool visit(StaticLimiterAABB2D& param1, ConstantMovingCircle& param2, int64_t& time, CollisionData* data);

    /** \brief Solve an intersection between a ConstantMovingCircle and a StaticSolidAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    inline bool visit(ConstantMovingCircle& param1, StaticSolidAABB2D& param2, int64_t& time, CollisionData* data);

    /** \brief Solve an intersection between a ConstantMovingCircle and a StaticLimiterAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    inline bool visit(ConstantMovingCircle& param1, StaticLimiterAABB2D& param2, int64_t& time, CollisionData* data);

    /** \brief Solve an intersection between a ConstantMovingCircle and a ConstantMovingCircle.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    inline bool visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, int64_t& time, CollisionData* data);
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_INTERSECTIONCOLLISIONSELECTOR_H_
