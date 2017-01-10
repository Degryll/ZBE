/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Drawable.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief This define an avatar that can be drawn.
 */

#ifndef CORE_ENTITIES_AVATARS_DRAWABLE_H_
#define CORE_ENTITIES_AVATARS_DRAWABLE_H_

namespace zbe {

/** \brief This define an avatar that can be drawn.
 */
struct Drawable {
    int x;      //!< X coordinate
    int y;      //!< Y coordinate
    unsigned w; //!< width
    unsigned h; //!< height
    int img;    //!< Image index
};

}  // namespace zbe

#endif  // CORE_ENTITIES_AVATARS_DRAWABLE_H_
