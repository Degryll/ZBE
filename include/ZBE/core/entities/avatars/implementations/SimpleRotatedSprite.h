/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedSprite.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an avatar that can be drawn in any direction.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEROTATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEROTATEDSPRITE_H_

#include "ZBE/core/entities/avatars/RotatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleSingleSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction.
 */
class SimpleRotatedSprite : virtual public RotatedSprite, virtual public SimpleSingleSprite {

public:

  /** \brief Parametrized Constructor.
   *  \param degrees Rotation degrees.
   */
  SimpleRotatedSprite(int64_t x = 0, int64_t y = 0, int64_t w = 0, int64_t h = 0, uint64_t graphics = 0, double degrees  = 0.0) :
  SimpleSingleSprite(x, y, w, h, graphics), degrees(degrees) {}

  /** \brief Returns degrees.
   *  \return degrees.
   */
  double getDegrees() {return degrees;}

private:
  double degrees; //!< rotation degrees

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEROTATEDSPRITE_H_
