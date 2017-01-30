/**
 * Copyright 2012 Batis Degryll Ludo
 * @file PhysicalObject.h
 * @since 2016-12-16
 * @date 2017-01-30
 * @author Degryll Ludo Batis
 * @brief Defines the interface of an object that interacts physically.
 */

#ifndef ZBE_ARCHETYPES_PHYSICALOBJECT_H
#define ZBE_ARCHETYPES_PHYSICALOBJECT_H

#include <cstdint>

namespace zbe {

class PhysicalObject {
public:

  PhysicalObject (uint64_t actuatorsList) : al(actuatorsList) {}

  virtual ~PhysicalObject() {}

  void setActuatorsList(uint64_t actuatorsList) {al = actuatorsList;}
  uint64_t getActuatorsList() {return (al);}

private:
  uint64_t al;
};

}  // namespace

#endif //ZBE_ARCHETYPES_PHYSICALOBJECT_H
