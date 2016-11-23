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

/** \brief Entity that can be seen as a collisioner.
 */
class CollisionerEntity {
  public:

    virtual Collisioner* getCollisioner() = 0;

};

/** \brief Entity that can be seen as a collisioner using an adaptor.
 */
template <typename T>
class CollisionerEntityAdapted {
  public:
    CollisionerEntityAdapted(T* entity) : entity(entity) {}

    void setAdaptor(CollisionerAdaptor<T> *adaptor) {a = adaptor;}

    Collisioner* getCollisioner() {return (a->getCollisioner(entity));}

  private:
    T* entity;
    CollisionerAdaptor<T> *a;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_COLLISIONERENTITY_H_
