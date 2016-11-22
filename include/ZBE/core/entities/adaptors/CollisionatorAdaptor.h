/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionatorAdaptor.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief Template that adapts an entity to a collisionator.
 */

#ifndef CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_
#define CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_

// Cambiar esto cuando esté lista
//#include "ZBE/core/entities/avatars/Collisioner.h"
class Collisionator {};

namespace zbe {

/** \brief Template that adapts an entity to a drawable.
 */
template <typedef T>
class CollisionatorAdaptor {
  public:
    virtual Collisionator getCollisionator(T entity) = 0;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORS_COLLISIONATORADAPTOR_H_
