/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Entity.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Degryll
 * @brief Define the basic functionality of every entity.
 */

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

Entity::~Entity() {
  for(auto it = tl.begin(); it != tl.end(); it++) {
    it->second->setERASED();
  }
}

void Entity::addToList(uint64_t id, Ticket *ticket) {
  tl[id] = ticket;
}

void Entity::setState(uint64_t id, zbe::Ticket::State state) {
  auto it = tl.find(id);
  if (it == tl.end()) {
    SysError::setError("Ticket in Entity list is not found.");
  } else {
    it->second->setState(state);
  }
}

}  // namespace zbe
