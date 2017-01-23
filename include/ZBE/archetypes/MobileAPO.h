/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Mobile.h
 * @since 2016-12-16
 * @date 2017-01-21
 * @author Degryll
 * @brief Defines the interface for a Mobile Active Physical Object.
 */

#ifndef ZBE_ARCHETYPES_MOBILEAPO_H
#define ZBE_ARCHETYPES_MOBILEAPO_H

#include "ZBE/archetypes/ActivePhysicalObject.h"
#include "ZBE/archetypes/Mobile.h"

namespace zbe {

template <typename R, unsigned s>
class MobileAPO : virtual public Mobile<s>, public ActivePhysicalObject<R> {
  public:
    ~MobileAPO() {}

};

}  // namespace

#endif //ZBE_ARCHETYPES_MOBILEAPO_H
