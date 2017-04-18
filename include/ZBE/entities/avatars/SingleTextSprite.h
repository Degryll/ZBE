/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleTextSprite.h
 * @since 2017-04-12
 * @date 2017-04-12
 * @author Batis
 * @brief This define an avatar that can be drawn as text.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_SIMPLETEXTSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_SIMPLETEXTSPRITE_H_

#include "ZBE/core/entities/avatars/SingleSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn as text.
 */
struct SingleTextSprite : virtual public SingleSprite {
    using Base = SingleSprite;
    const char* text = "";
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_SIMPLETEXTSPRITE_H_
