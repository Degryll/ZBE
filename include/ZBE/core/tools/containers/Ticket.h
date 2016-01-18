/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ticket.h
 * @since 2015/02/15
 * @date 2016/01/08
 * @author Degryll
 * @brief To be used in containers in witch each element can be marked as actived,
 * inactive, erase.
 */

#ifndef CORE_TOOLS_CONTAINERS_TICKET_H_
#define CORE_TOOLS_CONTAINERS_TICKET_H_

namespace zbe {

/** \brief To be used in containers in witch each element can be marked as active, inactive and erased.
 */
class Ticket {
  public:
    enum State{ACTIVE,INACTIVE,ERASED};  //!< The different states.

    /** \brief Parametrized constructor, ACTIVE is the default state.
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

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_TICKET_H_
