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
#include "ZBE/archetypes/Damping.h"

namespace zbe {

/** \brief This implements a base 1:1 avatar that can be moved.
 */
class SimpleBounceable {
  public:
    SimpleBounceable(Damping* damping) : d(damping) {}
    double getFactor(){return factor;}

  private:
    Damping* d;
    double factor;
};

}  // namespace zbe

#endif //ZBE_ENTITIES_AVATARS_SIMPLEBOUNCEABLE_H_
