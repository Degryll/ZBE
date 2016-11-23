/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionerEntity.h
 * @since 2016-11-23
 * @date 2016-11-23
 * @author Degryll
 * @brief Entity that can be seen as a collisioner.
 */

#ifndef CORE_ENTITIES_ADAPTORENTITIES_COLLISIONERENTITY_H_
#define CORE_ENTITIES_ADAPTORENTITIES_COLLISIONERENTITY_H_

#include "ZBE/core/entities/adaptors/CollisionerAdaptor.h"
#include "ZBE/core/entities/avatars/Collisioner.h"

namespace zbe {

/** \brief Template that adapts an entity to a drawable.
 */
template <typedef T>
class CollisionerEntity {
  public:
    CollisionerEntity(T* entity) : entity(entity) {}

    void setAdaptor(CollisionerAdaptor *adaptor) {a = adaptor;}

    Collisioner getCollisioner() {return (a->getCollisioner(entity));}

  private:
    T* entity;
    CollisionerAdaptor *a;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_COLLISIONERENTITY_H_
