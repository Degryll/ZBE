/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSprite.h
 * @since 2017-04-05
 * @date 2018-02-25
 * @author Degryll
 * @brief This define an avatar that can be drawn in any direction with different sprites.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_STATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_STATEDSPRITE_H_

#include <cstdint>

#include "ZBE/core/entities/avatars/RotatedSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction with different sprites.
 */
class StatedSprite : virtual public RotatedSprite {

public:

  using Base = RotatedSprite; //!< Inheritance info.

  /** \brief Virtual Destructor.
   */
  virtual ~StatedSprite() {};

  /** \brief Returns state.
   *  \return state.
   */
  virtual int64_t getState() = 0;

  /** \brief Sets state.
   *  \param state
   */
  virtual void setState(int64_t state) = 0;

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_STATEDSPRITE_H_
