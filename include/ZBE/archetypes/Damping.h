/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Damping.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Defines the interface of a class with a damping factor.
 */

#ifndef ZBE_ARCHETYPES_DAMPING_H
#define ZBE_ARCHETYPES_DAMPING_H

namespace zbe {

class Damping {
  public:
    ~Damping() {}

    virtual void setFactor(double factor) = 0;
    virtual double getFactor() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_DAMPING_H
