/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideMobile.h
 * @since 2017-03-26
 * @date 2017-03-26
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the Wide archetype.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDE_H

#include "ZBE/archetypes/WideMobile.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"

namespace zbe {

class SimpleWide : virtual public Wide {
  public:
    SimpleWide(double width) :w(width) {}

    void setWidth(double width) {w = width;}
    double getWidth() {return (w);}

  private:
    double w;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDE_H
