/**
 * Copyright 2012 Batis Degryll Ludo
 * @file State.h
 * @since 2017-07-02
 * @date 2017-07-02
 * @author Degryll Ludo Batis
 * @brief Defines the interface of a entity that can be counted.
 */

#ifndef ZBE_ARCHETYPES_COUNTABLE_H
#define ZBE_ARCHETYPES_COUNTABLE_H

#include "ZBE/core/tools/shared/value.h"

namespace zbe {

template <typename T>
class Countable {
public:
  /** \brief Parametrized constructor.
      \param ninstances
   */
  Countable(std::shared_ptr<Value<T> > ninstances) : ninstances(ninstances) {
    ninstances->add(1);
  }

  /** \brief Desctructor
  */
  ~Countable() {
    ninstances->add(-1);
  }

private:
  std::shared_ptr<Value<T> > ninstances;
};

} // namespace zbe

#endif  // ZBE_ARCHETYPES_COUNTABLE_H
