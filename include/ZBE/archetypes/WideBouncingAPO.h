/**
 * Copyright 2012 Batis Degryll Ludo
 * @file WideBouncingAPO.h
 * @since 2017-01-30
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class with a position, a velocity and a width.
 */

#ifndef ZBE_ARCHETYPES_WIDEBOUNCINGAPO_H
#define ZBE_ARCHETYPES_WIDEBOUNCINGAPO_H

#include "ZBE/archetypes/BouncingAPO.h"
#include "ZBE/archetypes/Wide.h"

namespace zbe {

/** \brief Defines the interface of a class with a position, a velocity and a width.
 */
template <unsigned s>
class WideBouncingAPO : virtual public Wide, virtual public BouncingAPO<s> {
public:
  /** \brief Virtual destructor.
   */
  virtual ~WideBouncingAPO() {}
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_WIDEBOUNCINGAPO_H
