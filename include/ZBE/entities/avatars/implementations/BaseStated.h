/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseStated.h
 * @since 2017-06-05
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Base implementation of a state.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESTATED_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESTATED_H_

#include <cstdint>

#include "ZBE/entities/avatars/Stated.h"

namespace zbe {

/** \brief Base implementation of a state.
 */
class BaseStated : virtual public Stated {
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
  void setState(int64_t state) {s->setState(state);}

    /** \brief Adds a value to the state attribute.
   *  \param value The integer value to add to the state.
   */
  void add(int64_t value) {s->add(value);}

  /** \brief Getter for the state attribute.
   *  \return The integer value of the state.
   */
  int64_t getState() {return s->getState();}

private:
  State* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESTATED_H_
