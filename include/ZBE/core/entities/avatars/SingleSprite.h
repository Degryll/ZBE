/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSprite.h
 * @since 2016-11-22
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an avatar that can be drawn.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_

namespace zbe {

/** \brief This define an avatar that can be drawn.
 */
struct SingleSprite {
    using Base = void;
    int64_t x = 0; //!< X coordinate
    int64_t y = 0; //!< Y coordinate
    int64_t w = 0; //!< width
    int64_t h = 0; //!< height
    uint64_t graphics = 0;    //!< Image index
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_SIMPLESPRITE_H_
