/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleState.h
 * @since 2017-06-04
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the State interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H

#include <cstdint>

#include "ZBE/archetypes/State.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Simple implementation of the State interface.
 */
class SimpleState : public State {
public:

  /** \brief Constructs a SimpleState with a state value (default 0).
   */
  SimpleState(int64_t state = 0) : s(state) {}

  /** \brief Sets state value
   *  \param state int64_t value for state.
   *  \sa getState, add
   */
  void setState(int64_t state) {s = state;}

  /** \brief Adds given value to internal one.
   *  \param state int64_t value to add.
   *  \sa getState, setState
   */
  void add(int64_t value) {s += value;}

  /** \brief Returns state value
   * \return int64_t value for the state.
   */
  int64_t getState() {return s;}

private:
	int64_t s;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLESTATE_H
