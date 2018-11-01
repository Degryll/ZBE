/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Position.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll
 * @brief Defines the interface of a class ZBEAPI with a position.
 */

#ifndef ZBE_ARCHETYPES_POSITION_H
#define ZBE_ARCHETYPES_POSITION_H

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines the interface of a class ZBEAPI with a position.
 */
template <unsigned s>
class Position {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Position() {}

  /** \brief Sets the position using a Point.
   *  \param position Position with the values of the position.
   *  \sa setPosition, getPosition
   */
  virtual void setPosition(std::initializer_list<double> l) = 0;

  /** \brief Sets position using an initializer list.
   *  \param l Initializer list with the values of the position.
   *  \sa setPosition, getPosition
   */
  virtual void setPosition(Point<s> position) = 0;

  /** \brief Gets the position.
   *  \return Return a reference to the actual position in a point.
   *  \sa setPosition
   */
  virtual Point<s>& getPosition() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_POSITION_H
