/**
 * Copyright 2011 Batis Degryll Ludo
 *
 * @file Vector2DPolar.cpp
 *
 * @since 24/07/2011
 * @date 24/07/2011
 * @author Ludo
 * @brief structure used to manage 2d vectors (polar constructor)
 */

#include "ZBE/core/tools/math/Vector2DPolar.h"

namespace zbe {
// TODO(Ludo) tal vez cambiar el parametro m por d
// en ingles se suele llamar distancia
/**
 * @fn Vector2DPolar(double m, double a)
 * @brief Create a vector 2D with distance and angle.
 * @param d double. Distance of the vector.
 * @param a double. Angle of the vector.
 */
Vector2DPolar::Vector2DPolar(double m, double a) {
  this->x = cos(a)*m;
  this->y = sin(a)*m;
}
}
