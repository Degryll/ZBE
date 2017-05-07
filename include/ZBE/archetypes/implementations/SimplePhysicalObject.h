/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimplePhysicalObject.h
 * @since 2016-12-16
 * @date 2017-05-07
 * @author Degryll
 * @brief Implements the interface of an object that interacts physically.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPHYSICALOBJECT_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPHYSICALOBJECT_H

#include <cstdint>

#include "ZBE/archetypes/PhysicalObject.h"

namespace zbe {

class SimplePhysicalObject : virtual public PhysicalObject {
public:

  SimplePhysicalObject(uint64_t actuatorsList) : al(actuatorsList) {}

  virtual ~SimplePhysicalObject() {}

  uint64_t getActuatorsList() {return (al);}

private:
  uint64_t al;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEPHYSICALOBJECT_H
