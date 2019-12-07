/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleWideMobile.h
 * @since 2017-03-26
 * @date 2017-05-07
 * @author Degryll Ludo Batis
 * @brief Simple implementation of the Wide archetype.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDE_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDE_H

#include "ZBE/archetypes/Wide.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Simple implementation of the Wide archetype.
 */
class ZBEAPI SimpleWide : virtual public Wide {
public:
  /** \brief Parametrized constructor. Set the size of the archetype.
   *  \param width Size of the archetype.
   */
  SimpleWide(double width) :w(width) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleWide() {}

  /** \brief Set the size of the archetype.
   *  \param width Size of the archetype.
   *  \sa getWidth
   */
  void setWidth(double width) {w = width;}

  /** \brief Return the size of the archetype.
   *  \return The size of the archetype.
   *  \sa setWidth
   */
  double getWidth() {return (w);}

private:
  double w;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEWIDE_H
