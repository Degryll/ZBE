/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideMobileAPO.h
 * @since 2017-01-30
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Implements the interface of a class ZBEAPI with a position, velocity, width and interacts actively with other objects.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILEAPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILEAPO_H

#include <cstdint>
#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/archetypes/WideMobileAPO.h"
#include "ZBE/archetypes/implementations/SimpleWide.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/archetypes/implementations/SimpleActivePhysicalObject.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implements the interface of a class ZBEAPI with a position, velocity, width and interacts actively with other objects.
 */
template <unsigned s>
class SimpleWideMobileAPO : virtual public WideMobileAPO<s>, public SimpleWide, public SimpleMobile<s> public SimpleActivePhysicalObject {
public:
  /** \brief Constructor with position and velocity set to 0.
   */
  SimpleWideMobileAPO(double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWide(width), SimpleMobile<s>(), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position set by an initializer list and velocity set to 0.
   */
  SimpleWideMobileAPO(std::initializer_list<double> position, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWide(width), SimpleMobile<s>(position), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position set by a Point and velocity set to 0.
   */
  SimpleWideMobileAPO(Point<s> position, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWide(width), SimpleMobile<s>(position), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position set to 0 and velocity set by a Vector.
   */
  SimpleWideMobileAPO(Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWide(width), SimpleMobile<s>(velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position and velocity set by an initializer list.
   */
  SimpleWideMobileAPO(std::initializer_list<double> position, std::initializer_list<double> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWide(width), SimpleMobile<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position set by a Point and velocity set by an initializer list.
   */
  SimpleWideMobileAPO(Point<s> position, std::initializer_list<double> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWide(width), SimpleMobile<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position set by a Point and velocity set by a Vector.
   */
  SimpleWideMobileAPO(Point<s> position, Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWide(width), SimpleMobile<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position set by an initializer list and velocity set by a Vector.
   */
  SimpleWideMobileAPO(std::initializer_list<double> position, Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleWide(width), SimpleMobile<s>(position, velocity), SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleWideMobileAPO() {}
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILEAPO_H
