/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleSprite.h
 * @since 2016-11-22
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be drawn.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_SINGLESPRITE_H_
#define ZBE_CORE_ENTITIES_AVATARS_SINGLESPRITE_H_

#include <cstdint>

namespace zbe {

/** \brief This define an avatar that can be drawn.
 */
class SingleSprite {

public:

  using Base = void; //!< Inheritance info.

  /** \brief Virtual Destructor.
   */
  virtual ~SingleSprite() {};

  /** \brief Returns x.
   *  \return x.
   */
  virtual int64_t getX() = 0;

  /** \brief Returns y.
   *  \return y.
   */
  virtual int64_t getY() = 0;

  /** \brief Returns w.
   *  \return w.
   */
  virtual int64_t getW() = 0;

  /** \brief Returns h.
   *  \return h.
   */
  virtual int64_t getH() = 0;

  /** \brief Returns graphics.
   *  \return graphics.
   */
  virtual uint64_t getGraphics() = 0;

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_SINGLESPRITE_H_
