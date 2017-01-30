/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ActivePhysicalObject.h
 * @since 2016-12-16
 * @date 2017-01-30
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts actively physically.
 * Please, if inherit this class, use APO for naming.
 */

#ifndef ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H
#define ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H

#include <cstdint>

#include "ZBE/archetypes/PhysicalObject.h"

namespace zbe {

class ActivePhysicalObject : public PhysicalObject {
public:
  ActivePhysicalObject(uint64_t actuatorsList, uint64_t collisionablesList) : PhysicalObject(actuatorsList), cl(collisionablesList) {}

  virtual ~ActivePhysicalObject() {}

  void setCollisionablesList(uint64_t collisionablesList) {cl = collisionablesList;}
  uint64_t getCollisionablesList() {return (cl);}

private:
  uint64_t cl;
};

}  // namespace

#endif //ZBE_ARCHETYPES_ACTIVEPHYSICALOBJECT_H
