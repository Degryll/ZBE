/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoAvatars.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Avatars for ludo's proving grounds.
 */

#ifndef ZBE_MAIN_LUDO_ENTITIES_LUDOAVATARS
#define ZBE_MAIN_LUDO_ENTITIES_LUDOAVATARS

#include "ZBE/core/entities/avatars/SingleSprite.h"

namespace ludo {

/** \brief This define an avatar that can be drawn and has a rotation.
 */
struct SimpleRotatedSprite : public zbe::SingleSprite {
    using Base = SingleSprite;
    double angle; //!< rotation in degrees
};

} // namespace

#endif //ZBE_MAIN_LUDO_ENTITIES_LUDOAVATARS
