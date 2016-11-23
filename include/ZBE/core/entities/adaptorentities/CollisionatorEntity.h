/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionatorEntity.h
 * @since 2016-11-23
 * @date 2016-11-23
 * @author Degryll
 * @brief Entity that can be seen as a collisionator.
 */

#ifndef CORE_ENTITIES_ADAPTORENTITIES_COLLISIONATORENTITY_H_
#define CORE_ENTITIES_ADAPTORENTITIES_COLLISIONATORENTITY_H_

#include "ZBE/core/entities/adaptors/CollisionatorAdaptor.h"
#include "ZBE/core/entities/avatars/Collisionator.h"

namespace zbe {

/** \brief Template that adapts an entity to a drawable.
 */
template <typedef T>
class CollisionatorEntity {
  public:
    CollisionatorEntity(T* entity) : entity(entity) {}

    void setAdaptor(CollisionatorAdaptor *adaptor) {a = adaptor;}

    Collisionator getCollisionator() {return (a->getCollisionator(entity));}

  private:
    T* entity;
    CollisionatorAdaptor<T> *a;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_COLLISIONATORENTITY_H_
