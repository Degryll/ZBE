/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimplePhysicalObject.h
 * @since 2016-12-16
 * @date 2017-05-07
 * @author Degryll
 * @brief Implements the interface of an object that interacts with other objects.
 * Please, if inherit from this class, use PO for naming.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPHYSICALOBJECT_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPHYSICALOBJECT_H

#include <cstdint>

#include "ZBE/archetypes/PhysicalObject.h"

namespace zbe {

/** \brief Implements the interface of an object that interacts with other objects.
 *  Please, if inherit from this class, use PO for naming.
 */
class SimplePhysicalObject : virtual public PhysicalObject {
public:
  /** \brief Construct a physicalObject with his actuators list.
   *  \param actuatorsList Index list of actuators.
   */
  SimplePhysicalObject(uint64_t actuatorsList) : al(actuatorsList) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimplePhysicalObject() {}

  /** \brief Set the actuators list.
   *  \param actuatorsList The actuators list index.
   *  \sa getActuatorsList
   */
  void setActuatorsList(uint64_t actuatorsList) {al = actuatorsList;}

  /** \brief Get the actuators list index.
   *  \return The index of the actuators list.
   */
  uint64_t getActuatorsList() {return (al);}

private:
  uint64_t al;
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPHYSICALOBJECT_H
