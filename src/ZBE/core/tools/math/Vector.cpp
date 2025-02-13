/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector.h
 * @since 2017-02-28
 * @date 2018-03-27
 * @author Ludo Degryll Batis
 * @brief Vector functions.
 */

#include <cstdint>
#include <cstdio>

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

double angle(Vector<2> lhs, Vector<2> rhs) {
  double dot = (lhs * rhs);
  double len1sqr = lhs * lhs;
  double len2sqr = rhs * rhs;
  double cos = dot /sqrt(len1sqr * len2sqr);
  return safe_acos(cos);
}

int halfspace(Point2D p, Point2D linePoint1, Point2D linePoint2) {
    Point2D lineVector = {linePoint2.x - linePoint1.x, linePoint2.y - linePoint1.y};
    Point2D vectorToPoint = {p.x - linePoint1.x, p.y - linePoint1.y};
    double crossProduct = (lineVector.x * vectorToPoint.y) - (vectorToPoint.x * lineVector.y);
    if (crossProduct > 0.0) {
        return 1; // Punto a la izquierda de la recta (sentido antihorario)
    } else if (crossProduct < 0.0) {
        return -1; // Punto a la derecha de la recta (sentido horario)
    } else {
        return 0; // Punto sobre la recta
    }

}

Point2D triangleCenter(Point2D vertex1, Point2D vertex2, Point2D vertex3) {
    Point2D center;
    // Calcular el promedio de las coordenadas x e y de los vértices
    center.x = (vertex1.x + vertex2.x + vertex3.x) / 3.0;
    center.y = (vertex1.y + vertex2.y + vertex3.y) / 3.0;
    return center;
}

}  // namespace
