/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Entity.h
 * @since 2016-03-24
 * @date 2018-05-06
 * @author Degryll Batis Ludo
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

void Entity::addTicket(uint64_t id, std::shared_ptr<Ticket> ticket) {
  auto it = tl.find(id);
  if (it != tl.end()) {
    SysError::setError("Ticket in Entity list is not found.");
  }
  tl[id] = ticket;
}

void Entity::replaceTicket(uint64_t id, std::shared_ptr<Ticket> ticket) {
  auto it = tl.find(id);
  if (it != tl.end()) {
    ticket->setState(it->second->getState());
    it->second->setERASED();
  }
  tl[id] = ticket;
}

void Entity::setACTIVE(uint64_t id) {
  auto it = tl.find(id);
  if (it == tl.end()) {
    SysError::setError("Ticket in Entity list is not found.");
  } else {
    it->second->setACTIVE();
  }
}

inline void Entity::setACTIVE() {
  for(auto& t : tl){
    t.second->setACTIVE();
  }
}

void Entity::setINACTIVE(uint64_t id) {
  auto it = tl.find(id);
  if (it == tl.end()) {
    SysError::setError("Ticket in Entity list is not found.");
  } else {
    it->second->setINACTIVE();
  }
}

inline void Entity::setINACTIVE() {
  for(auto& t : tl){
    t.second->setINACTIVE();
  }
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

inline void Entity::setERASED() {
  for(auto& t : tl){
    t.second->setERASED();
  }
  tl.clear();
}

void Entity::setDouble(uint64_t id, std::shared_ptr<Value<double> >   val) {
  auto it = dv.find(id);
  if (it != dv.end()) {
    SysError::setError("Overriding entity double value not allowed.");
  } else {
    dv[id] = val;
  }
}

void Entity::setFloat(uint64_t id, std::shared_ptr<Value<float> >   val) {
  auto it = fv.find(id);
  if (it != fv.end()) {
    SysError::setError("Overriding entity double value not allowed.");
  } else {
    fv[id] = val;
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

std::shared_ptr<Value<float> >  Entity::getFloat(uint64_t id) {
  auto it = fv.find(id);
  if (it == fv.end()) {
    SysError::setError("Entity has no double value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<float> >());
  } else {
    return (fv[id]);
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
