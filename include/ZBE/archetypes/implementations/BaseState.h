/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseState.h
 * @since 2017-08-24
 * @date 2018-02-22
 * @author Degryll Ludo Batis
 * @brief Base implementation of the State interface using a Value<uint64_t>.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_BASESTATE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_BASESTATE_H

#include <cstdint>
#include <memory>

#include "ZBE/archetypes/State.h"

#include "ZBE/core/tools/shared/Value.h"

namespace zbe {

/** \brief Base implementation of the State interface using a Value<uint64_t>.
 */
class BaseState : virtual public State {
public:
  BaseState(std::shared_ptr<Value<int64_t> > state) : s(state) {}

  /** \brief Setter for the state attribute.
   *  \param state The integer value for the state.
   */
  void setState(int64_t state) {s->setValue(state);}

  /** \brief Adds a value to the state attribute.
   *  \param value The integer value to add to the state.
   */
  void add(int64_t value) {s->add(value);}

  /** \brief Getter for the state attribute.
   *  \return The integer value of the state.
   */
  int64_t getState() {return (s->getValue());}

private:
	std::shared_ptr<Value<int64_t> > s;
};

}  // namespace zbe

# endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_BASESTATE_H
