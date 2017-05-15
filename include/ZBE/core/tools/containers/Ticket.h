/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ticket.h
 * @since 2015/02/15
 * @date 2017/05/15
 * @author Degryll Ludo
 * @brief To be used in containers in witch each element can be marked as active,
 * inactive or erase.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_TICKET_H_
#define ZBE_CORE_TOOLS_CONTAINERS_TICKET_H_

#include <memory>

namespace zbe {

/** \brief Ticket to send to and entities so it can mark itself as active, inactive or erase in the related list.
 */
class Ticket {
public:
  enum State{ACTIVE,INACTIVE,ERASED};  //!< The different states.

  /** \brief Parametrized constructor, ACTIVE is the default state.
   *  \param state The initial state of the element
   */
  Ticket(State state = ACTIVE) : s(state) {}

  inline void setState(State state) {s = state;}  //!< Set the State.
  inline State getState() const {return (s);}     //!< Get the current state.

  inline void setACTIVE()   {s = ACTIVE;}    //!< Set the state as ACTIVE.
  inline void setINACTIVE() {s = INACTIVE;}  //!< Set the state as INACTIVE.
  inline void setERASED()   {s = ERASED;}    //!< Set the state as ERASED.

  inline bool isACTIVE()    {return (s == ACTIVE);}    //!< True if state is ACTIVE.
  inline bool isNotACTIVE() {return (s != ACTIVE);}    //!< True if state is not ACTIVE, either INACTIVE or ERASED.
  inline bool isINACTIVE()  {return (s == INACTIVE);}  //!< True if state is INACTIVE.
  inline bool isERASED()    {return (s == ERASED);}    //!< True if state is ERASED.

private:

  State s;  //!< State of the object

};

/** \brief To be used in containers in witch each element can be marked as active, inactive and erased.
 */
template <typename T>
class TicketedElement : public Ticket {
public:

  /** \brief Parametrized constructor, ACTIVE is the default state.
   *  \param element The element
   *  \param state The initial state of the element
   */
  TicketedElement(std::shared_ptr<T> element, State state = ACTIVE) : Ticket(state), e(element) {}

  /** \brief Getter to the element.
   *  \return The element
   */
  inline std::shared_ptr<T> getElement() {return (e);}

private:

  std::shared_ptr<T> e;      //!< Element

};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_TICKET_H_
