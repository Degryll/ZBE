/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedSprite.h
 * @since 2017-04-05
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be drawn in any direction with different animations.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_ANIMATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_ANIMATEDSPRITE_H_

#include <cstdint>
#include "ZBE/core/entities/avatars/StatedSprite.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction with different animations.
 */
class  AnimatedSprite : virtual public StatedSprite {
public:
  using Base = StatedSprite; //!< Inheritance info.

  /** \brief Virtual Destructor.
   */
  virtual ~AnimatedSprite() {};

  /** \brief Returns time.
   *  \return time.
   */
  virtual uint64_t getTime() = 0;

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_ANIMATEDSPRITE_H_
