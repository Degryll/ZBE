/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideMobile.h
 * @since 2017-01-30
 * @date 2017-01-30
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the WideMobile interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILE_H

#include "ZBE/archetypes/WideMobile.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/archetypes/implementations/SimpleWide.h"

namespace zbe {

template <unsigned s>
class SimpleWideMobile : virtual public WideMobile<s>, public SimpleMobile<s>, public SimpleWide {
  public:
    SimpleWideMobile(double width) : SimpleMobile<s>(), SimpleWide(width) {}
    SimpleWideMobile(std::initializer_list<double> position, double width) : SimpleMobile<s>(position), SimpleWide(width) {}
    SimpleWideMobile(Point<s> position, double width) : SimpleMobile<s>(position), SimpleWide(width) {}
    SimpleWideMobile(Vector<s> velocity, double width) : SimpleMobile<s>(velocity), SimpleWide(width) {}
    SimpleWideMobile(std::initializer_list<double> position, std::initializer_list<double> velocity, double width) : SimpleMobile<s>(position, velocity), SimpleWide(width) {}
    SimpleWideMobile(Point<s> position, std::initializer_list<double> velocity, double width) : SimpleMobile<s>(position, velocity), SimpleWide(width) {}
    SimpleWideMobile(Point<s> position, Vector<s> velocity, double width) : SimpleMobile<s>(position, velocity), SimpleWide(width) {}
    SimpleWideMobile(std::initializer_list<double> position, Vector<s> velocity, double width) : SimpleMobile<s>(position, velocity), SimpleWide(width) {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILE_H
