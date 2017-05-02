/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedSprite.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an avatar that can be drawn in any direction with different animations.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_ANIMATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_ANIMATEDSPRITE_H_

#include "ZBE/core/entities/avatars/StatedSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction with different animations.
 */
struct AnimatedSprite : virtual public StatedSprite {
    using Base = StatedSprite;
    uint64_t frame = 0;    //!< Frame of the animation
    const uint64_t *nframes = nullptr; //!< Number of frames per animation
    const int64_t  *width   = nullptr; //!< Pixel width of the animation
    const int64_t  *height  = nullptr; //!< Pixel height of the animation
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_ANIMATEDSPRITE_H_
