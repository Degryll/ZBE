/**
 * Copyright 2012 Batis Degryll Ludo
 * @file WideMobile.h
 * @since 2017-01-30
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class ZBEAPI with a position, a velocity and a width.
 */

#ifndef ZBE_ARCHETYPES_WIDEMOBILE_H
#define ZBE_ARCHETYPES_WIDEMOBILE_H

#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/Wide.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines the interface of a class ZBEAPI with a position, a velocity and a width.
 */
template <unsigned s>
class WideMobile : virtual public Wide, virtual public Mobile<s> {
public:
  /** \brief Virtual destructor.
   */
  virtual ~WideMobile() {}
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_WIDEMOBILE_H
