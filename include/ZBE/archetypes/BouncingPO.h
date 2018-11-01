/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncingPO.h
 * @since 2017-03-07
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Defines the interface for a Bouncing Physical Object.
 */

#ifndef ZBE_ARCHETYPES_BOUNCINGPO_H
#define ZBE_ARCHETYPES_BOUNCINGPO_H

#include <cstdint>

#include "ZBE/archetypes/PhysicalObject.h"
#include "ZBE/archetypes/Bouncing.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines the interface for a Bouncing Physical Object.
 */
template <unsigned s>
class BouncingPO : virtual public Bouncing<s>, virtual public PhysicalObject {
public:
  /** \brief Virtual destructor.
   */
  virtual ~BouncingPO() {}
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_BOUNCINGPO_H
