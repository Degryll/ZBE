/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideMobile.h
 * @since 2017-01-30
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the WideMobile interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILE_H

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/archetypes/WideMobile.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/archetypes/implementations/SimpleWide.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Simple implementation of the WideMobile interface.
 */
template <unsigned s>
class ZBEAPI SimpleWideMobile : virtual public WideMobile<s>, public SimpleWide, public SimpleMobile<s> {
public:
  /** \brief Constructor with position and velocity set to 0.
   */
  SimpleWideMobile(double width) : SimpleMobile<s>(), SimpleWide(width) {}

  /** \brief Constructor with position set by an initializer list and velocity set to 0.
   */
  SimpleWideMobile(std::initializer_list<double> position, double width) : SimpleMobile<s>(position), SimpleWide(width) {}

  /** \brief Constructor with position set by a Point and velocity set to 0.
   */
  SimpleWideMobile(Point<s> position, double width) : SimpleMobile<s>(position), SimpleWide(width) {}

  /** \brief Constructor with position set to 0 and velocity set by a Vector.
   */
  SimpleWideMobile(Vector<s> velocity, double width) : SimpleMobile<s>(velocity), SimpleWide(width) {}

  /** \brief Constructor with position and velocity set by an initializer list.
   */
  SimpleWideMobile(std::initializer_list<double> position, std::initializer_list<double> velocity, double width) : SimpleMobile<s>(position, velocity), SimpleWide(width) {}

  /** \brief Constructor with position set by a Point and velocity set by an initializer list.
   */
  SimpleWideMobile(Point<s> position, std::initializer_list<double> velocity, double width) : SimpleMobile<s>(position, velocity), SimpleWide(width) {}

  /** \brief Constructor with position set by a Point and velocity set by a Vector.
   */
  SimpleWideMobile(Point<s> position, Vector<s> velocity, double width) : SimpleMobile<s>(position, velocity), SimpleWide(width) {}

  /** \brief Constructor with position set by an initializer list and velocity set by a Vector.
   */
  SimpleWideMobile(std::initializer_list<double> position, Vector<s> velocity, double width) : SimpleMobile<s>(position, velocity), SimpleWide(width) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleWideMobile() {}
};

}  // namespace

#endif  //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDEMOBILE_H
