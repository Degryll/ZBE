///**
// * Copyright 2012 Batis Degryll Ludo
// * @file BaseSphereMovableCator.h
// * @since 2017-03-12
// * @date 2017-03-12
// * @author Degryll Ludo Batis
// * @brief This implements a base 1:1 avatar that can be moved and bounce.
// */
//
//#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESPHEREBOUNCERMOVABLECATOR_H_
//#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESPHEREBOUNCERMOVABLECATOR_H_
//
//#include "ZBE/entities/avatars/implementations/BaseSphereMovableCator.h"
//#include "ZBE/entities/avatars/implementations/BaseBouncer.h"
//#include "ZBE/entities/avatars/BouncerMovableCollisionator.h"
//#include "ZBE/archetypes/implementations/SimpleWideBouncingMobileAPO.h"
//
//namespace zbe {
//
///** \brief This implements a base 1:1 avatar that can be moved and bounce.
// */
//template <typename R, unsigned s>
//class BaseSphereBouncerMovableCator : virtual public BouncerMovableCollisionator<R, s>, public BaseBouncer<s>, public BaseSphereMovableCator<R, s> {
//  public:
//    BaseSphereBouncerMovableCator(SimpleWideBouncingMobileAPO<s>* mobile) : BaseBouncer<s>(mobile), BaseSphereMovableCator<R, s>(mobile) {}
//};
//
//}  // namespace zbe
//
//#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESPHEREBOUNCERMOVABLECATOR_H_
