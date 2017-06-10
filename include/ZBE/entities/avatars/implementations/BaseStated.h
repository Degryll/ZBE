/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseStated.h
 * @since 2017-06-05
 * @date 2017-06-06
 * @author Batis Degryll Ludo
 * @brief Base implementation of a state.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESTATED_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESTATED_H_

#include <cstdint>

#include "ZBE/archetypes/State.h"

namespace zbe {

/** \brief Base implementation of a state.
 */
class BaseStated {
public:
  BaseStated(const BaseStated&) = delete; //<! Avoid copy
  void operator=(const BaseStated&) = delete; //<! Avoid copy

  /** \brief Builds a stated linked to a state.
   *  \param state The state to be linked to.
   */
  BaseStated(State* state) : s(state) {}

  /** \brief Setter for the state attribute.
   *  \param state The integer value for the state.
   */
  void setState(uint64_t state) {state->setState(state)}

  /** \brief Getter for the state attribute.
   *  \return The integer value of the state.
   */
  uint64_t getState() {return state->getState()}

private:
  State* state;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_STATED_H_
