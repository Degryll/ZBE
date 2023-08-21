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

double angle(Vector<3> lhs, Vector<3> rhs) {
  double dot = (lhs * rhs);
  double cos = dot /(lhs.getModule() + rhs.getModule());
  return acos(cos);
}

}  // namespace
