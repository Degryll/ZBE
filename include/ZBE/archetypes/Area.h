/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Area.h
 * @since 2017-10-14
 * @date 2017-10-14
 * @author Degryll Ludo Batis
 * @brief Interface of an archetype that has an area.
 */

#ifndef ZBE_ARCHETYPES_AREA_H
#define ZBE_ARCHETYPES_AREA_H

namespace zbe {

/** @brief Interface of an archetype that has an area.
*/
class Area {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Area() {}

  /** \brief Set area height
   *  \param height
   */
  virtual void setHeight(double height) = 0;

  /** \brief Set area width
   *  \param width
   */
  virtual void setWidth(double width) = 0;

  /** \brief Get area height
   */
  virtual double getHeight() = 0;

  /** \brief Get area width
   */
  virtual double getWidth() = 0;
};

} // namespace zbe

#endif  // ZBE_ARCHETYPES_AREA_H
