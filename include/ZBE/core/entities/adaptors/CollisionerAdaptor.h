/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionerAdaptor.h
 * @since 2016-11-22
 * @date 2016-11-23
 * @author Degryll
 * @brief Template that adapts an entity to a collisioner.
 */

#ifndef CORE_ENTITIES_ADAPTORS_COLLISIONERADAPTOR_H_
#define CORE_ENTITIES_ADAPTORS_COLLISIONERADAPTOR_H_

#include <memory>

#include "ZBE/core/entities/avatars/Collisioner.h"

namespace zbe {

/** \brief Template that adapts an entity to a drawable.
 */
template <typename T>
class CollisionerAdaptor {
  public:
    virtual std::shared_ptr<Collisioner> getCollisioner(T* entity) = 0;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORS_COLLISIONERADAPTOR_H_
