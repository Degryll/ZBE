/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEvent.h
 * @since 2016-03-26
 * @date 2016-03-26
 * @author Degryll
 * @brief Has the information needed to resolve a collision.
 */

#ifndef CORE_EVENTS_COLLISIONEVENT_H
#define CORE_EVENTS_COLLISIONEVENT_H

#include "ZBE/core/events/Event.h"
#include "ZBE/core/entities/CollisionerEntity.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

/** \brief Has the information needed to resolve a collision.
 */
class CollisionEvent2D : public Event {
  public:
    /** \brief Parametrized Constructor.
    *
    * \param id Represents the global id of this event.
    * \param time Exact moment in which it occurred
    * \param entityA The first entity involved in the collision.
    * \param entityB The second entity involved in the collision.
    * \param point Point of collision.
    */
    CollisionEvent2D(uint64_t id, uint64_t time, CollisionerEntity *entityA, CollisionerEntity *entityB, Point2D point) : Event(id, time), a(entityA), b(entityB), p(point) {}

    /** \brief Empty destructor.
    */
    virtual ~CollisionEvent2D() {};

    /** \brief Get the first entity involved in the collision.
    * \return The first entity involved in the collision.
    */
    inline CollisionerEntity* getEntityA() {return (a);}

    /** \brief Get the second entity involved in the collision.
    * \return The second entity involved in the collision.
    */
    inline CollisionerEntity* getEntityB() {return (b);}

    /** \brief Get the point of collision.
    * \return The point of collision.
    */
    inline Point2D getPoint() {return (p);}

  private:
    CollisionerEntity *a;  //!< First entitie involved.
    CollisionerEntity *b;  //!< Second entitie involved.
    Point2D p;             //!< Point of collision.
};

}  // namespace zbe

#endif // CORE_EVENTS_COLLISIONEVENT_H
