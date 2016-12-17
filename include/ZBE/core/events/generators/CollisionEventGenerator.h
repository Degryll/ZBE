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

#include "ZBE/core/entities/adaptorentities/CollisionatorEntity.h"
#include "ZBE/core/entities/adaptorentities/CollisionerEntity.h"
#include "ZBE/core/tools/math/collisions/CollisionSystemSolver.h"
#include "ZBE/core/events/EventStore.h"
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
      lmct(ListManager<TicketedForwardList<CollisionatorEntity*> >::getInstance()),
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
    CollisionSelector cs;  //!< Use to select the type of the collision.
    EventStore& es;

    ListManager<TicketedForwardList<CollisionatorEntity*> >& lmct;
    ListManager<TicketedForwardList<CollisionerEntity<R>*> >& lmcn;
};

}  // namespace zbe

#endif // CORE_EVENTS_COLLISIONEVENTGENERATOR_H
