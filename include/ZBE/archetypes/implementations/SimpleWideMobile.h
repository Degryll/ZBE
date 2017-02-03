/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideMobile.h
 * @since 2017-01-30
 * @date 2017-01-30
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the WideMobile interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILE_H
#define ZBE_ARCHETYPES_IMPLEENTATIONS_SIMPLEWIDEMOBILE_H

#include <cstdint>

#include "ZBE/archetypes/WideMobile.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"

namespace zbe {

template <unsigned s>
class SimpleWideMobile : virtual public WideMobile<s>, public SimpleMobile<s> {
  public:
    SimpleWideMobile(uint64_t width) : SimpleMobile<s>(), w(width) {}
    SimpleWideMobile(std::initializer_list<int64_t> position, uint64_t width) : SimpleMobile<s>(position), w(width) {}
    SimpleWideMobile(Point<s> position, uint64_t width) : SimpleMobile<s>(position), w(width) {}
    SimpleWideMobile(Vector<s> velocity, uint64_t width) : SimpleMobile<s>(velocity), w(width) {}
    SimpleWideMobile(std::initializer_list<int64_t> position, std::initializer_list<int64_t> velocity, uint64_t width) : SimpleMobile<s>(position, velocity), w(width) {}
    SimpleWideMobile(Point<s> position, std::initializer_list<int64_t> velocity, uint64_t width) : SimpleMobile<s>(position, velocity), w(width) {}
    SimpleWideMobile(Point<s> position, Vector<s> velocity, uint64_t width) : SimpleMobile<s>(position, velocity), w(width) {}
    SimpleWideMobile(std::initializer_list<int64_t> position, Vector<s> velocity, uint64_t width) : SimpleMobile<s>(position, velocity), w(width) {}

    void setWidth(uint64_t width) {w = width;}
    uint64_t getWidth() {return (w);}

  private:
    uint64_t w;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILE_H
