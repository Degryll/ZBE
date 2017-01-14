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
class Drawable {
  public:
    virtual ~Drawable() {}

    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual unsigned getW() = 0;
    virtual unsigned getH() = 0;
    virtual int getGraphics() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_DRAWABLE_H_
