/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CustomVector.h
 * @since 2017-10-15
 * @date 2017-10-15
 * @author Batis Degryll Ludo
 * @brief Interface capable of give the position of a magnet.
 */

#ifndef ZOMBIENOID_ENTITIES_AVATARS_MAGNET_H_
#define ZOMBIENOID_ENTITIES_AVATARS_MAGNET_H_

#include "ZBE/entities/avatars/Positionable.h"

namespace zombienoid {

/** @brief Interface capable of give the position of a magnet.
 */
template <unsigned s>
class Magnet : virtual public zbe::Positionable<s> {
public:
  using Base = void;
  
  virtual ~Magnet() {}
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_ENTITIES_AVATARS_MAGNET_H_
