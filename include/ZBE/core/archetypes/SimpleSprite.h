/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSprite.h
 * @since 2014-09-27
 * @date 2014-09-27
 * @author Ludo and Degryll
 * @brief Define a class that can be draw as a simple sprite.
 */

#ifndef CORE_ARCHETYPES_SIMPLESPRITE_H_
#define CORE_ARCHETYPES_SIMPLESPRITE_H_

namespace zbe {

class SimpleSprite {
  public:
    virtual ~SimpleSprite() {}

    virtual int getImage() = 0;
    virtual unsigned int getLeftX() = 0;
    virtual unsigned int getTopY() = 0;
    virtual unsigned int getWidth() = 0;
    virtual unsigned int getHeight() = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_SIMPLESPRITE_H_
