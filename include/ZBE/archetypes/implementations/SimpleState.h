/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleState.h
 * @since 2017-06-04
 * @date 2017-06-04
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the State interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H

#include "ZBE/archetypes/State.h"

namespace zbe {

class SimpleState : public State {
public:
  SimpleState(uint64_t state = 0) : s(state) {}

  void setState(uint64_t state) {s = state;}
  uint64_t getState() {return s;}

private:
	uint64_t s;
};

}  // namespace zbe
# endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H
