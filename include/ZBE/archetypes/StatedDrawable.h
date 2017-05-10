/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedDrawable.h
 * @since 2017-04-05
 * @date 2017-05-10
 * @author Degryll
 * @brief This define an entity that can be drawn in any direction with different sprites.
 */

#ifndef ZBE_ARCHETYPES_STATEDDRAWABLE_H_
#define ZBE_ARCHETYPES_STATEDDRAWABLE_H_

#include "ZBE/archetypes/RotatedDrawable.h"

namespace zbe {

/** \brief This define an entity that can be drawn in any direction with different sprites.
 */
class StatedDrawable : virtual public RotatedDrawable {
public:
  /** \brief Virtual destructor.
   */
  virtual ~StatedDrawable() {}

  /** \brief Gets the state of the sprite.
   *  \return The current state of the sprite.
   */
  virtual uint64_t getState() = 0;

  /** \brief Gets the number of states of the sprite.
   *  \return The total number of states.
   */
  virtual uint64_t getNumStates() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_STATEDDRAWABLE_H_
