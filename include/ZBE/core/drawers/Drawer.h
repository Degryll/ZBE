/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Drawer.h
 * @since 2014-09-22
 * @date 2014-09-27
 * @author Ludo and Degryll
 * @brief Define the minimal functions of every Drawer.
 */

#ifndef CORE_DRAWERS_DRAWER_H_
#define CORE_DRAWERS_DRAWER_H_

namespace zbe {

class Drawer {
  public:
    virtual ~Drawer() {}

    virtual void draw() = 0;
};

}  // namespace zbe

#endif  // CORE_DRAWERS_DRAWER_H_
