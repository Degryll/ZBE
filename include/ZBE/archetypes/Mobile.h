/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Mobile.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Defines the interface of a class with a position and a velocity.
 */

#ifndef ZBE_ARCHETYPES_MOBILE_H
#define ZBE_ARCHETYPES_MOBILE_H

#include "ZBE/archetypes/Position.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

template <unsigned s>
class Mobile : public Position<s> {
  public:
    virtual ~Mobile() {}

    virtual void setVelocity(std::initializer_list<double> l) = 0;
    virtual void setVelocity(Vector<s> velocity) = 0;

    virtual Vector<s>& getVelocity() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_MOBILE_H
