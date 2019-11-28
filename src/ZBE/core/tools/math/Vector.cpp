/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector.h
 * @since 2017-02-28
 * @date 2018-03-27
 * @author Ludo Degryll Batis
 * @brief Vector functions.
 */

#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

Vector<2> reflect(Vector<2> ray, const Vector<2> &normal){
    return ray.reflect(normal);
}

Vector<3> reflect(Vector<3> ray, const Vector<3> &normal){
    return ray.reflect(normal);
}

Vector<3> cross(Vector<3> lhs, const Vector<3>& rhs) {
 return (lhs.cross(rhs));
}

}  // namespace
