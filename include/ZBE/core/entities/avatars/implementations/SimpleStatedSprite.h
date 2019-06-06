/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedSprite.h
 * @since 2017-04-05
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be drawn in any direction with different sprites.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESTATEDSPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESTATEDSPRITE_H_

#include <cstdint>

#include "ZBE/core/entities/avatars/StatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleRotatedSprite.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be drawn in any direction with different sprites.
 */
class SimpleStatedSprite : virtual public StatedSprite, public SimpleRotatedSprite {
public:
  
  /** \brief Empty Constructor.
   */
  SimpleStatedSprite() :  SimpleRotatedSprite(), state() {}

  /** \brief Parametrized Constructor.
   *  \param x x coord
   *  \param y y coord
   *  \param w width
   *  \param h height
   *  \param graphics graphics id
   *  \param degrees degrees
   *  \param state state
   */
  SimpleStatedSprite(int64_t x, int64_t y, int64_t w, int64_t h, uint64_t graphics, double degrees, uint64_t state) :
  SimpleRotatedSprite(x, y, w, h, graphics, degrees), state(state) {}

  /** \brief Returns state.
   *  \return state.
   */
  int64_t getState() {return state;}

  /** \brief Sets state.
   *  \param state value for State attribute
   */
  virtual void setState(int64_t state) {this->state = state;}

private:
  int64_t state;   //!< state

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLESTATEDSPRITE_H_
