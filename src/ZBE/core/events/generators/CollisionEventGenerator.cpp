/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEventGenerator.h
 * @since 2016-06-05
 * @date 2016-08-15
 * @author Degryll
 * @brief Generate collision events.
 */

#include "ZBE/core/events/generators/CollisionEventGenerator.h"

#include "ZBE/core/events/EventDispatcher.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

template <typename R>
void CollisionEventGenerator<R>::generate(uint64_t initTime, uint64_t endTime) {
  uint64_t totalTime = endTime - initTime;
  Point2D point;

  TicketedForwardList<CollisionatorEntity*>* ctl = lmct.get(id);

  for(auto it = ctl->begin(); it != ctl->end(); it++) {
    Collisionator* cator = (*it)->getCollisionator();
    const std::forward_list<uint64_t>& cl = cator->getCollisionablesLists();
    for(auto jt = cl.begin(); jt != cl.end(); jt++) {
      TicketedForwardList<CollisionerEntity<R>*>* cnl = lmcn.get(*jt);
      for(auto kt = cnl->begin(); kt != cnl->end(); kt++) {
        Collisioner *coner = (*kt)->getCollisioner();
        if(cs.select(*cator, *coner, totalTime, point)) {
          es.storeEvent(new CollisionEvent2D(eventId, initTime+totalTime, cator, point));
          es.storeEvent(new CollisionEvent2D(eventId, initTime+totalTime, coner, point));
        }  // if collision
      } // for each collisionable
    }  // for collisionable list
  }  // for each collisionator
}


}  // namespace zbe