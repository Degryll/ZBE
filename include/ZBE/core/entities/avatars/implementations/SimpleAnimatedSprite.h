/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedSprite.h
 * @since 2017-06-13
 * @date 2017-06-13
 * @author Batis
 * @brief This define an avatar that can be drawn in any direction with different animations.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEANIMATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEANIMATEDSPRITE_H_

#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleStatedSprite.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction with different animations.
 */
class SimpleAnimatedSprite : virtual public AnimatedSprite, virtual public SimpleStatedSprite {

public:

  /** \brief Parametrized Constructor.
   *  \param time Current time of the animated sprite.
   */
  SimpleAnimatedSprite(int64_t x = 0, int64_t y = 0, int64_t w = 0, int64_t h = 0, uint64_t graphics = 0, double degrees  = 0.0, uint64_t state = 0, uint64_t time = 0) :
  SimpleStatedSprite(x, y, w, h, graphics, degrees, state), time(time) {}

  /** \brief Returns time.
   *  \return time.
   */
  uint64_t getTime() {return time;}

private:
  uint64_t time;    //!< Frame of the animation

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEANIMATEDSPRITE_H_
