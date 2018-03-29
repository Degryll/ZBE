/**
 * Copyright 2012 Batis Degryll Ludo
 * @file WideMobile.h
 * @since 2017-03-26
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Interface of an archetype with a width.
 */

#ifndef ZBE_ARCHETYPES_WIDE_H
#define ZBE_ARCHETYPES_WIDE_H

namespace zbe {

/** \brief Interface of an archetype with a width.
 */
class Wide {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Wide() {}

  /** \brief Set the width.
   *  \param width width.
   *  \sa getWidth
   */
  virtual void setWidth(double) = 0;

  /** \brief Return the width.
   *  \return The width.
   *  \sa setWidth
   */
  virtual double getWidth() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_WIDE_H
