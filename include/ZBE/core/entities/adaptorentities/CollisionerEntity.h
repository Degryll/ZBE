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
#include "ZBE/core/entities/avatars/ReactObject.h"

namespace zbe {

/** \brief Entity that can be seen as a collisioner.
 */
class CollisionerEntity {
  public:

    virtual ~CollisionerEntity();

    virtual Collisioner* getCollisioner() = 0;

  	virtual ReactObject* getReactObject() = 0;

};

/** \brief Entity that can be seen as a collisioner using an adaptor.
 */
template <typename T>
class CollisionerEntityAdapted {
  public:
    CollisionerEntityAdapted(T* entity) : entity(entity) {}

    void setCollisionerAdaptor(CollisionerAdaptor<T> *adaptor) {c = adaptor;}

    Collisioner* getCollisioner() {return (c->getCollisioner(entity));}

  	void setReactObjectAdaptor(ReactObjectAdaptor<T> *adaptor) {r = adaptor;}

  	ReactObject* getReactObject() {return (r->getReactObject(entity));}

  private:
    T* entity;
    CollisionerAdaptor<T> *c;
  	ReactObjectAdaptor<T> *r;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_COLLISIONERENTITY_H_
