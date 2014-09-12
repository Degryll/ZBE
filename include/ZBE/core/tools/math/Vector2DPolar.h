/**
 * Copyright 2011 Batis Degryll Ludo
 *
 * @file Vector2DPolar.h
 *
 * @since 22/07/2010
 * @date 24/07/2011
 * @author Ludo
 * @brief structure used to manage 2d vectors (polar constructor)
 */

#ifndef SRC_TOOLS_VECTOR2DPOLAR_H_
#define SRC_TOOLS_VECTOR2DPOLAR_H_

#include "./Vector2D.h"
namespace zbe {
/**
 * @class Vector2DPolar
 * @brief Implements a polar construction of a vector2D.
 */
class Vector2DPolar: public Vector2D {
  public:

    // TODO(Ludo) tal vez cambiar el parametro m por d
    // en ingles se suele llamar distancia
    Vector2DPolar(double m, double a);
};
}
#endif  // SRC_TOOLS_VECTOR2DPOLAR_H_
