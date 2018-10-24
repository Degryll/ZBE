/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Mobile.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll
 * @brief Defines the interface of a class ZBEAPI with a position and a velocity.
 */

#ifndef ZBE_ARCHETYPES_MOBILE_H
#define ZBE_ARCHETYPES_MOBILE_H

#include <initializer_list>

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/archetypes/Position.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines the interface of a class ZBEAPI with a position and a velocity.
 */
template <unsigned s>
class ZBEAPI Mobile : virtual public Position<s> {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Mobile() {}

  /** \brief Sets velocity using a Vector.
   *  \param velocity Vector with the values of the velocity.
   *  \sa setVelocity, getVelocity
   */
  virtual void setVelocity(std::initializer_list<double> l) = 0;

  /** \brief Sets velocity using an initializer list.
   *  \param l Initializer list with the values of the velocity.
   *  \sa setVelocity, getVelocity
   */
  virtual void setVelocity(Vector<s> velocity) = 0;

  /** \brief Gets the velocity.
   *  \return Return a reference to the actual velocity in a vector.
   *  \sa setVelocity
   */
  virtual Vector<s>& getVelocity() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_MOBILE_H
