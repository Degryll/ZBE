/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableAdaptor.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Template that adapts an entity to a movable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_MOVABLEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_MOVABLEADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Movable.h"

namespace zbe {

/** \brief Template that adapts an entity to a movable.
 */
template <typename T, usigned s>
class MovableAdaptor {
  public:
    virtual std::shared_ptr< Movable<s> > getMovable(T* entity) = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_MOVABLEADAPTOR_H_
