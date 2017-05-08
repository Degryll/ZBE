/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleMobile.h
 * @since 2016-12-16
 * @date 2017-05-08
 * @author Degryll Ludo
 * @brief Simple implementation of the Mobile<s> interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE_H

#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/implementations/SimplePosition.h"

namespace zbe {

/** \brief Simple implementation of the Mobile<s> interface.
 */
template <unsigned s>
class SimpleMobile : virtual public Mobile<s>, public SimplePosition<s> {
public:
  /** \brief Empty constructor. Position and velocity are set to 0.
   */
  SimpleMobile() : SimplePosition<s>(), v() {}

  /** \brief Position is set by an initilizer list, velocity is set to 0.
   */
  SimpleMobile(std::initializer_list<double> position) : SimplePosition<s>(position), v() {}

  /** \brief Position is set by a Point, velocity will be set to 0.
   */
  SimpleMobile(Point<s> position) : SimplePosition<s>(position), v() {}

  /** \brief Position is set to 0, velocity is set by a vector.
   */
  SimpleMobile(Vector<s> velocity) : SimplePosition<s>(), v(velocity) {}

  /** \brief Position and velocity are set by an initializer list.
   */
  SimpleMobile(std::initializer_list<double> position, std::initializer_list<double> velocity) : SimplePosition<s>(position), v(velocity) {}

  /** \brief Position is set by a Point, velocity is set by an initializer list.
   */
  SimpleMobile(Point<s> position, std::initializer_list<double> velocity) : SimplePosition<s>(position), v(velocity) {}

  /** \brief Position is set by a Point, velocity is set by a Vector.
   */
  SimpleMobile(Point<s> position, Vector<s> velocity) : SimplePosition<s>(position), v(velocity) {}

  /** \brief Position is set by an initializer list, velocity is set by a Vector.
   */
  SimpleMobile(std::initializer_list<double> position, Vector<s> velocity) : SimplePosition<s>(position), v(velocity) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleMobile() {}

  /** \brief Sets velocity using a Vector.
   *  \param velocity Vector with the values of the velocity.
   *  \sa setVelocity, getVelocity
   */
  void setVelocity(Vector<s> velocity) {v = velocity;}

  /** \brief Sets velocity using an initializer list.
   *  \param l Initializer list with the values of the velocity.
   *  \sa setVelocity, getVelocity
   */
  void setVelocity(std::initializer_list<double> l) {v = l;}

  /** \brief Gets the velocity.
   *  \return Return a reference to the actual velocity in a vector.
   *  \sa setVelocity
   */
  Vector<s>& getVelocity() {return (v);}

private:
  Vector<s> v;
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE_H
