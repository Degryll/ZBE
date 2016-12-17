/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BounceableAdaptor.h
 * @since 2016-12-17
 * @date 2016-12-17
 * @author Batis
 * @brief Template that adapts an entity to a bounceable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BOUNCEABLEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BOUNCEABLEADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Bounceable.h"

namespace zbe {

/** \brief Template that adapts an entity to a movable 2D.
 */
template <typename T>
class BounceableAdaptor {
  public:
    virtual std::shared_ptr<Bounceable> getBounceable(T* entity) = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BOUNCEABLEADAPTOR_H_
