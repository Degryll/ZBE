/**
 * Copyright 2012 Batis Degryll Ludo
 * @file PhysicalObject.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts with other objects.
 */

#ifndef ZBE_ARCHETYPES_PHYSICALOBJECT_H
#define ZBE_ARCHETYPES_PHYSICALOBJECT_H

#include <cstdint>

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Defines the interface of an object that interacts with other objects.
 *  Please, if inherit from this class, use PO for naming.
 */
class ZBEAPI PhysicalObject {
public:
  /** \brief Virtual destructor.
   */
  virtual ~PhysicalObject() {}

  /** \brief Set the actuators list.
   *  \param actuatorsList The actuators list index.
   *  \sa getActuatorsList
   */
  virtual void setActuatorsList(uint64_t actuatorsList) = 0;

  /** \brief Get the actuators list index.
   *  \return The index of the actuators list.
   */
  virtual uint64_t getActuatorsList() = 0;
};

}  // namespace zbe

#endif  // ZBE_ARCHETYPES_PHYSICALOBJECT_H
