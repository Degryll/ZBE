/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DrawableEntity.h
 * @since 2016-11-23
 * @date 2016-11-23
 * @author Degryll
 * @brief Entity that can be seen as a drawable.
 */

#ifndef CORE_ENTITIES_ADAPTORENTITIES_DRAWABLEENTITY_H_
#define CORE_ENTITIES_ADAPTORENTITIES_DRAWABLEENTITY_H_

#include "ZBE/core/entities/adaptors/DrawableAdaptor.h"
#include "ZBE/core/entities/avatars/Drawable.h"

namespace zbe {

/** \brief Template that adapts an entity to a drawable.
 */
template <typedef T>
class DrawableEntity {
  public:
    DrawableEntity(T* entity) : entity(entity) {}

    void setAdaptor(DrawableAdaptor *adaptor) {a = adaptor;}

    Drawable getDrawable() {return (a->getDrawable(entity));}

  private:
    T* entity;
    DrawableAdaptor *a;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_DRAWABLEENTITY_H_
