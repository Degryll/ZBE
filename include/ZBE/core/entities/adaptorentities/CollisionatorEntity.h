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

 /** \brief Entity that can be seen as a collisionator.
 */
class CollisionatorEntity {
  public:

    virtual Collisionator* getCollisionator() = 0;

};

/** \brief Entity that can be seen as a collisionator using an adaptor.
 */
template <typename T>
class CollisionatorEntityAdapted : CollisionatorEntity {
  public:
    CollisionatorEntityAdapted(T* entity) : entity(entity) {}

    void setAdaptor(CollisionatorAdaptor<T> *adaptor) {a = adaptor;}

    Collisionator* getCollisionator() {return (a->getCollisionator(entity));}

  private:
    T* entity;
    CollisionatorAdaptor<T> *a;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_COLLISIONATORENTITY_H_
