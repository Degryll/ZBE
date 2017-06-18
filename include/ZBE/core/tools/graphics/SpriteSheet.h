/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SpriteSheet.h
 * @since 2017-06-14
 * @date 2017-06-14
 * @author Degryll Ludo Batis
 * @brief Interface capable of generate a sprite from a given entity.
 */

#ifndef ZBE_CORE_TOOLS_GRAPHICS_SPRITESHEET_H_
#define ZBE_CORE_TOOLS_GRAPHICS_SPRITESHEET_H_

#include <stdint.h>

#include "ZBE/core/tools/graphics/Sprite.h"
#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Interface capable of generate a sprite from a given entity.
 */
template<typename T>
class SpriteSheet {

    virtual ~SpriteSheet(){} //!< Virtual destrutor.

    /** \brief Generate a sprite from a given entity.
     *  \return generated sprite
     **/
    virtual Sprite generateSprite(AvatarEntity<T>* e) = 0;

};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_GRAPHICS_SPRITESHEET_H_
