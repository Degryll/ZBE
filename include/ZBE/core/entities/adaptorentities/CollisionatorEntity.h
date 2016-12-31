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
template <typename R>
class CollisionatorEntity {
  public:

    virtual std::shared_ptr<Collisionator<R> > getCollisionator() = 0;

};

/** \brief Entity that can be seen as a collisionator using an adaptor.
 */
template <typename T, typename R>
class CollisionatorEntityAdapted : public CollisionatorEntity<R> {
  public:
    CollisionatorEntityAdapted(T* entity) : entity(entity) {}

    virtual ~CollisionatorEntityAdapted() {delete a;}

    void setAdaptor(CollisionatorAdaptor<T,R> *adaptor) {a = adaptor;}

    std::shared_ptr<Collisionator<R> > getCollisionator() {return (a->getCollisionator(entity));}

  private:
    T* entity;
    CollisionatorAdaptor<T,R> *a;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_COLLISIONATORENTITY_H_
