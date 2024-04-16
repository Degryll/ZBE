/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseCollisionSelector.cpp
 * @since 2017-04-23
 * @date 2018-03-06
 * @author Ludo Degryll Batis
 * @brief Apply the correct function to solve predictable collisions.
 */

//#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"

#include "ZBE/core/events/generators/util/CollisionBodies.h"

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
      bool visit(StaticSolidAABB2D&, StaticSolidAABB2D&, int64_t&, OldCollisionData*);

      /** \brief Solve a collision between a StaticLimiterAABB2D and a StaticLimiterAABB2D.
       *  \param param1 First element interested in the collision
       *  \param param2 Second element interested in the collision
       *  \param time Where collisión time will be stored if a collision is detected,
       *  \param point Where collisión point will be stored if a collision is detected,
       *  \param normal Where collisión normal will be stored if a collision is detected,
       */
      inline bool visit(StaticLimiterAABB2D&, StaticLimiterAABB2D&, int64_t&, OldCollisionData*);

      /** \brief Solve a collision between a StaticSolidAABB2D and a StaticLimiterAABB2D.
       *  \param param1 First element interested in the collision
       *  \param param2 Second element interested in the collision
       *  \param time Where collisión time will be stored if a collision is detected,
       *  \param point Where collisión point will be stored if a collision is detected,
       *  \param normal Where collisión normal will be stored if a collision is detected,
       */
      inline bool visit(StaticSolidAABB2D&, StaticLimiterAABB2D&, int64_t&, OldCollisionData*);

      /** \brief Solve a collision between a StaticLimiterAABB2D and a StaticSolidAABB2D.
       *  \param param1 First element interested in the collision
       *  \param param2 Second element interested in the collision
       *  \param time Where collisión time will be stored if a collision is detected,
       *  \param point Where collisión point will be stored if a collision is detected,
       *  \param normal Where collisión normal will be stored if a collision is detected,
       */
      inline bool visit(StaticLimiterAABB2D&, StaticSolidAABB2D&, int64_t&, OldCollisionData*);

      /** \brief Solve a collision between a StaticSolidAABB2D and a ConstantMovingCircle.
       *  \param param1 First element interested in the collision
       *  \param param2 Second element interested in the collision
       *  \param time Where collisión time will be stored if a collision is detected,
       *  \param point Where collisión point will be stored if a collision is detected,
       *  \param normal Where collisión normal will be stored if a collision is detected,
       */
      inline bool visit(StaticSolidAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, OldCollisionData* data);

      /** \brief Solve a collision between a StaticLimiterAABB2D and a ConstantMovingCircle.
       *  \param param1 First element interested in the collision
       *  \param param2 Second element interested in the collision
       *  \param time Where collisión time will be stored if a collision is detected,
       *  \param point Where collisión point will be stored if a collision is detected,
       *  \param normal Where collisión normal will be stored if a collision is detected,
       */
      inline bool visit(StaticLimiterAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, OldCollisionData* data);

      /** \brief Solve a collision between a ConstantMovingCircle and a StaticSolidAABB2D.
       *  \param param1 First element interested in the collision
       *  \param param2 Second element interested in the collision
       *  \param time Where collisión time will be stored if a collision is detected,
       *  \param point Where collisión point will be stored if a collision is detected,
       *  \param normal Where collisión normal will be stored if a collision is detected,
       */
      inline bool visit(ConstantMovingCircle& param1, StaticSolidAABB2D& param2, uint64_t& time, OldCollisionData* data);

      /** \brief Solve a collision between a ConstantMovingCircle and a StaticLimiterAABB2D.
       *  \param param1 First element interested in the collision
       *  \param param2 Second element interested in the collision
       *  \param time Where collisión time will be stored if a collision is detected,
       *  \param point Where collisión point will be stored if a collision is detected,
       *  \param normal Where collisión normal will be stored if a collision is detected,
       */
      inline bool visit(ConstantMovingCircle& param1, StaticLimiterAABB2D& param2, uint64_t& time, OldCollisionData* data);

      /** \brief Solve a collision between a ConstantMovingCircle and a ConstantMovingCircle.
       *  \param param1 First element interested in the collision
       *  \param param2 Second element interested in the collision
       *  \param time Where collisión time will be stored if a collision is detected,
       *  \param point Where collisión point will be stored if a collision is detected,
       *  \param normal Where collisión normal will be stored if a collision is detected,
       */
      inline bool visit(ConstantMovingCircle& param1, ConstantMovingCircle& param2, uint64_t& time, OldCollisionData* data);
  };


bool BaseCollisionSelector::visit(StaticSolidAABB2D&, StaticSolidAABB2D&, int64_t&, OldCollisionData*) {return (false);}

bool BaseCollisionSelector::visit(StaticLimiterAABB2D&, StaticLimiterAABB2D&, int64_t&, OldCollisionData*) {return (false);}

bool BaseCollisionSelector::visit(StaticSolidAABB2D&, StaticLimiterAABB2D&, int64_t&, OldCollisionData*) {return (false);}

bool BaseCollisionSelector::visit(StaticLimiterAABB2D&, StaticSolidAABB2D&, int64_t&, OldCollisionData*) {return (false);}

bool BaseCollisionSelector::visit(StaticSolidAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, OldCollisionData* data) {
  return(IntersectionMovingCircleOutsideAABB2D(param2.getCircle(), param2.getDirection(), param1.getAABB2D(), time, data->getPoint(), data->getNormal()));
}

bool BaseCollisionSelector::visit(StaticLimiterAABB2D& param1, ConstantMovingCircle& param2, uint64_t& time, OldCollisionData* data) {
  return(IntersectionMovingCircleInsideAABB2D(param2.getCircle(), param2.getDirection(), param1.getAABB2D(), time, data->getPoint(), data->getNormal()));
}

bool BaseCollisionSelector::visit(ConstantMovingCircle& param1, StaticSolidAABB2D& param2, uint64_t& time, OldCollisionData* data) {
  return(IntersectionMovingCircleOutsideAABB2D(param1.getCircle(), param1.getDirection(), param2.getAABB2D(), time, data->getPoint(), data->getNormal()));
}

bool BaseCollisionSelector::visit(ConstantMovingCircle& param1, StaticLimiterAABB2D& param2, uint64_t& time, OldCollisionData* data) {
  return(IntersectionMovingCircleInsideAABB2D(param1.getCircle(), param1.getDirection(), param2.getAABB2D(), time, data->getPoint(), data->getNormal()));
}

bool BaseCollisionSelector::visit(ConstantMovingCircle&, ConstantMovingCircle&, uint64_t&, OldCollisionData*) {
  // TODO Degryll implementar ConstantMovingSphere contra ConstantMovingSphere
  return (false);
}

}  // namespace zbe
