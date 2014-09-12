/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector2DCartesian.cpp
 *
 * @since 26/07/2011
 * @date 26/07/2011
 * @author Batis
 * @brief Implements Vector2DCartesian class.
 */

#include "ZBE/core/tools/math/Vector2DCartesian.h"

namespace zbe {
/**
 * @fn Vector2DCartesian::Vector2DCartesian(double x, double y)
 * @brief Constructor of Vector2DCartesian that creates a
 * vector with Cartesian coordinates x and y.
 * @param x double. x coordinate.
 * @param y double. y coordinate.
 */
Vector2DCartesian::Vector2DCartesian(double x, double y) {
  this->x = x;
  this->y = y;
}
}
