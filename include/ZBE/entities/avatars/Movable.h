/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movable.h
 * @since 2016-12-16
 * @date 2017-01-17
 * @author Degryll Ludo
 * @brief This define an avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_MOVABLE_H_
#define ZBE_ENTITIES_AVATARS_MOVABLE_H_

#include <initializer_list>

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/entities/avatars/Positionable.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be moved.
 */
template <unsigned s>
class Movable : virtual public Positionable<s> {
  public:
    using Base = Positionable<s>;//!< inheritance info

    /** \brief Virtual destructor.
     */
    virtual ~Movable() {}

    /** \brief Sets the velocity for this movable.
     * \param List of values for the velocity.
     */
    virtual void setVelocity(std::initializer_list<double> l) = 0;

    /** \brief Sets the velocity for this movable.
     * \param The velocity.
     */
    virtual void setVelocity(Vector<s> velocity) = 0;

    /** \brief Returns actual velocity of this movable.
     * \return Actual velocity.
     */
    virtual Vector<s>& getVelocity() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_MOVABLE_H_
