/**
 * Copyright 2012 Batis Degryll Ludo
 * @file WideMobile.h
 * @since 2017-03-26
 * @date 2017-05-10
 * @author Degryll Batis Ludo
 * @brief Defines the interface of a class with a width.
 */

#ifndef ZBE_ARCHETYPES_WIDE_H
#define ZBE_ARCHETYPES_WIDE_H

namespace zbe {

/** \brief Defines the interface of a class with a width.
 */
class Wide {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Wide() {}

  /** \brief Set the size of the archetype.
   *  \param width Size of the archetype.
   *  \sa getWidth
   */
  virtual void setWidth(double width) = 0;

  /** \brief Return the size of the archetype.
   *  \return The size of the archetype.
   *  \sa setWidth
   */
  virtual double getWidth() = 0;
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_WIDE_H
