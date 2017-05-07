/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncingMobileAPO.h
 * @since 2017-03-07
 * @date 2017-03-07
 * @author Batis Degryll Ludo
 * @brief Defines the interface for a Bouncing Mobile Active Physical Object.
 */

#ifndef ZBE_ARCHETYPES_BOUNCINGMOBILEAPO_H
#define ZBE_ARCHETYPES_BOUNCINGMOBILEAPO_H

#include "ZBE/archetypes/ActivePhysicalObject.h"
#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/Bouncing.h"

namespace zbe {

template <unsigned s>
class BouncingAPO : virtual public Bouncing<s>, virtual public MobileAPO<s> {
public:
  virtual ~BouncingAPO() {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_BOUNCINGMOBILEAPO_H
