/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSprite.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief This define an avatar that can be drawn.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_

namespace zbe {

/** \brief This define an avatar that can be drawn.
 */
struct SimpleSprite {
    using Base = void;
    int x;      //!< X coordinate
    int y;      //!< Y coordinate
    unsigned w; //!< width
    unsigned h; //!< height
    int graphics;    //!< Image index
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_
