/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ActivePhysicalObject.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts actively physically.
 * Please, if inherit from this class, use APO for naming.
 */

#ifndef ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H
#define ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H

#include <cstdint>

#include "ZBE/archetypes/PhysicalObject.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines the interface of an object that interacts actively physically.
 *  Please, if inherit from this class, use APO for naming.
 */
class ActivePhysicalObject : virtual public PhysicalObject {
public:
  /** \brief Virtual destructor.
   */
  virtual ~ActivePhysicalObject() {}

  /** \brief Set the collisionables list.
   *  \param collisionablesList The collisionables list index.
   *  \sa getColliionablesList
   */
  virtual void setCollisionablesList(uint64_t collisionablesList) = 0;

  /** \brief Return the collisionables list index.
   *  \return The collisionables list index.
   *  \sa setColliionablesList
   */
  virtual uint64_t getCollisionablesList() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H
