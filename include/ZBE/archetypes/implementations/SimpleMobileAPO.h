/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleMobileAPO.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll
 * @brief Simple implementation of the Mobile active physical object interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILEAPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILEAPO_H

#include <cstdint>
#include <initializer_list>

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/archetypes/MobileAPO.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/archetypes/implementations/SimpleAcitvePhysicalObject.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Simple implementation of the Mobile active physical object interface.
 */
template <typename R, unsigned s>
class SimpleMobileAPO : public MobileAPO<R, s>, public SimpleMobile<s>, public SimpleActivePhysicalObject {
public:
  /** \brief Constructs a BouncingAPO with position and velocity set to 0.
   */
  SimpleMobileAPO(uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile(), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as an initializer list. Velocity will be 0.
   */
  SimpleMobileAPO(std::initializer_list<double> position, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile(position), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point. Velocity will be 0.
   */
  SimpleMobileAPO(Point<s> position, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with velocity data as a Vector. Position will be 0.
   */
  SimpleMobileAPO(Vector<s> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position and velocity data as an initializer list.
   */
  SimpleMobileAPO(std::initializer_list<double> position, std::initializer_list<double> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point, and velocity data as an initializer list.
   */
  SimpleMobileAPO(Point<s> position, std::initializer_list<double> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point, and velocity data as a Vector.
   */
  SimpleMobileAPO(Point<s> position, Vector<s> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as an initializer list, and velocity data as a Vector.
   */
  SimpleMobileAPO(std::initializer_list<double> position, Vector<s> velocity, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleMobileAPO(){}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILEAPO_H
