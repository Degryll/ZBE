/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BarCustomVector.h
 * @since 2017-10-15
 * @date 2017-10-15
 * @author Batis Degryll Ludo
 * @brief Zombienoid bar bounce vector.
 */

#ifndef ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONMAGNET_H_
#define ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONMAGNET_H_

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/entities/avatars/implementations/BasePositionable.h"

#include "entities/avatars/Magnet.h"

namespace zombienoid {

/** @brief Zombienoid bar bounce vector.
 */
template <unsigned s>
class BasePositionMagnet : virtual public Magnet<s>, virtual public zbe::Positionable<s>, public zbe::BasePositionable<s> {
public:

  BasePositionMagnet(zbe::Position<2> *position) : zbe::BasePositionable<s>(position) {}

  virtual ~BasePositionMagnet(){}
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONMAGNET_H_
