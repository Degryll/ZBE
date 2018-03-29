/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleBouncing.h
 * @since 2017-03-07
 * @date 2018-02-22
 * @author Batis Degryll Ludo
 * @brief Implements the interface of a class that stores normals to bounce.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCING_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCING_H

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/archetypes/Bouncing.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"

namespace zbe {

/** \brief Implements the interface of a class that stores normals to bounce.
 */
template <unsigned s>
class SimpleBouncing : virtual public Bouncing<s>, public SimpleMobile<s> {
public:
  /** \brief Empty constructor. Initially no normal has been added.
   */
  SimpleBouncing()  : SimpleMobile<s>(), n(Vector<s>::zeros()), hasN(false) {}

  /** \brief Constructor with position data as an initializer list. Velocity will be 0.
   */
  SimpleBouncing(std::initializer_list<double> position)  : SimpleMobile<s>(position), n(Vector<s>::zeros()), hasN(false) {}

  /** \brief Constructor with position data as a Point. Velocity will be 0.
   */
  SimpleBouncing(Point<s> position) : SimpleMobile<s>(position), n(Vector<s>::zeros()), hasN(false) {}

  /** \brief Constructor with velocity data as a Vector. Position will be 0.
   */
  SimpleBouncing(Vector<s> velocity) : SimpleMobile<s>(velocity), n(Vector<s>::zeros()), hasN(false) {}

  /** \brief Constructor with position and velocity data as an initializer list.
   */
  SimpleBouncing(std::initializer_list<double> position, std::initializer_list<double> velocity) : SimpleMobile<s>(position, velocity), n(Vector<s>::zeros()), hasN(false) {}

  /** \brief Constructor with position data as a Point, and velocity data as an initializer list.
   */
  SimpleBouncing(Point<s> position, std::initializer_list<double> velocity) : SimpleMobile<s>(position, velocity), n(Vector<s>::zeros()), hasN(false) {}

  /** \brief Constructor with position data as a Point, and velocity data as a Vector.
   */
  SimpleBouncing(Point<s> position, Vector<s> velocity) : SimpleMobile<s>(position, velocity), n(Vector<s>::zeros()), hasN(false) {}

  /** \brief Constructor with position data as an initializer list, and velocity data as a Vector.
   */
  SimpleBouncing(std::initializer_list<double> position, Vector<s> velocity) : SimpleMobile<s>(position, velocity), n(Vector<s>::zeros()), hasN(false) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleBouncing() {}

  /** \brief Add a new normal.
   *  \param normal The normal to be added.
   */
  void addNormal(const Vector<s>& normal) {n += normal; hasN=true;}

  /** \brief Return a vector equals to the sum of the normals added.
   *  \return The accumulated normal.
   */
  Vector<s> getNormalSum() {return (n);}

  /** \brief Return if any normal has been added.
   *  \return True if addNormal is called, false otherwise.
   */
  bool hasNormals() {return (hasN);}

  /** \brief Sets the initial status. Ignore all previous calls to addNormal.
   */
  void clearNormals() {n.setZeros(); hasN=false;}

private:
  Vector<s> n;
  bool hasN;
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCING_H
