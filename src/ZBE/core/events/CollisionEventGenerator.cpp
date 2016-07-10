/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEventGenerator.h
 * @since 2016-06-05
 * @date 2016-06-16
 * @author Degryll
 * @brief Generate collision events.
 */

#include "ZBE/core/events/CollisionEventGenerator.h"

#include <forward_list>

#include "ZBE/core/entities/CollisionerEntity.h"
#include "ZBE/core/entities/CollisionatorEntity.h"
#include "ZBE/core/events/CollisionEvent.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

void CollisionEventGenerator::generate(uint64_t initTime, uint64_t endTime) {
  uint64_t totalTime = endTime - initTime;
  Point2D point;

  std::forward_list<CollisionatorEntity*>* ctl = lmct.get(id);

  for(auto it = ctl->begin(); it != ctl->end(); it++) {
    const std::forward_list<uint64_t>& cl = (*it)->getCollisionablesList();
    for(auto jt = cl.begin(); jt != cl.end(); jt++) {
      std::forward_list<CollisionerEntity*>* cnl = lmcn.get(*jt);
      for(auto kt = cnl->begin(); kt != cnl->end(); kt++) {
        if(cs.select(*(*it), *(*kt), totalTime, point)) {
          es.storeEvent(CollisionEvent2D(eventId, initTime+totalTime, *it, *kt, point, totalTime));
        }  // if collision
      } // for each collisionable
    }  // for collisionable list
  }  // for each collisionator
}


}  // namespace zbe
