/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimplePositionPO.h
 * @since 2017-03-30
 * @date 2017-05-09
 * @author Batis
 * @brief Simple implementation of the PositionPO interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/archetypes/PositionPO.h"
#include "ZBE/archetypes/implementations/SimplePosition.h"
#include "ZBE/archetypes/implementations/SimplePhysicalObject.h"

namespace zbe {

/** \brief Simple implementation of the PositionPO interface.
 */
template <unsigned s>
class SimplePositionPO : virtual public PositionPO<s>, public SimplePosition<s>, public SimplePhysicalObject {
public:
  /** \brief Constructs a SimplePositionPO with position set to 0.
   */
  SimplePositionPO(uint64_t actuatorsList) : SimplePosition<s>(), SimplePhysicalObject(actuatorsList) {}

  /** \brief Constructor with position data as an initializer list.
   */
  SimplePositionPO(Point<s> position, uint64_t actuatorsList) : SimplePosition<s>(position), SimplePhysicalObject(actuatorsList) {}

  /** \brief Constructor with position data as a Point.
   */
  SimplePositionPO(std::initializer_list<double> l, uint64_t actuatorsList) : SimplePosition<s>(l), SimplePhysicalObject(actuatorsList) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimplePositionPO() {}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H
