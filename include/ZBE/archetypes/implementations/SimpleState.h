/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleState.h
 * @since 2017-06-04
 * @date 2017-08-05
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the State interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H

#include "ZBE/archetypes/State.h"

namespace zbe {

class SimpleState : public State {
public:
  SimpleState(int64_t state = 0) : s(state) {}

  void setState(int64_t state) {s = state;}

  void add(int64_t value) {s += value;}

  /** \brief
   *
   * \return int64_t
   *
   */
  int64_t getState() {return s;}

private:
	int64_t s;
};

}  // namespace zbe
# endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H
