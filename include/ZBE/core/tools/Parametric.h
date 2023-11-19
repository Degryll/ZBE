/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Parametric.h
 * @since 2021-02-18
 * @date 2021-02-18
 * @author Ludo Batis Degryll
 * @brief Custom implementations of avatar.
 */

#ifndef ZBE_CORE_TOOLS_PARAMETRIC_H_
#define ZBE_CORE_TOOLS_PARAMETRIC_H_

namespace zbe {

template <typename T>
class Parametric {
public:
  virtual ~Parametric() = default;
  virtual void set(T value) = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_PARAMETRIC_H_
