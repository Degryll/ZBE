/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedSprite.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an avatar that can be drawn in any direction.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_ROTATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_ROTATEDSPRITE_H_

#include "ZBE/core/entities/avatars/SimpleSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction.
 */
struct RotatedSprite : virtual public SimpleSprite {
    using Base = SimpleSprite;
    double degrees; //!< rotation degrees
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_ROTATEDSPRITE_H_
