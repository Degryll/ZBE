/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector2DCartesian.h
 *
 * @since 22/07/2010
 * @date 22/07/2010
 * @author ludo
 * @brief Implements Vector2Dcartesian class
 */

#ifndef SRC_TOOLS_VECTOR2DCARTESIAN_H_
#define SRC_TOOLS_VECTOR2DCARTESIAN_H_

#include "./Vector2D.h"
namespace zbe {
/**
 * @class Vector2DCartesian
 * @brief Structure used to manage 2d vectors (cartesian constructor)
 */
class Vector2DCartesian: public Vector2D {
  public:

    Vector2DCartesian(double x, double y);
};
}
#endif  // SRC_TOOLS_VECTOR2DCARTESIAN_H_
