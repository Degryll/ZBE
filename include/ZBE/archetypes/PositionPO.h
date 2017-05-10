/**
 * Copyright 2012 Batis Degryll Ludo
 * @file PositionPO.h
 * @since 2017-03-30
 * @date 2017-05-10
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts physically and have a position 0_0.
 */

#ifndef ZBE_ARCHETYPES_POSITIONPO_H
#define ZBE_ARCHETYPES_POSITIONPO_H

#include "ZBE/archetypes/PhysicalObject.h"
#include "ZBE/archetypes/Position.h"

namespace zbe {

/** \brief Defines the interface of an object that interacts physically and have a position 0_0.
 */
template <unsigned s>
class PositionPO : virtual public Position<s>, virtual public PhysicalObject {
public:
  /** \brief Virtual destructor.
   */
  virtual ~PositionPO() {}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_POSITIONPO_H
