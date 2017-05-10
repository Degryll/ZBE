/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncingAPO.h
 * @since 2017-03-07
 * @date 2017-05-10
 * @author Batis Degryll Ludo
 * @brief Defines the interface for a Bouncing Active Physical Object.
 */

#ifndef ZBE_ARCHETYPES_BOUNCINGAPO_H
#define ZBE_ARCHETYPES_BOUNCINGAPO_H

#include "ZBE/archetypes/ActivePhysicalObject.h"
#include "ZBE/archetypes/BouncingPO.h"

namespace zbe {

/** \brief Defines the interface for a Bouncing Active Physical Object.
 */
template <unsigned s>
class BouncingAPO : virtual public BouncingPO<s>, virtual public ActivePhysicalObject {
public:
  /** \brief Virtual destructor.
   */
  virtual ~BouncingAPO() {}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_BOUNCINGAPO_H
