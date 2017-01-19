/**
 * Copyright 2012 Batis Degryll Ludo
 * @file PhysicalObject.h
 * @since 2016-12-16
 * @date 2017-01-19
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts physically.
 */

#ifndef ZBE_ARCHETYPES_PHYSICALOBJECT_H
#define ZBE_ARCHETYPES_PHYSICALOBJECT_H

#include <cstdint>
#include "ZBE/core/tools/math/collisions/CollisionObject.h"

namespace zbe {

template <typename R>
class PhysicalObject {
  public:
    virtual ~PhysicalObject() {}

    virtual CollisionObject<R> * getCollisionObject() = 0;
    virtual uint64_t getActuatorsList() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_PHYSICALOBJECT_H
