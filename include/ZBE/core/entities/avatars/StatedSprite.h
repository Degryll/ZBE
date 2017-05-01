/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSprite.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an avatar that can be drawn in any direction with different sprites.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_STATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_STATEDSPRITE_H_

#include "ZBE/core/entities/avatars/RotatedSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction with different sprites.
 */
struct StatedSprite : virtual public RotatedSprite {
    using Base = RotatedSprite;
    uint64_t state = 0;   //!< state
    uint64_t nstates = 0; //!< Number of states
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_STATEDSPRITE_H_
