/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleValue.h
 * @since 2017-06-28
 * @date 2017-06-28
 * @author Batis Degryll Ludo
 * @brief Stores a value that can be modified.
 */

#ifndef ZBE_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_
#define ZBE_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_

#include "ZBE/core/tools/shared/Value.h"

namespace zbe {

/** Stores a value that can be modified.
 */
template <typename T>
class SimpleValue : public Value<T> {
public:
  /** brief Void constructor.
   */
  SimpleValue() : v() {}

  /** brief Parametrized contructor.
   *  param value Value to store.
   */
  SimpleValue(T value) : v(value) {}

  /** brief Sets the value.
   *  param value Value to store.
   */
  void setValue(T value) {
    v = value ;
  }

  /** brief Returns the value.
   *  return value;
   */
  T getValue() {
    return v;
  }

  /** brief Modifies stored value by the param received.
   *  param value Value to add.
   */
  void add(T value) {
    v += value;
  }

private:
  T v;
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_
