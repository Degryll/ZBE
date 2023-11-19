/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InteractionEvent.h
 * @since 2016-12-27
 * @date 2018-03-18
 * @author Degryll Ludo Batis
 * @brief Event that has the information needed to resolve a interaction.
 */

#ifndef ZBE_CORE_EVENTS_INTERACTIONEVENT_H
#define ZBE_CORE_EVENTS_INTERACTIONEVENT_H

#include <memory>
#include <cstdint>

#include "ZBE/core/events/Event.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/events/generators/util/ReactObject.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Has the information needed to resolve a interaction.
 */
template<typename R>
class InteractionEvent : public Event {
  public:

    /** \brief Parametrized constructor.
     *  \param rhs InteractionEvent for copy constructor.
     */
    InteractionEvent(const InteractionEvent& rhs) {
      Event::operator=(rhs);
      c = rhs.c;
      data = rhs.data;
    }

    /** \brief Parametrized Constructor.
    *
    * \param id Represents the global id of this event.
    * \param time Exact moment in which it occurred
    * \param interactioner Avatar of the first entity involved in the interaction.
    * \param interactionData Parametric data about the interaction.
    * \param reactObject The second entity involved in the interaction.
    */
    InteractionEvent(uint64_t id, uint64_t time, Interactioner<R>* interactioner, typename R::InteractionData interactionData, std::shared_ptr<ReactObject<R> >  reactObject) : Event(id, time), c(interactioner), data(interactionData), ro(reactObject) {}

    /** \brief base destructor.
    */
    virtual ~InteractionEvent() {};

    /** \brief Copy Operator.
     */
    InteractionEvent& operator=(const InteractionEvent& rhs) {
      Event::operator=(rhs);
      c = rhs.c;
      data = rhs.data;
      return (*this);
    }

    /** \brief Get the entity involved in the interaction.
    * \return The entity involved in the interaction.
    */
    inline Interactioner<R>* getInteractioner() {return (c);}

    /** \brief Get the point of interaction.
    * \return The point of interaction.
    */
    inline typename R::InteractionData getInteractionData() {return (data);}

    /** \brief Get the point of interaction.
    * \return The point of interaction.
    */
    inline std::shared_ptr<ReactObject<R> > getReactObject() {return (ro);}

    /** \brief Manage the current event and, presumably,
     * do the actions associated with it.
     */
    void manage() {
      c->react(&data,ro);
    };

  private:
    Interactioner<R>* c;     //!< First entitie involved avatar.
    typename R::InteractionData data;   //!< Point of interaction.
    std::shared_ptr<ReactObject<R> > ro; //!< second entitie involved. void to avoid template.
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_INTERACTIONEVENT_H
