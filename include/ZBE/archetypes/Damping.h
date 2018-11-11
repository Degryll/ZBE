/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Damping.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll
 * @brief Defines the interface of a class with a damping factor.
 */

#ifndef ZBE_ARCHETYPES_DAMPING_H
#define ZBE_ARCHETYPES_DAMPING_H

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines the interface of a class with a damping factor.
 */
class Damping {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Damping() {}

  /** \brief Sets the damping factor to factor.
   *  \param factor The damping factor.
   */
  virtual void setFactor(double factor) = 0;

  /** \brief Return the damping factor.
   *  \return The damping factor.
   */
  virtual double getFactor() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_DAMPING_H
