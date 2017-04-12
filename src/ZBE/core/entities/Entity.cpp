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

void Entity::addToList(uint64_t id, std::shared_ptr<Ticket> ticket) {
  auto it = tl.find(id);
  if (it != tl.end()) {
    it->second->setERASED();
  }
  tl[id] = ticket;
}

void Entity::setACTIVE(uint64_t id) {
  _setState(id, zbe::Ticket::State::ACTIVE);
};

void Entity::setINACTIVE(uint64_t id) {
  _setState(id, zbe::Ticket::State::INACTIVE);
};

void Entity::setERASED(uint64_t id) {
  auto it = tl.find(id);
  if (it == tl.end()) {
    SysError::setError("Ticket in Entity list is not found.");
  } else {
    it->second->setERASED();
    tl.erase(it);
  }
};

void Entity::setACTIVE() {
  _setState(zbe::Ticket::State::ACTIVE);
};

void Entity::setINACTIVE() {
};

void Entity::setERASED() {
  _setState(zbe::Ticket::State::ERASED);
  tl.clear();
};

void Entity::_setState(uint64_t id, zbe::Ticket::State state) {
  auto it = tl.find(id);
  if (it == tl.end()) {
    SysError::setError("Ticket in Entity list is not found.");
  } else {
    it->second->setState(state);
  }
}

inline void Entity::_setState(zbe::Ticket::State state) {
  for(auto& t : tl){
    t.second->setState(state);
  }
}

}  // namespace zbe
