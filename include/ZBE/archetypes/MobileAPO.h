/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MobileAPO.h
 * @since 2016-12-16
 * @date 2017-05-10
 * @author Degryll
 * @brief Defines the interface for a Mobile Active Physical Object.
 */

#ifndef ZBE_ARCHETYPES_MOBILEAPO_H
#define ZBE_ARCHETYPES_MOBILEAPO_H

#include "ZBE/archetypes/ActivePhysicalObject.h"
#include "ZBE/archetypes/MobilePO.h"

namespace zbe {

/** \brief Defines the interface for a Mobile Active Physical Object.
 */
template <unsigned s>
class MobileAPO : virtual public MobilePO<s>, virtual public ActivePhysicalObject {
public:
  /** \brief Virtual destructor.
   */
  virtual ~MobileAPO() {}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_MOBILEAPO_H
