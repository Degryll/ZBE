///**
// * Copyright 2012 Batis Degryll Ludo
// * @file BaseSphereBouncerMCMAPOAdaptor.h
// * @since 2017-03-12
// * @date 2017-03-12
// * @author Batis Degryll Ludo
// * @brief Implementation that adapts a SimpleWideBouncingMobileAPO entity to a BouncerMovableCollisionator.
// */
//
//#ifndef ZBE_ENTITIES_ADAPTORS_BASESSPHEREBOUNCERMCMAPOADAPTOR_H_
//#define ZBE_ENTITIES_ADAPTORS_BASESSPHEREBOUNCERMCMAPOADAPTOR_H_
//
//#include <memory>
//
//#include "ZBE/core/entities/avatars/Collisionator.h"
//#include "ZBE/entities/avatars/implementations/BaseSphereBouncerMovableCator.h"
//#include "ZBE/entities/avatars/BouncerMovableCollisionator.h"
//#include "ZBE/entities/avatars/Movable.h"
//#include "ZBE/entities/avatars/Bouncer.h"
//#include "ZBE/entities/avatars/MovableCollisionator.h"
//#include "ZBE/entities/avatars/BouncerCollisionator.h"
//#include "ZBE/archetypes/implementations/SimpleWideBouncingMobileAPO.h"
//#include "ZBE/entities/adaptors/BouncerMovableCollisionatorAdaptor.h"
//
//namespace zbe {
//
///** \brief Implementation that adapts a SimpleWideBouncingMobileAPO entity to a BouncerMovableCollisionator.
// */
//template <typename R, unsigned s>
//class BaseSphereBouncerMCMAPOAdaptor : public BouncerMovableCollisionatorAdaptor<R, SimpleWideBouncingMobileAPO<s>, s> {
//  public:
//
//    std::shared_ptr<BouncerMovableCollisionator<R, s> > getBouncerMovableCollisionator(SimpleWideBouncingMobileAPO<s>* entity) {
//        std::shared_ptr<BouncerMovableCollisionator<R, s> > p(new BaseSphereBouncerMovableCator<R, s>(entity));
//        return (p);
//    }
//
//    std::shared_ptr<Collisionator<R> > getCollisionator(SimpleWideBouncingMobileAPO<s>* entity) {
//        std::shared_ptr<Collisionator<R> > p(new BaseSphereBouncerMovableCator<R, s>(entity));
//        return (p);
//    }
//
//    std::shared_ptr<Movable<s> > getMovable(SimpleWideBouncingMobileAPO<s>* entity) {
//        std::shared_ptr<Movable<s> > p(new BaseSphereBouncerMovableCator<R, s>(entity));
//        return (p);
//    }
//
//    std::shared_ptr<Bouncer<s> > getBouncer(SimpleWideBouncingMobileAPO<s>* entity) {
//        std::shared_ptr<Bouncer<s> > p(new BaseSphereBouncerMovableCator<R, s>(entity));
//        return (p);
//    }
//
//    std::shared_ptr<MovableCollisionator<R, s> > getMovableCollisionator(SimpleWideBouncingMobileAPO<s>* entity) {
//        std::shared_ptr<MovableCollisionator<R, s> > p(new BaseSphereBouncerMovableCator<R, s>(entity));
//        return (p);
//    }
//
//    std::shared_ptr<BouncerCollisionator<R, s> > getBouncerCollisionator(SimpleWideBouncingMobileAPO<s>* entity) {
//        std::shared_ptr<BouncerCollisionator<R, s> > p(new BaseSphereBouncerMovableCator<R, s>(entity));
//        return (p);
//    }
//};
//
//}  // namespace zbe
//
//#endif  // ZBE_ENTITIES_ADAPTORS_BASESSPHEREBOUNCERMCMAPOADAPTOR_H_
