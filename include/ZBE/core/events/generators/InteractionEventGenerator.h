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

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/avatars/Interactionator.h"

#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InteractionEvent.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Generate interaction events occurred within the remaining frame time.
 */
template <typename R, typename IS, typename LN, typename LT>
class InteractionEventGenerator : virtual public Daemon {
public:
  InteractionEventGenerator(const InteractionEventGenerator&) = delete;  //!< Avoid copy.
  void operator=(const InteractionEventGenerator&) = delete;  //!< Avoid copy.

  /** \brief Empty Constructor, unusable generator until the list id, event id and interaction selector are properly set.
   */
  InteractionEventGenerator()
  : es(EventStore::getInstance()), id(0), eventId(0), is(nullptr),
    lmct(RsrcStore<LT>::getInstance()),
    lmcn(RsrcStore<LN>::getInstance()),
    contextTime(zbe::SysTime::getInstance()) {}

  /** \brief Parametrized Constructor.
   *  \param list The list id of interactionators
   *  \param Id for the interaction events.
   *  \param is An interaction selector, that is part of a visitor pattern. This
   *  selector chooses how to check the interacion according to the types of the
   *  participants in the interaction.
   */
  InteractionEventGenerator(uint64_t list, uint64_t eventId, std::shared_ptr<IS> is)
  : es(EventStore::getInstance()), id(list), eventId(eventId), is(is),
    lmct(RsrcStore<LT>::getInstance()),
    lmcn(RsrcStore<LN>::getInstance()),
    contextTime(zbe::SysTime::getInstance()) {}

  /** \brief Sets the interactionators list id.
  *   \param id interactionators list id.
  */
  void setListId(uint64_t id) {this->id = id;}

  /** \brief Sets the the id for the generated events.
  *   \param eventId events id.
  */
  void setEventId(uint64_t eventId) {this->eventId = eventId;}

  /** \brief Sets the Interaction Selector
  *   \param is id interactionators list id.
  */
  void setInteractionSelector(std::shared_ptr<IS> is) {this->is = is;}

  /** \brief Empty destructor.
  */
  virtual ~InteractionEventGenerator() {}

  /** \brief It will look for interaction events occurred within the available
   *  time and it will send them to the EventStore.
   */
  void run();

protected:
  /** \brief Stores both events in the EventStore
   * \param a Interaction event from entity a
   * \param a Interaction event from entity b
   */
  virtual void storeEvents(InteractionEvent<R>* a, InteractionEvent<R>* b){
    es.storeEvent(a);
    es.storeEvent(b);
  }

  /** \brief Returns the available time to search for interactions.
   */
  virtual int64_t getTotalTime() {
    return contextTime->getRemainTime();
  }

  EventStore& es; //!< The Event Store.

private:

  uint64_t id;  //!< id for the list of interactionators.
  uint64_t eventId;  //!< id for the events of this type.
  std::shared_ptr<IS> is;  //!< Use to select the type of the interaction.

  RsrcStore<LT>& lmct;
  RsrcStore<LN>& lmcn;
  std::shared_ptr<ContextTime> contextTime;
};

/** \brief It looks for interactions between interactor objects.
 */
template <typename R, typename IS, typename LN, typename LT>
void InteractionEventGenerator<R, IS, LN, LT>::run() {
  int64_t totalTime = getTotalTime();
  // Point2D point;
  // Vector2D normal
  typename R::InteractionData iData;
  std::shared_ptr<LT> itl = lmct.get(id);

  for(auto iatorEntity : (*itl)) {
    Interactionator<R>* iator;
    iatorEntity->assignAvatar(&iator);
    uint64_t cablesId = iator->getInteractionablesListId();
    std::shared_ptr<LN> inl = lmcn.get(cablesId);
    for(auto ionerEntity : (*inl)) {
      Interactioner<R>* ioner;
      ionerEntity->assignAvatar(&ioner);
      if(is->select(iator->getInteractionObject(), ioner->getInteractionObject(), totalTime, &iData)) {
        InteractionEvent<R>* a = new InteractionEvent<R>(eventId, contextTime->getInitFrameTime() + totalTime, iator, iData, std::shared_ptr<zbe::ReactObject<R> >(ioner->getReactObject()));
        InteractionEvent<R>* b = new InteractionEvent<R>(eventId, contextTime->getInitFrameTime() + totalTime, ioner, iData, std::shared_ptr<zbe::ReactObject<R> >(iator->getReactObject()));
        storeEvents(a,b);
      }  // if interaction
    }  // for each interactionable
  }  // for each interactionator
}

/** \brief Generate interaction events occurred in the current time.
 */
template <typename R, typename IS, typename LN, typename LT>
class InstantInteractionEventGenerator : public InteractionEventGenerator<R, IS, LN, LT> {
public:
  InstantInteractionEventGenerator(const InstantInteractionEventGenerator&) = delete; //!< Avoid copy.
  void operator=(const InstantInteractionEventGenerator&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */
  InstantInteractionEventGenerator(): InteractionEventGenerator<R, IS, LN, LT>(){}

  /** \brief Parametrized Constructor.
   * \param list The list id of interactionators.
   * \param eventId Id for the interaction events.
   * \param is An interaction selector, that is part of a visitor pattern. This
   *  selector chooses how to check the interacion according to the types of the
   *  participants in the interaction.
   */
  InstantInteractionEventGenerator(uint64_t list, int eventId, std::shared_ptr<IS> is): InteractionEventGenerator<R, IS, LN, LT>(list, eventId, is){}

protected:
  /** \brief Stores both events in the EventStore
   * \param a Interaction event from entity a view
   * \param a Interaction event from entity b view
   */
  void storeEvents(InteractionEvent<R>* a, InteractionEvent<R>* b){
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
