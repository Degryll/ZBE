/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEventGenerator.h
 * @since 2016-06-05
 * @date 2016-08-04
 * @author Degryll
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
    void generate(uint64_t initTime, uint64_t endTime){
      uint64_t totalTime = endTime - initTime;
      Point2D point;

printf("PRE\n");fflush(stdout);

      TicketedForwardList<CollisionatorEntity<R>*>* ctl = lmct.get(id);

printf("FOR collisionator list\n");fflush(stdout);
      for(auto it = ctl->begin(); it != ctl->end(); it++) {
        std::shared_ptr<Collisionator<R> > cator = (*it)->getCollisionator();
        const std::forward_list<uint64_t>& cl = cator->getCollisionablesLists();
printf("FOR collisioner list\n");fflush(stdout);
        for(auto jt = cl.begin(); jt != cl.end(); jt++) {
          TicketedForwardList<CollisionerEntity<R>*>* cnl = lmcn.get(*jt);
printf("FOR collisioner\n");fflush(stdout);
          for(auto kt = cnl->begin(); kt != cnl->end(); kt++) {
            std::shared_ptr<Collisioner<R> > coner = (*kt)->getCollisioner();
printf("pre if\n");fflush(stdout);
            if(cs.select(*cator, *coner, totalTime, point)) {
printf("if\n");fflush(stdout);
              CollisionData cd(point);
printf("store\n");fflush(stdout);
              es.storeEvent(new CollisionEvent2D<R>(eventId, initTime+totalTime, cator, cd, (*kt)->getReactObject()));
              es.storeEvent(new CollisionEvent2D<R>(eventId, initTime+totalTime, coner, cd, (*it)->getReactObject()));
            }  // if collision
printf("post if\n");fflush(stdout);
          } // for each collisionable
printf("post collisioner\n");fflush(stdout);
        }  // for collisionable list
printf("post collisioner list\n");fflush(stdout);
      }  // for each collisionator
printf("post collisionator list\n");fflush(stdout);
    }

  private:
    uint64_t id;  //!< id for the list of collisionators.
    int eventId;  //!< id for the events of this type.
    CollisionSelector<R> cs;  //!< Use to select the type of the collision.
    EventStore& es;

    ListManager<TicketedForwardList<CollisionatorEntity<R>*> >& lmct;
    ListManager<TicketedForwardList<CollisionerEntity<R>*> >& lmcn;
};

}  // namespace zbe

#endif // CORE_EVENTS_COLLISIONEVENTGENERATOR_H
