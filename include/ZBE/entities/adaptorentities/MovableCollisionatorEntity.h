/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableCollisionatorEntity.h
 * @since 2016-12-16
 * @date 2017-01-21
 * @author Degryll
 * @brief Entity that can be seen as a movable collisionator.
 */

#ifndef ZBE_ENTITIES_ADAPTORENTITIES_MOVABLECOLLISIONATORENTITY_H_
#define ZBE_ENTITIES_ADAPTORENTITIES_MOVABLECOLLISIONATORENTITY_H_

#include <memory>

#include "ZBE/entities/adaptors/MovableCollisionatorAdaptor.h"
#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/MovableCollisionator.h"
#include "ZBE/core/entities/adaptorentities/CollisionatorEntity.h"

namespace zbe {

/** \brief Entity that can be seen as a movable collisionator.
 */
template <typename R, unsigned s>
class MovableCollisionatorEntity {
  public:
    virtual ~MovableCollisionatorEntity(){}

    virtual std::shared_ptr< MovableCollisionator<R, s> > getMovableCollisionator() = 0;

};

/** \brief Entity that can be seen as a movable collisionator using an adaptor.
 */
template <typename R, typename T, unsigned s>
class MovableCollisionatorEntityAdapted : public MovableCollisionatorEntity<R, s>, public CollisionatorEntity<R>  {
  public:
    MovableCollisionatorEntityAdapted(const MovableCollisionatorEntityAdapted&) = delete;
    void operator=(const MovableCollisionatorEntityAdapted&) = delete;

    MovableCollisionatorEntityAdapted(T* entity) : entity(entity), a(nullptr) {}

    virtual ~MovableCollisionatorEntityAdapted(){}

    void setMovableCollisionatorAdaptor(MovableAdaptor<T, s> *adaptor) {a = adaptor;}

    std::shared_ptr< MovableCollisionator<R, s> > getMovableCollisionator() {return (a->getMovableCollisionator(entity));}

    std::shared_ptr< Movable<s> > getMovable() {return (a->getMovable(entity));}

    std::shared_ptr<Collisionator<R> > getCollisionator() {return (a->getCollisionator(entity));}


  private:
    T* entity;
    MovableCollisionatorAdaptor<R, T, s> *a;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORENTITIES_MOVABLECOLLISIONATORENTITY_H_
