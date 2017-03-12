/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleBouncing.h
 * @since 2017-03-07
 * @date 2017-03-07
 * @author Batis Degryll Ludo
 * @brief Defines the interface of a class that stores normals for to bounce.
 */

#ifndef ZBE_ARCHETYPES_SIMPLEBOUNCING_H
#define ZBE_ARCHETYPES_SIMPLEBOUNCING_H

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/archetypes/Bouncing.h"

namespace zbe {

template <unsigned s>
class SimpleBouncing : public Bouncing<s> {
  public:
  	SimpleBouncing()  : n(Vector<s>::zeros()), hasN(false) {}
  	~SimpleBouncing() {}

    void addNormal(const Vector<s>& normal) {n += normal; hasN=true;}
    Vector<s> getNormalSum() {return (n);}
    bool hasNormals() {return (hasN);}
    void clearNormals() {n.setZeros(); hasN=false;}

  private:
  	Vector<s> n;
    bool hasN;
};

}  // namespace

#endif //ZBE_ARCHETYPES_SIMPLEBOUNCING_H
