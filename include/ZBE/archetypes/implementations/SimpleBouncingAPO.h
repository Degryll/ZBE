/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleBouncingMobileAPO.h
 * @since 2017-03-07
 * @date 2017-05-06
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the Bouncing Mobile active physical object interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGMOBILEAPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGMOBILEAPO_H

#include "ZBE/archetypes/BouncingMobileAPO.h"
#include "ZBE/archetypes/implementations/SimpleMobileAPO.h"
#include "ZBE/archetypes/implementations/SimpleBouncing.h"

namespace zbe {

/** \brief Simple implementation of the Bouncing Mobile active physical object interface.
 */
template <typename R, unsigned s>
class SimpleBouncingAPO : virtual public BouncingAPO<R, s>, public SimpleMobileAPO<R, s>, public SimpleBouncing<s> {
public:
  /** \brief Virtual destructor.
   */
  virtual ~SimpleBouncingMobileAPO(){}
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGMOBILEAPO_H
