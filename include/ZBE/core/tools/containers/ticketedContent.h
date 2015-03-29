/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ticketed_content.h
 * @since 2015/02/08
 * @date 2015/02/15
 * @author Degryll
 * @brief To be used in containers wich each element can be marked as active,
 * inactive, erase.
 */

#ifndef CORE_TOOLS_CONTAINERS_TICKETEDCONTENT_H_
#define CORE_TOOLS_CONTAINERS_TICKETEDCONTENT_H_

#include <cmath>
#include "ticket.h"

namespace zbe {

template<typename ValueType>
class ticketedContent : ticket {
  public:
    ticketedContent(ValueType *value, State state = ACTIVE) : v(value), s(state) {}
    virtual ~ticketedContent() {}

    ValueType* content() const {return (v);}

    void setState(State state) {s = state;}
    State getState() {return (s);}

  private:
    ValueType *v;
    State s;
};

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_TICKETEDCONTENT_H_
