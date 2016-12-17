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

/** \brief Entity that can be seen as a drawable.
 */
class DrawableEntity {
  public:

    virtual std::shared_ptr<Drawable> getDrawable() = 0;

};

/** \brief Entity that can be seen as a drawable using an adaptor.
 */
template <typename T>
class DrawableEntityAdapted : public Drawable {
  public:
    DrawableEntityAdapted(T* entity) : entity(entity) {}

    void setAdaptor(DrawableAdaptor *adaptor) {a = adaptor;}

    std::shared_ptr<Drawable> getDrawable() {return (a->getDrawable(entity));}

  private:
    T* entity;
    DrawableAdaptor *a;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ADAPTORENTITIES_DRAWABLEENTITY_H_
