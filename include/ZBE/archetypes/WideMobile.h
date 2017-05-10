/**
 * Copyright 2012 Batis Degryll Ludo
 * @file WideMobile.h
 * @since 2017-01-30
 * @date 2017-05-10
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class with a position, a velocity and a width.
 */

#ifndef ZBE_ARCHETYPES_WIDEMOBILE_H
#define ZBE_ARCHETYPES_WIDEMOBILE_H

#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/Wide.h"

namespace zbe {

/** \brief Defines the interface of a class with a position, a velocity and a width.
 */
template <unsigned s>
class WideMobile : virtual public Mobile<s>, virtual public Wide {
public:
  /** \brief Virtual destructor.
   */
  virtual ~WideMobile() {}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_WIDEMOBILE_H
