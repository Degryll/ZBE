/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ticket.h
 * @since 2015/02/15
 * @date 2015/02/15
 * @author Degryll
 * @brief To be used in containers in witch each element can be marked as active,
 * inactive, erase.
 */

#ifndef CORE_TOOLS_CONTAINERS_TICKET_H_
#define CORE_TOOLS_CONTAINERS_TICKET_H_

#include <cmath>

namespace zbe {

class ticket {
  public:
    enum State{ACTIVE,INACTIVE,ERASED};

    virtual void setState(State state) const = 0;
    virtual State getState() const = 0;
};

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_TICKET_H_
