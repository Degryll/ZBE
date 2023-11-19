/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseCollisionSelector.h
 * @since 2017-04-23
 * @date 2018-03-06
 * @author Ludo Degryll Batis
 * @brief Apply the correct function to solve predictable collisions.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_BASECOLLISIONSELECTOR_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_BASECOLLISIONSELECTOR_H_

#include <cstdint>

#include "ZBE/core/tools/math/collisions/intersections.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/events/generators/util/CollisionData.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"

#include "ZBE/core/system/system.h"


namespace zbe {

/** \brief Apply the correct function to solve a collision.
 */
class ZBEAPI BaseCollisionSelector : public CollisionSelector {

  /** \brief Solve a collision between a StaticSolidAABB2D and a StaticSolidAABB2D.
   *  \param param1 First element interested in the collision
   *  \param param2 Second element interested in the collision
   *  \param time Where collisión time will be stored if a collision is detected,
   *  \param point Where collisión point will be stored if a collision is detected,
   *  \param normal Where collisión normal will be stored if a collision is detected,
   */
    bool visit(StaticSolidAABB2D&, StaticSolidAABB2D&, int64_t&, CollisionData*);

    /** \brief Solve a collision between a StaticLimiterAABB2D and a StaticLimiterAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    /*inline*/ bool visit(StaticLimiterAABB2D&, StaticLimiterAABB2D&, int64_t&, CollisionData*);

    /** \brief Solve a collision between a StaticSolidAABB2D and a StaticLimiterAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    /*inline*/ bool visit(StaticSolidAABB2D&, StaticLimiterAABB2D&, int64_t&, CollisionData*);

    /** \brief Solve a collision between a StaticLimiterAABB2D and a StaticSolidAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    /*inline*/ bool visit(StaticLimiterAABB2D&, StaticSolidAABB2D&, int64_t&, CollisionData*);

    /** \brief Solve a collision between a StaticSolidAABB2D and a ConstantMovingCircle.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    /*inline*/ bool visit(StaticSolidAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, CollisionData* data);

    /** \brief Solve a collision between a StaticLimiterAABB2D and a ConstantMovingCircle.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    /*inline*/ bool visit(StaticLimiterAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, CollisionData* data);

    /** \brief Solve a collision between a ConstantMovingCircle and a StaticSolidAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    /*inline*/ bool visit(ConstantMovingCircle& param1, StaticSolidAABB2D& param2, uint64_t& time, CollisionData* data);

    /** \brief Solve a collision between a ConstantMovingCircle and a StaticLimiterAABB2D.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    /*inline*/ bool visit(ConstantMovingCircle& param1, StaticLimiterAABB2D& param2, uint64_t& time, CollisionData* data);

    /** \brief Solve a collision between a ConstantMovingCircle and a ConstantMovingCircle.
     *  \param param1 First element interested in the collision
     *  \param param2 Second element interested in the collision
     *  \param time Where collisión time will be stored if a collision is detected,
     *  \param point Where collisión point will be stored if a collision is detected,
     *  \param normal Where collisión normal will be stored if a collision is detected,
     */
    /*inline*/ bool visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, uint64_t& time, CollisionData* data);
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_BASECOLLISIONSELECTOR_H_
