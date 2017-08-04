/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSprite.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an avatar that can be drawn in any direction with different sprites.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESTATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESTATEDSPRITE_H_

#include "ZBE/core/entities/avatars/StatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleRotatedSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction with different sprites.
 */
class SimpleStatedSprite : virtual public StatedSprite, public SimpleRotatedSprite {

public:

  /** \brief Parametrized Constructor.
   *  \param state Current state of the stated sprite.
   */
  SimpleStatedSprite(int64_t x, int64_t y, int64_t w, int64_t h, uint64_t graphics, double degrees, uint64_t state) :
  SimpleRotatedSprite(x, y, w, h, graphics, degrees), state(state) {}

  /** \brief Returns state.
   *  \return state.
   */
  uint64_t getState() {return state;}

private:
  uint64_t state;   //!< state

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESTATEDSPRITE_H_
