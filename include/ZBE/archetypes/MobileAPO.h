/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MobileAPO.h
 * @since 2016-12-16
 * @date 2017-01-21
 * @author Degryll
 * @brief Defines the interface for a Mobile Active Physical Object.
 */

#ifndef ZBE_ARCHETYPES_MOBILEAPO_H
#define ZBE_ARCHETYPES_MOBILEAPO_H

#include <cstdint>

#include "ZBE/archetypes/MobilePO.h"
#include "ZBE/archetypes/PositionAPO.h"

namespace zbe {

template <unsigned s>
class MobileAPO : virtual public MobilePO<s>, virtual public PositionAPO<s> {
public:
  virtual ~MobileAPO() {}

};

}  // namespace

#endif //ZBE_ARCHETYPES_MOBILEAPO_H
