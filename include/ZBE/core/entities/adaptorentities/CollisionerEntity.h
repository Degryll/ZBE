/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionerEntity.h
 * @since 2016-11-23
 * @date 2016-12-14
 * @author Degryll
 * @brief Entity that can be seen as a collisioner.
 */

#ifndef CORE_ENTITIES_ADAPTORENTITIES_COLLISIONERENTITY_H_
#define CORE_ENTITIES_ADAPTORENTITIES_COLLISIONERENTITY_H_

#include "ZBE/core/entities/adaptors/CollisionerAdaptor.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/adaptors/ReactObjectAdaptor.h"
#include "ZBE/core/tools/math/collisions/ReactObject.h"

namespace zbe {

/** \brief Entity that can be seen as a collisioner.
 */
template <typename R>
class CollisionerEntity {
  public:

    virtual ~CollisionerEntity() {};

    virtual std::shared_ptr<Collisioner<R> > getCollisioner() = 0;
};

/** \brief Entity that can be seen as a collisioner using an adaptor.
 */
template <typename T, typename R>
class CollisionerEntityAdapted : public CollisionerEntity<R> {
  public:
    CollisionerEntityAdapted(T* entity) : entity(entity) {}

    virtual ~CollisionerEntityAdapted(){}

    void setCollisionerAdaptor(CollisionerAdaptor<T, R> *adaptor) {c = adaptor;}

    CollisionerAdaptor<T, R>* getCollisionerAdaptor() {return (c);}

    std::shared_ptr<Collisioner<R> > getCollisioner() {return (c->getCollisioner(entity));}

  private:
    T* entity;
    CollisionerAdaptor<T, R> *c;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_COLLISIONERENTITY_H_
