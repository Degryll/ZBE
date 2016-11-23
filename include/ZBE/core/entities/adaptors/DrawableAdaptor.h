/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DrawableAdaptor.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef CORE_ENTITIES_ADAPTORS_DRAWABLEADAPTOR_H_
#define CORE_ENTITIES_ADAPTORS_DRAWABLEADAPTOR_H_

#include "ZBE/core/entities/avatars/Drawable.h"

namespace zbe {

/** \brief Template that adapts an entity to a drawable.
 */
template <typename T>
class DrawableAdaptor {
  public:
    virtual Drawable* getDrawable(T entity) = 0;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORS_DRAWABLEADAPTOR_H_
