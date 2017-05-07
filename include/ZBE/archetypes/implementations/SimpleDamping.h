/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleDamping.h
 * @since 2016-12-16
 * @date 2017-05-07
 * @author Degryll
 * @brief Simple implementation of the Damping interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDAMPING_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDAMPING_H

#include "ZBE/archetypes/Damping.h"

namespace zbe {

/** \brief Simple implementation of the Damping interface.
 */
class SimpleDamping : virtual public Damping {
public:
  /** \brief Empty constructor. Set the damping factor to 1.0.
   */
  SimpleDamping() : df(1.0) {}

  /** \brief Parametrized constructor. Sets the damping factor to factor.
   *  \param factor The damping factor.
   */
  SimpleDamping(const double factor) : df(factor) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleDamping() {}

  /** \brief Sets the damping factor to factor.
   *  \param factor The damping factor.
   */
  void setFactor(const double factor) {df = factor;}

  /** \brief Return the damping factor.
   *  \return The damping factor.
   */
  double getFactor() {return (df);}

private:
  double df;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDAMPING_H
