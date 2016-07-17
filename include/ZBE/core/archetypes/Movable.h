/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movible.h
 * @since 2015-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that can be moved around the world.
 */

#ifndef CORE_ARCHETYPES_MOVIBLE_H_
#define CORE_ARCHETYPES_MOVIBLE_H_

#include "ZBE/core/archetypes/Positionable.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

/** \brief Define a class that can be moved around the world.
 */
template<unsigned s>
class Movable : public Positionable<s> {
  public:
    virtual ~Movable() {};

    /** \brief Set the velocity with which the entity moves
     *
     * \param velocity Vector<s> Given velocity
     * \return virtual void
     *
     */
    virtual void setVelocity(Vector<s> velocity) = 0;

    /** \brief Get the velocity with which the entity moves
     *
     * \return virtual Vector<s> The velocity.
     *
     */
    virtual Vector<s> getVelocity() const = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_MOVIBLE_H_
