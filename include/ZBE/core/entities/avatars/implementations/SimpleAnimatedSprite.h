/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedSprite.h
 * @since 2017-06-13
 * @date 2018-02-25
 * @author Batis Degryll Batis
 * @brief This define an avatar that can be drawn in any direction with different animations.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEANIMATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEANIMATEDSPRITE_H_

#include <cstdint>

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleStatedSprite.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction with different animations.
 */
class ZBEAPI SimpleAnimatedSprite : virtual public AnimatedSprite, public SimpleStatedSprite {

public:

  /** \brief Empty Constructor.
   */
  SimpleAnimatedSprite() : SimpleStatedSprite(), t(), contextTime(nullptr) {}

  /** \brief Parametrized Constructor.
   *  \param time Current time of the animated sprite.
   */
  SimpleAnimatedSprite(int64_t x, int64_t y, int64_t w, int64_t h, uint64_t graphics, double degrees, uint64_t state, uint64_t time, std::shared_ptr<ContextTime> contextTime)
    : SimpleStatedSprite(x, y, w, h, graphics, degrees, state), t(time), contextTime(contextTime) {}

  /** \brief Returns time.
   *  \return time.
   */
  uint64_t getTime() {return contextTime->getEndFrameTime() - t;}

  /** \brief Returns time.
   *  \return time.
   */
  void setTime(uint64_t time) {
    t = time;
  }

  /** \brief Returns time.
   *  \return time.
   */
  void setContextTime(std::shared_ptr<ContextTime> contextTime) {
    this->contextTime = contextTime;
  }

private:
  uint64_t t;    //!< Frame of the animation
  std::shared_ptr<ContextTime> contextTime;
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEANIMATEDSPRITE_H_
