/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideBouncingAPO.h
 * @since 2017-03-20
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Implements the interface of a class with a position, a velocity, a width, the ability to accumulate normals and interacts actively with other objects.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEBOUNCINGAPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEBOUNCINGAPO_H

#include <cstdint>
#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/archetypes/WideBouncingAPO.h"
#include "ZBE/archetypes/implementations/SimpleWide.h"
#include "ZBE/archetypes/implementations/SimpleBouncing.h"
#include "ZBE/archetypes/implementations/SimpleActivePhysicalObject.h"

namespace zbe {

/** \brief Implements the interface of a class with a position, a velocity, a width, the ability to accumulate normals and interacts actively with other objects.
 */
template <unsigned s>
class SimpleWideBouncingAPO : virtual public WideBouncingAPO<s>, public SimpleWide, public SimpleBouncing<s>, public SimpleActivePhysicalObject {
public:
  /** \brief Constructor with position data as an initializer list. Velocity will be 0.
   */
  SimpleWideBouncingAPO(std::initializer_list<double> position, double width, uint64_t actuatorsList, uint64_t collisionablesList)
  : SimpleWide(width),
    SimpleBouncing<s>(position),
    SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point. Velocity will be 0.
   */
  SimpleWideBouncingAPO(Point<s> position, double width, uint64_t actuatorsList, uint64_t collisionablesList)
  : SimpleWide(width),
    SimpleBouncing<s>(position),
    SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with velocity data as a Vector. Position will be 0.
   */
  SimpleWideBouncingAPO(Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList)
  : SimpleWide(width),
    SimpleBouncing<s>(velocity),
    SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position and velocity data as an initializer list.
   */
  SimpleWideBouncingAPO(std::initializer_list<double> position, std::initializer_list<double> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList)
  : SimpleWide(width),
    SimpleBouncing<s>(position, velocity),
    SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point, and velocity data as an initializer list.
   */
  SimpleWideBouncingAPO(Point<s> position, std::initializer_list<double> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList)
  : SimpleWide(width),
    SimpleBouncing<s>(position, velocity),
    SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as a Point, and velocity data as a Vector.
   */
  SimpleWideBouncingAPO(Point<s> position, Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList)
  : SimpleWide(width),
    SimpleBouncing<s>(position, velocity),
    SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Constructor with position data as an initializer list, and velocity data as a Vector.
   */
  SimpleWideBouncingAPO(std::initializer_list<double> position, Vector<s> velocity, double width, uint64_t actuatorsList, uint64_t collisionablesList)
  : SimpleWide(width),
    SimpleBouncing<s>(position, velocity),
    SimpleActivePhysicalObject(actuatorsList, collisionablesList) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleWideBouncingAPO() {}
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEBOUNCINGAPO_H
