///**
// * Copyright 2012 Batis Degryll Ludo
// * @file BouncerCollisionatorAdaptor.h
// * @since 2016-12-16
// * @date 2017-01-21
// * @author Degryll
// * @brief Template that adapts an entity to a Bouncer collisionator.
// */
//
//#ifndef ZBE_ENTITIES_ADAPTORS_BOUNCERCOLLISIONATORADAPTOR_H_
//#define ZBE_ENTITIES_ADAPTORS_BOUNCERCOLLISIONATORADAPTOR_H_
//
//#include <memory>
//
//#include "ZBE/entities/avatars/BouncerCollisionator.h"
//#include "ZBE/entities/adaptors/BouncerAdaptor.h"
//#include "ZBE/core/entities/adaptors/CollisionatorAdaptor.h"
//
//namespace zbe {
//
///** \brief Template that adapts an entity to a Bouncer collisionator.
// */
//template <typename R, typename T, unsigned s>
//class BouncerCollisionatorAdaptor : virtual public BouncerAdaptor<T, s>, virtual public CollisionatorAdaptor<T, R> {
//  public:
//    virtual ~BouncerCollisionatorAdaptor(){};
//
//    virtual std::shared_ptr< BouncerCollisionator<R, s> > getBouncerCollisionator(T* entity) = 0;
//};
//
//}  // namespace zbe
//
//#endif  // ZBE_ENTITIES_ADAPTORS_BOUNCERCOLLISIONATORADAPTOR_H_
