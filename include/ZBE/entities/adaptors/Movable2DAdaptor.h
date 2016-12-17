/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movable2DAdaptor.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Template that adapts an entity to a movable 2D.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_MOVABLE2DADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_MOVABLE2DADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Movable2D.h"

namespace zbe {

/** \brief Template that adapts an entity to a movable 2D.
 */
template <typename T>
class Movable2DAdaptor {
  public:
    virtual std::shared_ptr<Movable2D> getMovable2D(T* entity) = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_MOVABLE2DADAPTOR_H_
