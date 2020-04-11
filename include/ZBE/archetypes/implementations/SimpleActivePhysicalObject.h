/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleActivePhysicalObject.h
 * @since 2017-05-07
 * @date 2017-05-07
 * @author Degryll Ludo Batis
 * @brief Implements the interface of an object that interacts actively with other objects.
 * Please, if inherit from this class, use APO for naming.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEACTIVEPHYSICALOBJECT_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEACTIVEPHYSICALOBJECT_H

#include <cstdint>

#include "ZBE/archetypes/ActivePhysicalObject.h"
#include "ZBE/archetypes/implementations/SimplePhysicalObject.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implements the interface of an object that interacts actively with other objects.
 *  Please, if inherit from this class, use APO for naming.
 */
class SimpleActivePhysicalObject : virtual public ActivePhysicalObject, public SimplePhysicalObject {
public:
  /** \brief Creates an Active physical object with two lists, his actuators and the collisionables.
   *  \param actuatorsList Index of a list of actuators. This actuators will be called when this object collide.
   *  \param collisionableList Index of a list of collisionables. The interaction generator look for a collision between this object and any of his collisionables.
   */
  SimpleActivePhysicalObject(uint64_t actuatorsList, uint64_t collisionablesList) : SimplePhysicalObject(actuatorsList), cl(collisionablesList) {}

  /** \brief Virtual destructor.
   */
  virtual ~SimpleActivePhysicalObject() {}

  /** \brief Set the collisionables list.
   *  \param collisionablesList The collisionables list index.
   *  \sa getColliionablesList
   */
  void setCollisionablesList(uint64_t collisionablesList) {cl = collisionablesList;}

  /** \brief Return the collisionables list index.
   *  \return The collisionables list index.
   *  \sa setColliionablesList
   */
  uint64_t getCollisionablesList() {return (cl);}

private:
  uint64_t cl;
};

}  // namespace zbe

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEACTIVEPHYSICALOBJECT_H
