/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ActivePhysicalObject.h
 * @since 2016-12-16
 * @date 2017-01-19
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts actively physically.
 * Please, if inherit this class, use APO for naming.
 */

#ifndef ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H
#define ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H

#include <cstdint>
#include "ZBE/archetypes/PhysicalObject.h"

namespace zbe {

template <typename R>
class ActivePhysicalObject : virtual public PhysicalObject<R> {
  public:
    virtual ~ActivePhysicalObject() {}

    virtual uint64_t getCollisionablesList() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H
