/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionableEntity.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Degryll
 * @brief Define the basic functionality of every Collisionable entity.
 */

#include "ZBE/core/entities/CollisionableEntity.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

void CollisionableEntity::addToCollisionablesList(uint64_t id, uint64_t listId) {
  cl[id] = listId;
}

void CollisionableEntity::removeFromCollisionablesList(uint64_t id) {
  cl.erase(id);
}

uint64_t CollisionableEntity::getCollisionablesList(uint64_t id) {
  auto it = cl.find(id);
  if (it == cl.end()) {
    SysError::setError("Collisionable in Entity list is not found.");
    return (0);
  } else {
    return (it->second);
  }
}

void CollisionableEntity::addToActuatorsList(uint64_t id, uint64_t listId) {
  al[id] = listId;
}

void CollisionableEntity::removeFromActuatorsList(uint64_t id) {
  al.erase(id);
}

uint64_t CollisionableEntity::getActuatorsList(uint64_t id) {
  auto it = al.find(id);
  if (it == al.end()) {
    SysError::setError("Actuator in Entity list is not found.");
    return (0);
  } else {
    return (it->second);
  }
}

}  // namespace zbe

