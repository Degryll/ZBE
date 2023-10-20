/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector.h
 * @since 2017-02-28
 * @date 2018-03-27
 * @author Ludo Degryll Batis
 * @brief Vector functions.
 */

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/system/system.h"
#include <cstdio>

namespace zbe {

Vector<2> ZBEAPI reflect(Vector<2> ray, const Vector<2> &normal){
    return ray.reflect(normal);
}

Vector<3> ZBEAPI reflect(Vector<3> ray, const Vector<3> &normal){
    return ray.reflect(normal);
}

Vector<3> ZBEAPI cross(Vector<3> lhs, const Vector<3>& rhs) {
  return (lhs.cross(rhs));
}


double safe_acos(double value) {
    if (value<=-1.0) {
        return PI;
    } else if (value>=1.0) {
        return 0.0;
    } else {
        return acos(value);
    }
}

double angle(Vector<3> lhs, Vector<3> rhs) {
  double dot = (lhs * rhs);
  double len1sqr = lhs * lhs;
  double len2sqr = rhs * rhs;
  double cos = dot /sqrt(len1sqr * len2sqr);
  return safe_acos(cos);
}

}  // namespace
