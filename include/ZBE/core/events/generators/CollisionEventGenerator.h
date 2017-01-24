/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEventGenerator.h
 * @since 2016-06-05
 * @date 2017-01-18
 * @author Degryll Ludo
 * @brief Generate collision events.
 */

#ifndef CORE_EVENTS_COLLISIONEVENTGENERATOR_H
#define CORE_EVENTS_COLLISIONEVENTGENERATOR_H

#include <cstdint>
#include <memory>

#include "ZBE/core/entities/adaptorentities/CollisionerEntity.h"
#include "ZBE/core/entities/adaptorentities/CollisionatorEntity.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

namespace zbe {

/** \brief Generate collision events.
 */
template <typename R>
class CollisionEventGenerator {
  public:
    /** \brief Parametrized Constructor.
     *  \param list The list id of collisionators
     *  \param Id for the collision events.
     */
    CollisionEventGenerator(uint64_t list, int eventId)
    : id(list), eventId(eventId), cs(), es(EventStore::getInstance()),
      lmct(ListManager<TicketedForwardList<CollisionatorEntity<R>*> >::getInstance()),
      lmcn(ListManager<TicketedForwardList<CollisionerEntity<R>*> >::getInstance()) {};

    /** \brief Empty destructor.
    */
    ~CollisionEventGenerator() {};

    /** Will search for collision events occurred between initTime and finalTime and send it to the EventStore.
     * \param initTime Initial time of the frame
     * \param endTime End time of the frame
     */
    void generate(uint64_t initTime, uint64_t endTime);

  private:
    uint64_t id;  //!< id for the list of collisionators.
    int eventId;  //!< id for the events of this type.
    CollisionSelector<R> cs;  //!< Use to select the type of the collision.
    EventStore& es;

    ListManager<TicketedForwardList<CollisionatorEntity<R>*> >& lmct;
    ListManager<TicketedForwardList<CollisionerEntity<R>*> >& lmcn;
};

template <typename R>
void CollisionEventGenerator<R>::generate(uint64_t initTime, uint64_t endTime) {
  uint64_t totalTime = endTime - initTime;
  Point2D point;

  TicketedForwardList<CollisionatorEntity<R>*>* ctl = lmct.get(id);

  for(auto catorEntity : (*ctl)) {
    std::shared_ptr<Collisionator<R> > cator = catorEntity->getCollisionator();
    uint64_t cablesId = cator->getCollisionablesListId();
    TicketedForwardList<CollisionerEntity<R>*>* cnl = lmcn.get(cablesId);
    for(auto conerEntity : (*cnl)) {
      std::shared_ptr<Collisioner<R> > coner = conerEntity->getCollisioner();
      if(cs.select(*cator, *coner, totalTime, point)) {
        CollisionData cd(point);
        es.storeEvent(new CollisionEvent2D<R>(eventId, initTime+totalTime, cator, cd, std::shared_ptr<zbe::ReactObject<R> >(coner->getReactObject())));
        es.storeEvent(new CollisionEvent2D<R>(eventId, initTime+totalTime, coner, cd, std::shared_ptr<zbe::ReactObject<R> >(cator->getReactObject())));
      }  // if collision
    }  // for each collisionable
  }  // for each collisionator
}

}  // namespace zbe

#endif // CORE_EVENTS_COLLISIONEVENTGENERATOR_H
