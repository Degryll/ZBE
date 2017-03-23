///**
// * Copyright 2012 Batis Degryll Ludo
// * @file BounceableEntity.h
// * @since 2016-12-17
// * @date 2016-12-17
// * @author Batis
// * @brief Entity that can be seen as a Bounceable.
// */
//
//#ifndef ZBE_ENTITIES_ADAPTORENTITIES_BOUNCEABLEENTITY_H_
//#define ZBE_ENTITIES_ADAPTORENTITIES_BOUNCEABLEENTITY_H_
//
//#include <memory>
//
//#include "ZBE/entities/adaptors/BounceableAdaptor.h"
//#include "ZBE/entities/avatars/Bounceable.h"
//
//namespace zbe {
//
///** \brief Entity that can be seen as a Bounceable.
// */
//class BounceableEntity {
//  public:
//
//    virtual std::shared_ptr<Bounceable> getBounceable() = 0;
//
//};
//
///** \brief Entity that can be seen as a Bounceable using an adaptor.
// */
//template <typename T>
//class BounceableEntityAdapted : public BounceableEntity {
//  public:
//    BounceableEntityAdapted(T* entity) : entity(entity) {}
//
//    void setAdaptor(BounceableAdaptor *adaptor) {a = adaptor;}
//
//    std::shared_ptr<Bounceable> getBounceable() {return (a->getBounceable(entity));}
//
//  private:
//    T* entity;
//    BounceableAdaptor *a;
//};
//
//}  // namespace zbe
//
//#endif  // ZBE_ENTITIES_ADAPTORENTITIES_BOUNCEABLEENTITY_H_
