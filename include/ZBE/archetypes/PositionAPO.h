/**
 * Copyright 2012 Batis Degryll Ludo
 * @file PositionAPO.h
 * @since 2017-03-30
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts physically and have a position.
 */

#ifndef ZBE_ARCHETYPES_POSITIONAPO_H
#define ZBE_ARCHETYPES_POSITIONAPO_H

#include "ZBE/archetypes/ActivePhysicalObject.h"
#include "ZBE/archetypes/PositionPO.h"

namespace zbe {

/** \brief Defines the interface of an object that interacts physically and have a position.
 */
template <unsigned s>
class PositionAPO : virtual public PositionPO<s>, virtual public ActivePhysicalObject {
public:
  /** \brief Virtual destructor.
   */
  virtual ~PositionAPO() {}
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_POSITIONAPO_H
