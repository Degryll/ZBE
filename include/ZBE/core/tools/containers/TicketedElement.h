/**
 * Copyright 2011 Batis Degryll Ludo
 * @file TicketedElement.h
 * @since 2018-05-06
 * @date 2018-05-06
 * @author Degryll Ludo Batis
 * @brief To be used in containers in witch each element can be marked as active, inactive and erased.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_TICKETEDELEMENT_H_
#define ZBE_CORE_TOOLS_CONTAINERS_TICKETEDELEMENT_H_

#include <memory>

#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief To be used in containers in witch each element can be marked as active, inactive and erased.
 */
template <typename T>
class TicketedElement : public Ticket {
public:

  /** \brief Parametrized constructor, ACTIVE is the default state.
   *  \param element The element
   *  \param state The initial state of the element
   */
  TicketedElement(std::shared_ptr<T> element) : s(ACTIVE), e(element) {}

  /** \brief Getter to the element.
   *  \return The element
   */
  inline std::shared_ptr<T> getElement() {return (e);}

  inline void setACTIVE()   {s = ACTIVE;}    //!< Set the state as ACTIVE.
  inline void setINACTIVE() {s = INACTIVE;}  //!< Set the state as INACTIVE.
  inline void setERASED()   {s = ERASED;}  //!< Set the state as ERASED.

  inline void setState(State state) {s = state;}  //!< Set the state as state.

  inline void toggle() {
    if(s == ACTIVE) {
      s = INACTIVE;
    } else if(s == INACTIVE) {
      s = ACTIVE;
    }
  }  //!< Set the state as state.

  inline bool isACTIVE()    {return (s == ACTIVE);}    //!< True if state is ACTIVE.
  inline bool isNotACTIVE() {return (s != ACTIVE);}    //!< True if state is not ACTIVE, either INACTIVE or ERASED.
  inline bool isINACTIVE()  {return (s == INACTIVE);}  //!< True if state is INACTIVE.
  inline bool isERASED()    {return (s == ERASED);}    //!< True if state is ERASED.

  inline State getState() {return (s);}  //!< Return the state of the ticket.

private:

  State s;  //!< State of the object
  std::shared_ptr<T> e;      //!< Element

};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_TICKETEDELEMENT_H_
