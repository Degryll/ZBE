/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedDrawable.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an entity that can be drawn in any direction.
 */

#ifndef ZBE_ARCHETYPES_ROTATEDDRAWABLE_H_
#define ZBE_ARCHETYPES_ROTATEDDRAWABLE_H_

#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief This define an entity that can be drawn in any direction.
 */
class RotatedDrawable : virtual public Drawable {
  public:
    virtual ~AnimatedDrawable() {}

    virtual double getDegrees() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_ROTATEDDRAWABLE_H_
