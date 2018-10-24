/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimplePosition.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll
 * @brief Simple implementation of the Position interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION_H

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"

#include "ZBE/archetypes/Position.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Simple implementation of the Position interface.
 */
template <unsigned s>
class ZBEAPI SimplePosition : virtual public Position<s> {
public:
  /** \brief Empty constructor. Position is set to 0.
   */
  SimplePosition() : p() {}

  /** \brief Position is set by an initilizer list.
   */
  SimplePosition(std::initializer_list<double> l) : p(l) {}

  /** \brief Position is set by a Point.
   */
  SimplePosition(Point<s> position) : p(position) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimplePosition() {}

  /** \brief Sets the position using a Point.
   *  \param position Position with the values of the position.
   *  \sa setPosition, getPosition
   */
  void setPosition(Point<s> position) {p = position;}

  /** \brief Sets position using an initializer list.
   *  \param l Initializer list with the values of the position.
   *  \sa setPosition, getPosition
   */
  void setPosition(std::initializer_list<double> l) {p = l;}

  /** \brief Gets the position.
   *  \return Return a reference to the actual position in a point.
   *  \sa setPosition
   */
  Point<s>& getPosition() {return (p);}

private:
  Point<s> p;
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPOSITION_H
