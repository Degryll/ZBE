/**
 * Copyright 2012 Batis Degryll Ludo
 * @file PositionPO.h
 * @since 2017-03-30
 * @date 2017-03-30
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts physically and have a position 0_0.
 */

#ifndef ZBE_ARCHETYPES_POSITIONPO_H
#define ZBE_ARCHETYPES_POSITIONPO_H

#include <cstdint>
#include "ZBE/archetypes/PhysicalObject.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/archetypes/Position.h"

namespace zbe {

template <unsigned s>
class PositionPO : virtual public Position<s>, public PhysicalObject {
public:

  PositionPO (uint64_t actuatorsList) : PhysicalObject(actuatorsList) {}

  virtual ~PositionPO() {}

};

}  // namespace

#endif //ZBE_ARCHETYPES_POSITIONPO_H
