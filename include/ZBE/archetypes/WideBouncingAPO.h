/**
 * Copyright 2012 Batis Degryll Ludo
 * @file WideBouncingAPO.h
 * @since 2017-01-30
 * @date 2017-01-30
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class with a position, a velocity and a width.
 */

#ifndef ZBE_ARCHETYPES_WIDEMOBILE_H
#define ZBE_ARCHETYPES_WIDEMOBILE_H

#include <cstdint>

#include "ZBE/archetypes/BouncingAPO.h"
#include "ZBE/archetypes/Wide.h"

namespace zbe {

template <unsigned s>
class WideBouncingAPO : virtual public BouncingAPO<s>, virtual public Wide {
public:
  virtual ~WideBouncingAPO() {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_WIDEMOBILE_H
