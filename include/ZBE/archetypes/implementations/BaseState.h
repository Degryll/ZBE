/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseState.h
 * @since 2017-08-24
 * @date 2017-08-24
 * @author Degryll Ludo Batis
 * @brief Base implementation of the State interface using a Value<uint64_t>.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_BASESTATE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_BASESTATE_H

#include <memory>

#include "ZBE/archetypes/State.h"

#include "ZBE/core/tools/shared/Value.h"

namespace zbe {

class BaseState : public State {
public:
  BaseState(std::shared_ptr<Value<int64_t> > state) : s(state) {}

  void setState(int64_t state) {s->setValue(state);}

  void add(int64_t value) {s->add(value);}

  int64_t getState() {return (s->getValue());}

private:
	std::shared_ptr<Value<int64_t> > s;
};

}  // namespace zbe
# endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_BASESTATE_H
