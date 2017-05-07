/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MobilePO.h
 * @since 2016-12-16
 * @date 2017-01-21
 * @author Degryll
 * @brief Defines the interface for a Mobile Physical Object.
 */

#ifndef ZBE_ARCHETYPES_MOBILEPO_H
#define ZBE_ARCHETYPES_MOBILEPO_H

#include <cstdint>

#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/PositionPO.h"

namespace zbe {

template <unsigned s>
class MobilePO : virtual public Mobile<s>, virtual public PositionPO<s> {
public:
  virtual ~MobilePO() {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_MOBILEPO_H
