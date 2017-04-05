/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedDrawable.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an entity that can be drawn in any direction with different animations.
 */

#ifndef ZBE_ARCHETYPES_ANIMATEDDRAWABLE_H_
#define ZBE_ARCHETYPES_ANIMATEDDRAWABLE_H_

#include "ZBE/archetypes/StatedDrawable.h"

namespace zbe {

/** \brief This define an entity that can be drawn in any direction with different animations.
 */
class AnimatedDrawable : virtual public StatedDrawable {
  public:
    virtual ~AnimatedDrawable() {}

    virtual uint64_t getFrame() = 0;
    virtual uint64_t getNumFrames(uint64_t state) = 0;
    virtual int64_t getW(uint64_t state) = 0;
    virtual int64_t getH(uint64_t state) = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_ANIMATEDDRAWABLE_H_
