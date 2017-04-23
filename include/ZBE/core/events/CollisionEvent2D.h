/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEvent2D.h
 * @since 2016-12-27
 * @date 2016-12-27
 * @author Degryll Ludo
 * @brief Event that has the information needed to resolve a collision.
 */

#ifndef CORE_EVENTS_COLLISIONEVENT2D_H
#define CORE_EVENTS_COLLISIONEVENT2D_H

#include <memory>

#include "ZBE/core/events/Event.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"


namespace zbe {

/** \brief Has the information needed to resolve a collision.
 */
template<typename R>
class CollisionEvent2D : public Event {
  public:
    CollisionEvent2D(const CollisionEvent2D& rhs) {
      Event::operator=(rhs);
      c = rhs.c;
      cd = rhs.cd;
    }

    /** \brief Parametrized Constructor.
    *
    * \param id Represents the global id of this event.
    * \param time Exact moment in which it occurred
    * \param entityA The first entity involved in the collision.
    * \param entityB The second entity involved in the collision.
    * \param point Point of collision.
    */
    CollisionEvent2D(uint64_t id, int64_t time, Collisioner<R>* collisioner, CollisionData collisionData, std::shared_ptr<ReactObject<R> >  reactObject) : Event(id, time), c(collisioner), cd(collisionData), ro(reactObject) {}

    /** \brief base destructor.
    */
    virtual ~CollisionEvent2D() {};

    /** \brief Copy Operator.
     */
    CollisionEvent2D& operator=(const CollisionEvent2D& rhs) {
      Event::operator=(rhs);
      c = rhs.c;
      cd = rhs.cd;
      return (*this);
    }

    /** \brief Get the entity involved in the collision.
    * \return The entity involved in the collision.
    */
    inline Collisioner<R>* getCollisioner() {return (c);}

    /** \brief Get the point of collision.
    * \return The point of collision.
    */
    inline CollisionData getCollisionData() {return (cd);}

    /** \brief Get the point of collision.
    * \return The point of collision.
    */
    inline std::shared_ptr<ReactObject<R> > getReactObject() {return (ro);}

    /** \brief Manage the current event and, presumably,
     * do the actions associated with it.
     */
    void manage() {
      /*std::shared_ptr<Collisioner<R> >  c = event->getCollisioner();
      std::shared_ptr<ReactObject<R> >  ro = event->getReactObject();
      CollisionData cd = event->getCollisionData();*/
      c->react(&cd,&(*ro));
    };

  private:
    Collisioner<R>* c;     //!< First entitie involved avatar.
    CollisionData cd;   //!< Point of collision.
    std::shared_ptr<ReactObject<R> > ro; //!< second entitie involved. void to avoid template.
};


} // namespace zbe
#endif // CORE_EVENTS_COLLISIONEVENT2D_H
