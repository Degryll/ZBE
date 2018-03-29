/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Value.h
 * @since 2017-06-28
 * @date 2018-03-26
 * @author Batis Degryll Ludo
 * @brief Stores a value that can be modified.
 */

#ifndef ZBE_CORE_TOOLS_SHARED_VALUE_H_
#define ZBE_CORE_TOOLS_SHARED_VALUE_H_

namespace zbe {

/** Stores a value that can be modified.
 */
template <typename T>
class Value {
public:

  virtual ~Value(){} //<! Virtual destructor

  /** brief Sets the value.
   *  param value Value to store.
   */
  virtual void setValue(T value) = 0;

  /** brief Returns the value.
   *  return value;
   */
  virtual T getValue() = 0;

  /** brief Modifies stored value by the param received.
   *  param value Value to add.
   */
  virtual void add(T value) = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_SHARED_VALUE_H_
