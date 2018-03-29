/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InteractionEventGenerator.h
 * @since 2017-05-01
 * @date 2018-03-18
 * @author Degryll Ludo
 * @brief Generate Interaction events.
 */

#ifndef ZBE_CORE_EVENTS_INTERACTIONEVENTGENERATOR_H
#define ZBE_CORE_EVENTS_INTERACTIONEVENTGENERATOR_H

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

/** \brief Generate interaction events occurred within the remaining frame time.
 */
template <typename R, typename IS, typename LN, typename LT>
class InteractionEventGenerator : virtual public Daemon {
public:
  InteractionEventGenerator(const InteractionEventGenerator&) = delete;  //!< Avoid copy.
  void operator=(const InteractionEventGenerator&) = delete;  //!< Avoid copy.

  /** \brief Parametrized Constructor.
   *  \param list The list id of collisionators
   *  \param Id for the interaction events.
   *  \param is An interaction selector, that is part of a visitor pattern. This
   *  selector chooses how to check the interacion according to the types of the
   *  participants in the interaction.
   */
  InteractionEventGenerator(uint64_t list, int eventId, IS* is)
  : es(EventStore::getInstance()), id(list), eventId(eventId), is(is),
    lmct(ResourceManager<LT>::getInstance()),
    lmcn(ResourceManager<LN>::getInstance()),
    sysTime(zbe::SysTime::getInstance()) {}

  /** \brief Empty destructor.
  */
  virtual ~InteractionEventGenerator() {delete is;}

  /** \brief It will look for interaction events occurred within the available
   *  time and it will send them to the EventStore.
   */
  void run();

protected:
  /** \brief Stores both events in the EventStore
   * \param a Collision event from entity a
   * \param a Collision event from entity b
   */
  virtual void storeEvents(CollisionEvent2D<R>* a, CollisionEvent2D<R>* b){
    es.storeEvent(a);
    es.storeEvent(b);
  }

  /** \brief Returns the available time to search for interactions.
   */
  virtual int64_t getTotalTime() {
    return sysTime.getRemainTime();
  }

  EventStore& es; //!< The Event Store.

private:

  uint64_t id;  //!< id for the list of collisionators.
  int eventId;  //!< id for the events of this type.
  IS* is;  //!< Use to select the type of the interaction.

  ResourceManager<LT>& lmct;
  ResourceManager<LN>& lmcn;
  zbe::SysTime &sysTime;

};

/** \brief It looks for interactions between interactor objects.
 */
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

/** \brief Generate interaction events occurred in the current time.
 */
template <typename R, typename IS, typename LN, typename LT>
class InstantInteractionEventGenerator : public InteractionEventGenerator<R, IS, LN, LT> {
public:
  InstantInteractionEventGenerator(const InstantInteractionEventGenerator&) = delete; //!< Avoid copy.
  void operator=(const InstantInteractionEventGenerator&) = delete; //!< Avoid copy.

  /** \brief Parametrized Constructor.
   * \param list The list id of collisionators.
   * \param eventId Id for the interaction events.
   * \param is An interaction selector, that is part of a visitor pattern. This
   *  selector chooses how to check the interacion according to the types of the
   *  participants in the interaction.
   */
  InstantInteractionEventGenerator(uint64_t list, int eventId, IS* is): InteractionEventGenerator<R, IS, LN, LT>(list, eventId, is){}

protected:
  /** \brief Stores both events in the EventStore
   * \param a Collision event from entity a view
   * \param a Collision event from entity b view
   */
  void storeEvents(CollisionEvent2D<R>* a, CollisionEvent2D<R>* b){
    this->es.storeInstantEvent(a);
    this->es.storeInstantEvent(b);
  }

  /** \brief Returns the available time to search for interactions.
   */
  int64_t getTotalTime() {
    return 0;
  }

};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_INTERACTIONEVENTGENERATOR_H
