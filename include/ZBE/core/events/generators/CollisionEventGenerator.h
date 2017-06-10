/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionEventGenerator.h
 * @since 2016-06-05
 * @date 2017-03-20
 * @author Degryll Ludo
 * @brief Generate collision events.
 */

#ifndef CORE_EVENTS_COLLISIONEVENTGENERATOR_H
#define CORE_EVENTS_COLLISIONEVENTGENERATOR_H

#include <cstdint>
#include <memory>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/tools/containers/ResourceManager.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/system/SysTime.h"

namespace zbe {

/** \brief Generate collision events.
 */
template <typename R>
class CollisionEventGenerator : virtual public Daemon {
  public:
    CollisionEventGenerator(const CollisionEventGenerator&) = delete;
    void operator=(const CollisionEventGenerator&) = delete;

    /** \brief Parametrized Constructor.
     *  \param list The list id of collisionators
     *  \param Id for the collision events.
     */
    CollisionEventGenerator(uint64_t list, int eventId, CollisionSelector<R>* cs)
    : id(list), eventId(eventId), cs(cs), es(EventStore::getInstance()),
      lmct(ResourceManager<TicketedForwardList<AvatarEntity<Collisionator<R> > > >::getInstance()),
      lmcn(ResourceManager<TicketedForwardList<AvatarEntity<Collisioner<R> > > >::getInstance()),
      sysTime(zbe::SysTime::getInstance()) {};

    /** \brief Empty destructor.
    */
    ~CollisionEventGenerator() {delete cs;};

    /** Will search for collision events occurred between initTime and finalTime and send it to the EventStore.
     * \param initTime Initial time of the frame
     * \param endTime End time of the frame
     */
    void run();

  private:
    uint64_t id;  //!< id for the list of collisionators.
    int eventId;  //!< id for the events of this type.
    CollisionSelector<R>* cs;  //!< Use to select the type of the collision.
    EventStore& es;

    ResourceManager<TicketedForwardList<AvatarEntity<Collisionator<R> > > >& lmct;
    ResourceManager<TicketedForwardList<AvatarEntity<Collisioner<R> > > >& lmcn;
    zbe::SysTime &sysTime;
};

template <typename R>
void CollisionEventGenerator<R>::run() {
  int64_t totalTime = sysTime.getRemainTime();
  Point2D point;
  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisionator<R> > > > ctl = lmct.get(id);

  for(auto catorEntity : (*ctl)) {
    Collisionator<R>* cator;
    catorEntity->assignAvatar(&cator);
    uint64_t cablesId = cator->getCollisionablesListId();
    std::shared_ptr<TicketedForwardList<AvatarEntity<Collisioner<R> > > > cnl = lmcn.get(cablesId);
    for(auto conerEntity : (*cnl)) {
      Collisioner<R>* coner;
      conerEntity->assignAvatar(&coner);
      if(cs->select(*cator, *coner, totalTime, point)) {
        CollisionData cd(point);
        es.storeEvent(new CollisionEvent2D<R>(eventId, sysTime.getInitFrameTime() + totalTime, cator, cd, std::shared_ptr<zbe::ReactObject<R> >(coner->getReactObject())));
        es.storeEvent(new CollisionEvent2D<R>(eventId, sysTime.getInitFrameTime() + totalTime, coner, cd, std::shared_ptr<zbe::ReactObject<R> >(cator->getReactObject())));
      }  // if collision
    }  // for each collisionable
  }  // for each collisionator
}

}  // namespace zbe

#endif // CORE_EVENTS_COLLISIONEVENTGENERATOR_H
