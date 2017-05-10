/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedDrawable.h
 * @since 2017-04-05
 * @date 2017-04-05
 * @author Degryll
 * @brief This define an entity that can be drawn in any direction with different animations.
 */

#ifndef ZBE_ARCHETYPES_ANIMATEDDRAWABLE_H_
#define ZBE_ARCHETYPES_ANIMATEDDRAWABLE_H_

#include <cstdint>

#include "ZBE/archetypes/StatedDrawable.h"

namespace zbe {

/** \brief This define an entity that can be drawn in any direction with different animations.
 */
class AnimatedDrawable : virtual public StatedDrawable {
public:
  /** \brief Virtual destructor.
   */
  virtual ~AnimatedDrawable() {}

  /** \brief Gets the frame index.
   *  \return The frame index.
   *  \sa getNumFrames
   */
  virtual uint64_t getFrame() = 0;

  /** \brief Gets the total number of frames of each animation.
   *  \param state State of the sprite
   *  \return The number of frames of the animation at the given state.
   *  \sa getFrame
   */
  virtual uint64_t getNumFrames(uint64_t state) = 0;

  /** \brief Gets the global width of the animation at the given state.
   *  \param state State of the sprite
   *  \return The global width of the animation at the given state.
   *  \sa getGH
   */
  virtual int64_t getGW(uint64_t state) = 0;

  /** \brief Gets the global height of the animation at the given state.
   *  \param state State of the sprite
   *  \return The global height of the animation at the given state.
   *  \sa getGH
   */
  virtual int64_t getGH(uint64_t state) = 0;

  /** \brief Gets the widths of the different states.
   *  \return An array of widths.
   *  \sa getGHArray, getFArray
   */
  virtual const int64_t* getWArray() = 0;

  /** \brief Gets the heights of the different states.
   *  \return An array of heights.
   *  \sa getGWArray, getFArray
   */
  virtual const int64_t* getHArray() = 0;

  /** \brief Gets the number of frames of the different states.
   *  \return An array of frames.
   *  \sa getGWArray, getGHArray
   */
  virtual const uint64_t* getFArray() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_ANIMATEDDRAWABLE_H_
