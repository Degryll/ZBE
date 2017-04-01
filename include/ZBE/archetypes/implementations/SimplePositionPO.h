/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimplePositionPO.h
 * @since 2017-03-30
 * @date 2017-03-30
 * @author Batis
 * @brief Simple implementation of the PositionPO interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H

#include "ZBE/archetypes/implementations/SimplePosition.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/archetypes/PositionPO.h"
namespace zbe {

template <unsigned s>
class SimplePositionPO : public PositionPO<s>, public SimplePosition<s> {
  public:

    SimplePositionPO(uint64_t actuatorsList, Point<s> position) : PositionPO<s>(actuatorsList), SimplePosition<s>(position) {}

    virtual ~SimplePositionPO() {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITIONPO_H
