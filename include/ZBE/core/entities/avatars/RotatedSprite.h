/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedSprite.h
 * @since 2017-04-05
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be drawn in any direction.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_ROTATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_ROTATEDSPRITE_H_

#include "ZBE/core/entities/avatars/SingleSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction.
 */
class RotatedSprite : virtual public SingleSprite {

public:

  using Base = SingleSprite; //!< Inheritance info.

  /** \brief Virtual Destructor.
   */
  virtual ~RotatedSprite() {};

  /** \brief Returns degrees.
   *  \return degrees.
   */
  virtual double getDegrees() = 0;

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_ROTATEDSPRITE_H_
