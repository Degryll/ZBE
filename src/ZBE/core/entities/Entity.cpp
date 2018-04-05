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
}

void Entity::setINACTIVE(uint64_t id) {
  _setState(id, zbe::Ticket::State::INACTIVE);
}

void Entity::setERASED(uint64_t id) {
  auto it = tl.find(id);
  if (it == tl.end()) {
    SysError::setError("Ticket in Entity list is not found.");
  } else {
    it->second->setERASED();
    tl.erase(it);
  }
}

void Entity::setACTIVE() {
  _setState(zbe::Ticket::State::ACTIVE);
}

void Entity::setINACTIVE() {
}

void Entity::setERASED() {
  _setState(zbe::Ticket::State::ERASED);
  tl.clear();
}

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

void Entity::setDouble(uint64_t id, std::shared_ptr<Value<double> >   val) {
  auto it = dv.find(id);
  if (it != dv.end()) {
    SysError::setError("Overriding entity double value not allowed.");
  } else {
    dv[id] = val;
  }
}

void Entity::setUint(uint64_t id, std::shared_ptr<Value<uint64_t> > val) {
  auto it = uv.find(id);
  if (it != uv.end()) {
    SysError::setError("Overriding entity uint value not allowed.");
  } else {
    uv[id] = val;
  }
}

void Entity::setInt(uint64_t id, std::shared_ptr<Value<int64_t> >  val) {
  auto it = iv.find(id);
  if (it != iv.end()) {
    SysError::setError("Overriding entity int value not allowed.");
  } else {
    iv[id] = val;
  }
}

std::shared_ptr<Value<double> >  Entity::getDouble(uint64_t id) {
  auto it = dv.find(id);
  if (it == dv.end()) {
    SysError::setError("Entity has no double value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<double> >());
  } else {
    return (dv[id]);
  }
}

std::shared_ptr<Value<uint64_t> > Entity::getUint(uint64_t id) {
  auto it = uv.find(id);
  if (it == uv.end()) {
    SysError::setError("Entity has no uint value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<uint64_t> >());
  } else {
    return (uv[id]);
  }
}

std::shared_ptr<Value<int64_t> >  Entity::getInt(uint64_t id) {
  auto it = iv.find(id);
  if (it == iv.end()) {
    SysError::setError("Entity has no int value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<int64_t> >());
  } else {
    return (iv[id]);
  }
}

}  // namespace zbe
