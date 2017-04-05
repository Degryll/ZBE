/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Drawable.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief This define an entity that can be drawn.
 */

#ifndef ZBE_ARCHETYPES_DRAWABLE_H_
#define ZBE_ARCHETYPES_DRAWABLE_H_

namespace zbe {

/** \brief This define an entity that can be drawn.
 */
class RotatedDrawable {
  public:
    virtual ~AnimatedDrawable() {}

    virtual int64_t getX() = 0;
    virtual int64_t getY() = 0;
    virtual int64_t getW() = 0;
    virtual int64_t getH() = 0;
    virtual uint64_t getGraphics() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_DRAWABLE_H_
