/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Drawer.h
 * @since 2014-09-22
 * @date 2016-03-29
 * @author Ludo and Degryll
 * @brief Define the minimal functions of every Drawer.
 */

#ifndef CORE_DRAWERS_DRAWER_H_
#define CORE_DRAWERS_DRAWER_H_

#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Define the minimal functions of every Drawer.
 */
template<typename T>
class Drawer {
  public:
    /** \brief Virtual destructor.
     */
    virtual ~Drawer() {}

    /** \brief The function every punisher must have.
     *  \param entity The entity to be drawn.
     */
    virtual void apply(AvatarEntity<T> * entity) = 0;
};

}  // namespace zbe

#endif  // CORE_DRAWERS_DRAWER_H_
