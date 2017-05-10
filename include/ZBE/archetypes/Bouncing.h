/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bouncing.h
 * @since 2017-03-07
 * @date 2017-03-07
 * @author Batis Degryll Ludo
 * @brief Defines the interface of a class that stores normals for to bounce.
 */

#ifndef ZBE_ARCHETYPES_BOUNCING_H
#define ZBE_ARCHETYPES_BOUNCING_H

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/archetypes/Mobile.h"

namespace zbe {

template <unsigned s>
class Bouncing : virtual public Mobile<s> {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Bouncing() {}

  /** \brief Add a new normal.
   *  \param normal The normal to be added.
   */
  virtual void addNormal(const Vector<s>& normal) = 0;

  /** \brief Return a vector equals to the sum of the normals added.
   *  \return The accumulated normal.
   */
  virtual Vector<s> getNormalSum() = 0;

  /** \brief Return if any normal has been added.
   *  \return True if addNormal is called, false otherwise.
   */
  virtual bool hasNormals() = 0;

  /** \brief Sets the initial status. Ignore all previous calls to addNormal.
   */
  virtual void clearNormals() = 0;
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_BOUNCING_H
