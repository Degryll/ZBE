/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Position.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Defines the interface of a class with a position.
 */

#ifndef ZBE_ARCHETYPES_POSITION_H
#define ZBE_ARCHETYPES_POSITION_H

#include "ZBE/core/tools/math/Point.h"

namespace zbe {

template <unsigned s>
class Position {
  public:
    virtual ~Position() {}

    virtual void setPosition(std::initializer_list<double> l) = 0;
    virtual void setPosition(Point<s> position) = 0;

    virtual Point<s>& getPosition() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_POSITION_H
