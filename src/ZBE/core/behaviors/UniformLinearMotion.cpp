/**
 * Copyright 2012 Batis Degryll Ludo
 * @file UniformLinearMotion.cpp
 * @since 2015-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Updates the position of an object based on its speed.
 *        Requires Movible.
 */

#include "ZBE/core/behaviors/UniformLinearMotion.h"

namespace zbe {

void UniformLinearMotion::behaveUntil(double time) {
  for(auto it = first; it != last; ++it) {
    int vx = it->getVelocityX();
    int vy = it->getVelocityY();
    it->increaseX(int(vx*time));
    it->increaseY(int(vy*time));
  }
}

}  // namespace zbe
