/**
 * Copyright 2012 Batis Degryll Ludo
 * @file WideMobile.h
 * @since 2017-03-26
 * @date 2017-03-26
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class with a width.
 */

#ifndef ZBE_ARCHETYPES_WIDE_H
#define ZBE_ARCHETYPES_WIDE_H

namespace zbe {

class Wide {
  public:
    virtual ~Wide() {}

    virtual void setWidth(double width) = 0;
    virtual double getWidth() = 0;
};

}  // namespace

#endif //ZBE_ARCHETYPES_WIDE_H
