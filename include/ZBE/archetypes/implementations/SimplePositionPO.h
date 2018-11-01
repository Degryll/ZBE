/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimplePositionPO.h
 * @since 2017-03-30
 * @date 2018-02-25
 * @author Batis
 * @brief Simple implementation of the PositionPO interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H

#include <cstdint>
#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"

#include "ZBE/archetypes/PositionPO.h"
#include "ZBE/archetypes/implementations/SimplePosition.h"
#include "ZBE/archetypes/implementations/SimplePhysicalObject.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Simple implementation of the PositionPO interface.
 */
template <unsigned s>
class SimplePositionPO : virtual public PositionPO<s>, public SimplePosition<s>, public SimplePhysicalObject {
public:
  /** \brief Constructs a SimplePositionPO with position set to 0.
   */
  SimplePositionPO(uint64_t actuatorsList) : SimplePosition<s>(), SimplePhysicalObject(actuatorsList) {}

  /** \brief Constructor with position data as a Point.
   */
  SimplePositionPO(Point<s> position, uint64_t actuatorsList) : SimplePosition<s>(position), SimplePhysicalObject(actuatorsList) {}

  /** \brief Constructor with position data as an initializer list.
   */
  SimplePositionPO(std::initializer_list<double> l, uint64_t actuatorsList) : SimplePosition<s>(l), SimplePhysicalObject(actuatorsList) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimplePositionPO() {}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H
