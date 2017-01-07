/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableEntity.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Entity that can be seen as a movable.
 */

#ifndef ZBE_ENTITIES_ADAPTORENTITIES_MOVABLEENTITY_H_
#define ZBE_ENTITIES_ADAPTORENTITIES_MOVABLEENTITY_H_

#include <memory>

#include "ZBE/entities/adaptors/MovableAdaptor.h"
#include "ZBE/entities/avatars/Movable.h"

namespace zbe {

/** \brief Entity that can be seen as a movable.
 */
template <unsigned s>
class MovableEntity {
  public:

    virtual std::shared_ptr< Movable<s> > getMovable() = 0;

};

/** \brief Entity that can be seen as a movable using an adaptor.
 */
template <typename T, unsigned s>
class MovableEntityAdapted : public MovableEntity {
  public:
    MovableEntityAdapted(T* entity) : entity(entity) {}

    void setAdaptor(MovableAdaptor<s> *adaptor) {a = adaptor;}

    std::shared_ptr< Movable<s> > getMovable() {return (a->getMovable(entity));}

  private:
    T* entity;
    MovableAdaptor<s> *a;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORENTITIES_MOVABLEENTITY_H_
