/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionerEntity.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Degryll
 * @brief Define the basic functionality of every Collisionable entity.
 */

#include "ZBE/core/entities/CollisionerEntity.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

void CollisionerEntity::addToActuatorsList(uint64_t id, uint64_t listId) {
  al[id] = listId;
}

void CollisionerEntity::removeFromActuatorsList(uint64_t id) {
  al.erase(id);
}

uint64_t CollisionerEntity::getActuatorsList(uint64_t id) {
  auto it = al.find(id);
  if (it == al.end()) {
    SysError::setError("Actuator in Entity list is not found.");
    return (0);
  } else {
    return (it->second);
  }
}

}  // namespace zbe
