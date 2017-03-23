///**
// * Copyright 2012 Batis Degryll Ludo
// * @file BouncerCollisionatorEntity.h
// * @since 2017-03-12
// * @date 2017-03-12
// * @author Batis Degryll Ludo
// * @brief Entity that can be seen as a Bouncer collisionator.
// */
//
//#ifndef ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERCOLLISIONATORENTITY_H_
//#define ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERCOLLISIONATORENTITY_H_
//
//#include <memory>
//
//#include "ZBE/entities/adaptorentities/BouncerEntity.h"
//#include "ZBE/entities/avatars/Bouncer.h"
//#include "ZBE/entities/avatars/BouncerCollisionator.h"
//#include "ZBE/core/entities/adaptorentities/CollisionatorEntity.h"
//
//namespace zbe {
//
///** \brief Entity that can be seen as a Bouncer collisionator.
// */
//template <typename R, unsigned s>
//class BouncerCollisionatorEntity : virtual public BouncerEntity<s>, virtual public MovableCollisionatorEntity<R, s>,  virtual public CollisionatorEntity<R> {
//  public:
//    virtual ~BouncerCollisionatorEntity(){}
//
//    virtual std::shared_ptr< BouncerCollisionator<R, s> > getBouncerCollisionator() = 0;
//
//};
//
//
///** \brief Entity that can be seen as a bouncer movable collisionator using an adaptor.
// */
//template <typename R, typename T, unsigned s>
//class BouncerCollisionatorEntityAdapted : virtual public BouncerCollisionatorEntity<R, s> {
//  public:
//    BouncerCollisionatorEntityAdapted(const BouncerCollisionatorEntityAdapted&) = delete;
//    void operator=(const BouncerCollisionatorEntityAdapted&) = delete;
//
//    BouncerCollisionatorEntityAdapted(T* entity) : entity(entity), a(nullptr) {}
//
//    virtual ~BouncerCollisionatorEntityAdapted(){}
//
//    void setBouncerCollisionatorAdaptor(BouncerCollisionatorAdaptor<R, T, s> *adaptor) {a = adaptor;}
//
//    std::shared_ptr< MovableCollisionator<R, s> > getMovableCollisionator() {return (a->getMovableCollisionator(entity));}
//
//    std::shared_ptr< BouncerCollisionator<R, s> > getBouncerCollisionator() {return (a->getBouncerCollisionator(entity));}
//
//    std::shared_ptr< Movable<s> > getMovable() {return (a->getMovable(entity));}
//
//   std::shared_ptr< Bouncer<s> > getBouncer() {return (a->getBouncer(entity));}
//
//    std::shared_ptr<Collisionator<R> > getCollisionator() {return (a->getCollisionator(entity));}
//
//    std::shared_ptr<Collisioner<R> > getCollisioner() {return (a->getCollisionator(entity));}
//
//    std::shared_ptr<ReactObject<R> > getReactObject() {return (a->getCollisionator(entity));}
//
//  private:
//    T* entity;
//    BouncerCollisionatorAdaptor<R, T, s> *a;
//};
//
//}  // namespace zbe
//
//#endif  // ZBE_ENTITIES_ADAPTORENTITIES_BOUNCERCOLLISIONATORENTITY_H_
