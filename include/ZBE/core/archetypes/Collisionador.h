/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Collisionador.h
 * @since 2014-09-22
 * @date 2014-09-22
 * @author Ludo and Degryll
 * @brief Define a class that participate in collision system.
 */

#ifndef CORE_ARCHETYPES_COLLISIONADOR_H_
#define CORE_ARCHETYPES_COLLISIONADOR_H_

#include "ZBE/core/CollisionData.h"

namespace zbe {

class Collisionador : Collisioner {
  public:
    virtual ~Collisionador() {}

    double collisionDetection(std::forward_list<CollisionData> *cdata, double timeRemain);
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_COLLISIONADOR_H_
