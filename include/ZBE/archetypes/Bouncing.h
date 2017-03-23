/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bouncing.h
 * @since 2017-03-07
 * @date 2017-03-07
 * @author Batis Degryll Ludo
 * @brief Defines the interface of a class that stores normals for to bounce.
 */

#ifndef ZBE_ARCHETYPES_BOUNCING_H
#define ZBE_ARCHETYPES_BOUNCING_H

#include "ZBE/archetypes/Mobile.h"

namespace zbe {

template <unsigned s>
class Bouncing : virtual public Mobile<s> {
  public:
    ~Bouncing() {}
  	virtual void addNormal(const Vector<s>& normal) = 0;
  	virtual Vector<s> getNormalSum() = 0;
  	virtual bool hasNormals() = 0;
  	virtual void clearNormals() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_BOUNCING_H
