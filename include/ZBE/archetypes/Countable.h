/**
 * Copyright 2012 Batis Degryll Ludo
 * @file State.h
 * @since 2017-07-02
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Defines the interface of a entity that can be counted.
 */

#ifndef ZBE_ARCHETYPES_COUNTABLE_H
#define ZBE_ARCHETYPES_COUNTABLE_H

#include <memory>

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/system.h"

namespace zbe {

template <typename T>
class Countable {
public:
  /** \brief Parametrized constructor.
      \param ninstances
   */
  Countable(std::shared_ptr<Value<T> > ninstances) : ni(ninstances) {
    ni->add(1);
  }

  /** \brief Desctructor
  */
  virtual ~Countable() {
    ni->add(-1);
  }

private:
  std::shared_ptr<Value<T> > ni;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_COUNTABLE_H
