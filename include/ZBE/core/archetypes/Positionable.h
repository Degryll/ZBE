/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Positionable.h
 * @since 2015-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that has a position in the world.
 */

#ifndef CORE_ARCHETYPES_POSITIONABLE_H_
#define CORE_ARCHETYPES_POSITIONABLE_H_

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

template <unsigned s>
class Positionable {
  public:
    virtual ~Positionable() {}

    /** \brief Gets the current position of the entity
     *
     * \return virtual Point<s> Current position
     *
     */
    virtual Point<s> getPosition() const = 0;

    /** \brief Sets the position of the entity.
     *
     * \param position Point<s> Given position
     * \return virtual void
     *
     */
    virtual void setPosition(Point<s> position) = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_POSITIONABLE_H_
