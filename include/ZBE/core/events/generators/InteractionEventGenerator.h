/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InteractionEventGenerator.h
 * @since 2017-05-01
 * @date 2017-05-01
 * @author Degryll Ludo
 * @brief Generate Interaction events.
 */

#ifndef CORE_EVENTS_INTERACTIONEVENTGENERATOR_H
#define CORE_EVENTS_INTERACTIONEVENTGENERATOR_H

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/containers/ResourceManager.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

namespace zbe {

/** \brief Generate Interaction events.
 */
template <typename R, typename IS, typename LN, typename LT>
class InteractionEventGenerator : virtual public Daemon {
public:
  InteractionEventGenerator(const InteractionEventGenerator&) = delete;
  void operator=(const InteractionEventGenerator&) = delete;

  /** \brief Parametrized Constructor.
   *  \param list The list id of collisionators
   *  \param Id for the interaction events.
   */
  InteractionEventGenerator(uint64_t list, int eventId, IS* is)
  : es(EventStore::getInstance()), id(list), eventId(eventId), is(is),
    lmct(ResourceManager<LT>::getInstance()),
    lmcn(ResourceManager<LN>::getInstance()),
    sysTime(zbe::SysTime::getInstance()) {}

  /** \brief Empty destructor.
  */
  virtual ~InteractionEventGenerator() {delete is;}

  /** Will search for interaction events occurred between initTime and finalTime and send it to the EventStore.
   * \param initTime Initial time of the frame
   * \param endTime End time of the frame
   */
  void run();

protected:

  virtual void storeEvents(CollisionEvent2D<R>* a, CollisionEvent2D<R>* b){
    es.storeEvent(a);
    es.storeEvent(b);
  }

  virtual int64_t getTotalTime(){
    return sysTime.getRemainTime();
  }

  EventStore& es;

private:

  uint64_t id;  //!< id for the list of collisionators.
  int eventId;  //!< id for the events of this type.
  IS* is;  //!< Use to select the type of the interaction.

  ResourceManager<LT>& lmct;
  ResourceManager<LN>& lmcn;
  zbe::SysTime &sysTime;

};

template <typename R, typename IS, typename LN, typename LT>
void InteractionEventGenerator<R, IS, LN, LT>::run() {
  int64_t totalTime = getTotalTime();
  Point2D point;
  Vector2D normal;
  std::shared_ptr<LT> ctl = lmct.get(id);

  for(auto catorEntity : (*ctl)) {
    Collisionator<R>* cator;
    catorEntity->assignAvatar(&cator);
    uint64_t cablesId = cator->getCollisionablesListId();
    std::shared_ptr<LN> cnl = lmcn.get(cablesId);
    for(auto conerEntity : (*cnl)) {
      Collisioner<R>* coner;
      conerEntity->assignAvatar(&coner);
      if(is->select(*cator, *coner, totalTime, point, normal)) {
        CollisionData cd(point, normal);
        CollisionEvent2D<R>* a = new CollisionEvent2D<R>(eventId, sysTime.getInitFrameTime() + totalTime, cator, cd, std::shared_ptr<zbe::ReactObject<R> >(coner->getReactObject()));
        CollisionEvent2D<R>* b = new CollisionEvent2D<R>(eventId, sysTime.getInitFrameTime() + totalTime, coner, cd, std::shared_ptr<zbe::ReactObject<R> >(cator->getReactObject()));
        storeEvents(a,b);
      }  // if collision
    }  // for each collisionable
  }  // for each collisionator
}

/** \brief Generate Interaction events.
 */
template <typename R, typename IS, typename LN, typename LT>
class InstantInteractionEventGenerator : public InteractionEventGenerator<R, IS, LN, LT> {
public:
  InstantInteractionEventGenerator(const InstantInteractionEventGenerator&) = delete;
  void operator=(const InstantInteractionEventGenerator&) = delete;

  InstantInteractionEventGenerator(uint64_t list, int eventId, IS* is): InteractionEventGenerator<R, IS, LN, LT>(list, eventId, is){}

protected:

  void storeEvents(CollisionEvent2D<R>* a, CollisionEvent2D<R>* b){
    this->es.storeInstantEvent(a);
    this->es.storeInstantEvent(b);
  }

  int64_t getTotalTime(){
    return 0;
  }

};

}  // namespace zbe

#endif // CORE_EVENTS_INTERACTIONEVENTGENERATOR_H
