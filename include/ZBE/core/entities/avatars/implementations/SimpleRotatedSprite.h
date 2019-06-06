/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedSprite.h
 * @since 2017-04-05
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be drawn in any direction.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEROTATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEROTATEDSPRITE_H_

#include <cstdint>

#include "ZBE/core/entities/avatars/RotatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleSingleSprite.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction.
 */
class SimpleRotatedSprite : virtual public RotatedSprite, public SimpleSingleSprite {
public:
  /** \brief Empty Constructor.
   */
  SimpleRotatedSprite() : SimpleSingleSprite(), degrees() {}

  /** \brief Parametrized Constructor.
   *  \param degrees Rotation degrees.
   */
  SimpleRotatedSprite(int64_t x, int64_t y, int64_t w, int64_t h, uint64_t graphics, double degrees) :
  SimpleSingleSprite(x, y, w, h, graphics), degrees(degrees) {}

  /** \brief Returns the rotation angle in degrees.
   *  \return degrees.
   */
  double getDegrees() {return degrees;}

  /** \brief Sets the degrees.
   *  \param degrees rotation angle in degrees
   */
  void setDegrees(double degrees) {this->degrees = degrees;}

private:
  double degrees; //!< rotation degrees

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEROTATEDSPRITE_H_
