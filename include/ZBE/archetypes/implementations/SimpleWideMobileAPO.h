/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideMobileAPO.h
 * @since 2017-01-30
 * @date 2017-01-30
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class with a position, a velocity and a width.
 */

#ifndef ZBE_ARCHETYPES_SIMPLEWIDEMOBILEAPO_H
#define ZBE_ARCHETYPES_SIMPLEWIDEMOBILEAPO_H

#include "ZBE/archetypes/implementations/SimpleWideMobile.h"
#include "ZBE/archetypes/ActivePhysicalObject.h"

namespace zbe {

template <unsigned s>
class SimpleWideMobileAPO : public SimpleWideMobile<s>, public ActivePhysicalObject {
  public:
    virtual ~SimpleWideMobileAPO() {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_SIMPLEWIDEMOBILEAPO_H
