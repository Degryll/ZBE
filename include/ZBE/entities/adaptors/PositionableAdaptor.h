/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MovableAdaptor.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Template that adapts an entity to a positionable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_POSITIONABLEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_POSITIONABLEADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Positionable.h"

namespace zbe {

/** \brief Template that adapts an entity to a positionable.
 */
template <typename T, unsigned s>
class PositionableAdaptor {
  public:
    virtual std::shared_ptr< Positionable<s> > getPositionable(T* entity) = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_POSITIONABLEADAPTOR_H_
