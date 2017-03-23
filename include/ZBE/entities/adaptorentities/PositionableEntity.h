///**
// * Copyright 2012 Batis Degryll Ludo
// * @file PositionableEntity.h
// * @since 2016-12-16
// * @date 2016-12-18
// * @author Degryll
// * @brief Entity that can be seen as a positionable.
// */
//
//#ifndef ZBE_ENTITIES_ADAPTORENTITIES_POSITIONABLEENTITY_H_
//#define ZBE_ENTITIES_ADAPTORENTITIES_POSITIONABLEENTITY_H_
//
//#include <memory>
//
//#include "ZBE/entities/adaptors/PositionableAdaptor.h"
//#include "ZBE/entities/avatars/Positionable.h"
//
//namespace zbe {
//
///** \brief Entity that can be seen as a movable.
// */
//template <unsigned s>
//class PositionableEntity {
//  public:
//    virtual ~PositionableEntity() {}
//
//    virtual std::shared_ptr< Positionable<s> > getPositionable() = 0;
//
//};
//
///** \brief Entity that can be seen as a movable using an adaptor.
// */
//template <typename T, unsigned s>
//class PositionableEntityAdapted : public PositionableEntity<s> {
//  public:
//    PositionableEntityAdapted(const PositionableEntityAdapted&) = delete;
//    void operator=(const PositionableEntityAdapted&) = delete;
//
//    PositionableEntityAdapted(T* entity) : entity(entity), a(nullptr) {}
//
//    virtual ~PositionableEntityAdapted() {}
//
//    void setPositionableAdaptor(PositionableAdaptor<T, s> *adaptor) {a = adaptor;}
//
//    std::shared_ptr< Positionable<s> > getPositionable() {return (a->getPositionable(entity));}
//
//  private:
//    T* entity;
//    PositionableAdaptor<T, s> *a;
//};
//
//}  // namespace zbe
//
//#endif  // ZBE_ENTITIES_ADAPTORENTITIES_POSITIONABLEENTITY_H_
