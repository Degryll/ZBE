/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovable2D.h
 * @since 2016-12-17
 * @date 2016-12-17
 * @author Batis
 * @brief #####################################################################
 */

#ifndef ZBE_ENTITIES_AVATARS_SIMPLEBOUNCEABLE_H_
#define ZBE_ENTITIES_AVATARS_SIMPLEBOUNCEABLE_H_

#include "ZBE/entities/avatars/Bounceable.h"

namespace zbe {

/** \brief This implements a base 1:1 avatar that can be moved.
 */
class SimpleBounceable {
  public:
    SimpleBounceable(double factor) : factor(factor) {}
    double getFactor(){return factor;}

  private:
    double factor;
};

}  // namespace zbe

#endif //ZBE_ENTITIES_AVATARS_SIMPLEBOUNCEABLE_H_
