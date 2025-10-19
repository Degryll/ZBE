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

#include <string>
#include <nlohmann/json.hpp>

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/system/system.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/factories/Factory.h"

namespace zbe {

/** Stores a value that can be modified.
 */
template <typename T>
class SimpleValue : public Value<T> {
public:
  /** brief Void constructor.
   */
  SimpleValue() = default;

  /** brief Parametrized contructor.
   *  param value Value to store.
   */
  explicit SimpleValue(T value) : v(value) {}

  /** brief Sets the value.
   *  param value Value to store.
   */
  void set(T value) override {
    v = value ;
  }

  /** brief Returns the value.
   *  return value;
   */
  T& get() override {
    return v;
  }

// TODO no funciona con vector
//  /** brief Modifies stored value by the param received.
//   *  param value Value to add.
//   */
//  void add(T value) {
//    v += value;
//  }

private:
  T v;
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_
