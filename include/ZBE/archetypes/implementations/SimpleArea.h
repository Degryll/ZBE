/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Area.h
 * @since 2017-10-14
 * @date 2018-02-22
 * @author Degryll Ludo Batis
 * @brief Implementation of an archetype that has an area.
 */

#ifndef ZBE_ARCHETYPES_SIMPLEAREA_H
#define ZBE_ARCHETYPES_SIMPLEAREA_H

#include "ZBE/archetypes/Area.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** @brief Implementation of an archetype that has an area.
*/
class ZBEAPI SimpleArea : virtual public Area {
public:

  /** \brief Empty constructor
   */
  SimpleArea() : w(), h() {}

  /** \brief Constructor with initial data
   */
  SimpleArea(double width, double height) : w(width), h(height) {}

  /** \brief Virtual destructor.
   */
  ~SimpleArea() {}

  /** \brief Set area height
   *  \param height
   */
  void setHeight(double height) { h = height; }

  /** \brief Set area width
   *  \param width
   */
  void setWidth(double width) { w = width; }

  /** \brief Get area height
   */
  double getHeight() { return h; }

  /** \brief Get area width
   */
  double getWidth() { return w; }

private:

  double w;
  double h;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_SIMPLEAREA_H
