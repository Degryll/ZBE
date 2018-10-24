/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MobilePO.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll
 * @brief Defines the interface for a Mobile Physical Object.
 */

#ifndef ZBE_ARCHETYPES_MOBILEPO_H
#define ZBE_ARCHETYPES_MOBILEPO_H

#include "ZBE/archetypes/PhysicalObject.h"
#include "ZBE/archetypes/Mobile.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines the interface for a Mobile Physical Object.
 */
template <unsigned s>
class ZBEAPI MobilePO : virtual public Mobile<s>, virtual public PhysicalObject {
public:
  /** \brief Virtual destructor.
   */
  virtual ~MobilePO() {}
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_MOBILEPO_H
