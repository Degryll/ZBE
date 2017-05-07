/**
 * Copyright 2012 Batis Degryll Ludo
 * @file PositionAPO.h
 * @since 2017-03-30
 * @date 2017-03-30
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts physically and have a position 0_0.
 */

#ifndef ZBE_ARCHETYPES_POSITIONAPO_H
#define ZBE_ARCHETYPES_POSITIONAPO_H

#include <cstdint>

#include "ZBE/archetypes/PositionPO.h"
#include "ZBE/archetypes/ActivePhysicalObject.h"

namespace zbe {

template <unsigned s>
class PositionAPO : virtual public PositionPO<s>, virtual public ActivePhysicalObject {
public:
  virtual ~PositionAPO() {}

};

}  // namespace

#endif //ZBE_ARCHETYPES_POSITIONAPO_H
