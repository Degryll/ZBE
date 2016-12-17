/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleDamping.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Simple implementation of the Damping interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDAMPING_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDAMPING_H

#include "ZBE/archetypes/Damping.h"

namespace zbe {

class SimpleDamping : public Damping {
  public:
    SimpleDamping() : df(.0) {}
    SimpleDamping(double factor) : df(factor) {}

    void setFactor(double factor) {df = factor;}
    double getFactor() {return (df);}

  private:
    double df;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDAMPING_H
