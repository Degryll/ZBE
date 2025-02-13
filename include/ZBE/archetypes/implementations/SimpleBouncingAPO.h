/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleBouncingAPO.h
 * @since 2017-03-07
 * @date 2018-02-22
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the Bouncing Mobile active physical object interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGAPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGAPO_H

#include <cstdint>
#include <initializer_list>

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/archetypes/BouncingAPO.h"
#include "ZBE/archetypes/implementations/SimpleBouncing.h"
#include "ZBE/archetypes/implementations/SimpleActivePhysicalObject.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Simple implementation of the Bouncing Mobile active physical object interface.
 */
template <unsigned s>
class SimpleBouncingAPO : virtual public BouncingAPO<s>, public SimpleBouncing<s>, public SimpleActivePhysicalObject {
public:
  /** \brief Constructs a BouncingAPO with position and velocity set to 0.
   */
  SimpleBouncingAPO(uint64_t actuatorsList, uint64_t collisionablesList) : SimpleBouncing<s>(), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as an initializer list. Velocity will be 0.
   */
  SimpleBouncingAPO(std::initializer_list<double> position, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleBouncing<s>(position), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point. Velocity will be 0.
   */
  SimpleBouncingAPO(Point<s> position, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleBouncing<s>(position), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with velocity data as a Vector. Position will be 0.
   */
  SimpleBouncingAPO(Vector<s> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleBouncing<s>(velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position and velocity data as an initializer list.
   */
  SimpleBouncingAPO(std::initializer_list<double> position, std::initializer_list<double> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleBouncing<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point, and velocity data as an initializer list.
   */
  SimpleBouncingAPO(Point<s> position, std::initializer_list<double> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleBouncing<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point, and velocity data as a Vector.
   */
  SimpleBouncingAPO(Point<s> position, Vector<s> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleBouncing<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as an initializer list, and velocity data as a Vector.
   */
  SimpleBouncingAPO(std::initializer_list<double> position, Vector<s> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleBouncing<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleBouncingAPO() {}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEBOUNCINGAPO_H
