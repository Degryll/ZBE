/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleBouncingMobileAPO.h
 * @since 2017-03-07
 * @date 2017-03-07
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the Bouncing Mobile active physical object interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGMOBILEAPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGMOBILEAPO_H

#include <cstdint>

#include "ZBE/core/tools/math/collisions/CollisionObject.h"
#include "ZBE/core/tools/math/collisions/ReactObject.h"
#include "ZBE/archetypes/MobileAPO.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"

namespace zbe {

template <typename R, unsigned s>
class SimpleBouncingMobileAPO : virtual public BouncingMovileAPO<R, s>, public SimpleMobileAPO<R, s>, public SimpleBouncing<s> {
  public:
    virtual ~SimpleBouncingMobileAPO(){}
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGMOBILEAPO_H
