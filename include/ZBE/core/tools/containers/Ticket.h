/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ticket.h
 * @since 2015/02/15
 * @date 2015/04/10
 * @author Degryll
 * @brief To be used in containers in witch each element can be marked as active,
 * inactive, erase.
 */

#ifndef CORE_TOOLS_CONTAINERS_TICKET_H_
#define CORE_TOOLS_CONTAINERS_TICKET_H_

namespace zbe {

class Ticket {
  public:
    enum State{ACTIVE,INACTIVE,ERASED};

    Ticket(State state = ACTIVE) : s(state) {}
    virtual ~Ticket() {}

    void setState(State state) {s = state;}
    State getState() const {return (s);}

    void setACTIVE()   {s = ACTIVE;}
    void setINACTIVE() {s = INACTIVE;}
    void setERASED()   {s = ERASED;}

    bool isACTIVE()    {return (s == ACTIVE);}
    bool isNotACTIVE() {return (s != ACTIVE);}
    bool isINACTIVE()  {return (s == INACTIVE);}
    bool isERASED()    {return (s == ERASED);}

  private:
    State s;
};

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_TICKET_H_
