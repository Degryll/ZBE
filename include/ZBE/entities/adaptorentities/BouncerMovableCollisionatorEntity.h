/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncerMovableCollisionatorEntity.h
 * @since 2017-03-12
 * @date 2017-03-12
 * @author Batis Degryll Ludo
 * @brief Entity that can be seen as a bouncer movable collisionator.
 */

#ifndef ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERMOVABLECOLLISIONATORENTITY_H_
#define ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERMOVABLECOLLISIONATORENTITY_H_

#include <memory>
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/adaptors/BouncerMovableCollisionatorAdaptor.h"
#include "ZBE/entities/adaptorentities/MovableCollisionatorEntity.h"
#include "ZBE/entities/adaptorentities/BouncerCollisionatorEntity.h"

namespace zbe {

/** \brief Entity that can be seen as a bouncer movable collisionator.
 */
template <typename R, unsigned s>
class BouncerMovableCollisionatorEntity : virtual public MovableCollisionatorEntity<R, s>, virtual public BouncerCollisionatorEntity<R, s> {
  public:
    virtual ~BouncerMovableCollisionatorEntity(){}

    virtual std::shared_ptr< BouncerMovableCollisionator<R, s> > getBouncerMovableCollisionator() = 0;

};

/** \brief Entity that can be seen as a bouncer movable collisionator using an adaptor.
 */
template <typename R, typename T, unsigned s>
class BouncerMovableCollisionatorEntityAdapted : virtual public BouncerMovableCollisionatorEntity<R, s> {
  public:
    BouncerMovableCollisionatorEntityAdapted(const BouncerMovableCollisionatorEntityAdapted&) = delete;
    void operator=(const BouncerMovableCollisionatorEntityAdapted&) = delete;

    BouncerMovableCollisionatorEntityAdapted(T* entity) : entity(entity), a(nullptr) {}

    virtual ~BouncerMovableCollisionatorEntityAdapted(){}

    void setBouncerMovableCollisionatorAdaptor(BouncerMovableCollisionatorAdaptor<R, T, s> *adaptor) {a = adaptor;}

    std::shared_ptr< BouncerMovableCollisionator<R, s> > getBouncerMovableCollisionator() {return (a->getBouncerMovableCollisionator(entity));}

    std::shared_ptr< MovableCollisionator<R, s> > getMovableCollisionator() {return (a->getMovableCollisionator(entity));}

    std::shared_ptr< BouncerCollisionator<R, s> > getBouncerCollisionator() {return (a->getBouncerCollisionator(entity));}

    std::shared_ptr< Movable<s> > getMovable() {return (a->getMovable(entity));}

   std::shared_ptr< Bouncer<s> > getBouncer() {return (a->getBouncer(entity));}

    std::shared_ptr<Collisionator<R> > getCollisionator() {return (a->getCollisionator(entity));}

    std::shared_ptr<Collisioner<R> > getCollisioner() {return (a->getCollisionator(entity));}

    std::shared_ptr<ReactObject<R> > getReactObject() {return (a->getCollisionator(entity));}

  private:
    T* entity;
    BouncerMovableCollisionatorAdaptor<R, T, s> *a;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERMOVABLECOLLISIONATORENTITY_H_
