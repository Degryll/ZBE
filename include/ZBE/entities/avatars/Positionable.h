/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Positionable.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Defines an avatar that can be positioned.
 */

#ifndef ZBE_ENTITIES_AVATARS_POSITIONABLE_H_
#define ZBE_ENTITIES_AVATARS_POSITIONABLE_H_

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines an avatar that can be positioned.
 */
template <unsigned s>
class Positionable {
  public:
    using Base = void;//!< inheritance info

    /** \brief Virtual destructor.
     */
    virtual ~Positionable() {}

    /** \brief Sets the position for this Positionable.
     * \param List of values for the position..
     */
    virtual void setPosition(std::initializer_list<double> l) = 0;

    /** \brief Sets the position for this Positionable.
     * \param The position.
     */
    virtual void setPosition(Point<s> position) = 0;

    /** \brief Retunrs the position of this Positionable.
     * \return The position.
     */
    virtual Point<s>& getPosition() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_POSITIONABLE_H_
