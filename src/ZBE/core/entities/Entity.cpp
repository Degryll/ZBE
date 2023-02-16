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

void Entity::setACTIVE() {
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

void Entity::setINACTIVE() {
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

void Entity::setERASED() {
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

void Entity::setBool(uint64_t id, std::shared_ptr<Value<bool> >  val) {
  auto it = bv.find(id);
  if (it != bv.end()) {
    SysError::setError("Overriding entity bool value not allowed.");
  } else {
    bv[id] = val;
  }
}

void Entity::setVector3D(uint64_t id, std::shared_ptr<Value<Vector3D> > val) {
  auto it = v3v.find(id);
  if (it != v3v.end()) {
    SysError::setError("Overriding entity Vector3D value not allowed.");
  } else {
    v3v[id] = val;
  }
}

void Entity::setVector2D(uint64_t id, std::shared_ptr<Value<Vector2D> > val) {
  auto it = v2v.find(id);
  if (it != v2v.end()) {
    SysError::setError("Overriding entity Vector2D value not allowed.");
  } else {
    v2v[id] = val;
  }
}

void Entity::setString(uint64_t id, std::shared_ptr<Value<std::string> > val) {
  auto it = sv.find(id);
  if (it != sv.end()) {
    SysError::setError("Overriding entity String value not allowed.");
  } else {
    sv[id] = val;
  }
}

void Entity::setStringVector(uint64_t id, std::shared_ptr<Value<std::vector<std::string> > > val) {
  auto it = svv.find(id);
  if (it != svv.end()) {
    SysError::setError("Overriding entity String vector value not allowed.");
  } else {
    svv[id] = val;
  }
}

void Entity::overrideDouble(uint64_t id, std::shared_ptr<Value<double> >   val) {
  auto it = dv.find(id);
  if (it == dv.end()) {
    SysError::setError("Overriding entity double value require a previous value.");
  } else {
    dv[id] = val;
  }
}

void Entity::overrideFloat(uint64_t id, std::shared_ptr<Value<float> >   val) {
  auto it = fv.find(id);
  if (it == fv.end()) {
    SysError::setError("Overriding entity double value require a previous value.");
  } else {
    fv[id] = val;
  }
}

void Entity::overrideUint(uint64_t id, std::shared_ptr<Value<uint64_t> > val) {
  auto it = uv.find(id);
  if (it == uv.end()) {
    SysError::setError("Overriding entity uint value require a previous value.");
  } else {
    uv[id] = val;
  }
}

void Entity::overrideInt(uint64_t id, std::shared_ptr<Value<int64_t> >  val) {
  auto it = iv.find(id);
  if (it == iv.end()) {
    SysError::setError("Overriding entity int value require a previous value.");
  } else {
    iv[id] = val;
  }
}

void Entity::overrideBool(uint64_t id, std::shared_ptr<Value<bool> >  val) {
  auto it = bv.find(id);
  if (it == bv.end()) {
    SysError::setError("Overriding entity bool value require a previous value.");
  } else {
    bv[id] = val;
  }
}

void Entity::overrideVector3D(uint64_t id, std::shared_ptr<Value<Vector3D> > val) {
  auto it = v3v.find(id);
  if (it == v3v.end()) {
    SysError::setError("Overriding entity Vector3D value require a previous value.");
  } else {
    v3v[id] = val;
  }
}

void Entity::overrideVector2D(uint64_t id, std::shared_ptr<Value<Vector2D> > val) {
  auto it = v2v.find(id);
  if (it == v2v.end()) {
    SysError::setError("Overriding entity Vector2D value require a previous value.");
  } else {
    v2v[id] = val;
  }
}

void Entity::overrideString(uint64_t id, std::shared_ptr<Value<std::string> > val) {
  auto it = sv.find(id);
  if (it == sv.end()) {
    SysError::setError("Overriding entity String value require a previous value.");
  } else {
    sv[id] = val;
  }
}

void Entity::overrideStringVector(uint64_t id, std::shared_ptr<Value<std::vector<std::string> > > val) {
  auto it = svv.find(id);
  if (it == svv.end()) {
    SysError::setError("Overriding entity String vector value require a previous value.");
  } else {
    svv[id] = val;
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
    SysError::setError("Entity has no float value at given index " +  std::to_string(id) + ".");
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

std::shared_ptr<Value<bool> >  Entity::getBool(uint64_t id) {
  auto it = bv.find(id);
  if (it == bv.end()) {
    SysError::setError("Entity has no bool value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<bool> >());
  } else {
    return (bv[id]);
  }
}

std::shared_ptr<Value<Vector3D> > Entity::getVector3D(uint64_t id) {
  auto it = v3v.find(id);
  if (it == v3v.end()) {
    SysError::setError("Entity has no Vector3D value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<Vector3D> >());
  } else {
    return (v3v[id]);
  }
}

std::shared_ptr<Value<Vector2D> > Entity::getVector2D(uint64_t id) {
  auto it = v2v.find(id);
  if (it == v2v.end()) {
    SysError::setError("Entity has no Vector2D value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<Vector2D> >());
  } else {
    return (v2v[id]);
  }
}

std::shared_ptr<Value<std::string> > Entity::getString(uint64_t id) {
  auto it = sv.find(id);
  if (it == sv.end()) {
    SysError::setError("Entity has no string value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<std::string> >());
  } else {
    return (sv[id]);
  }
}

std::shared_ptr<Value<std::vector<std::string> > > Entity::getStringVector(uint64_t id) {
  auto it = svv.find(id);
  if (it == svv.end()) {
    SysError::setError("Entity has no string value at given index " +  std::to_string(id) + ".");
    return (std::shared_ptr<Value<std::vector<std::string> > >());
  } else {
    return (svv[id]);
  }
}

void Entity::setContextTime(std::shared_ptr<ContextTime> cTime) {
  this->cTime = cTime;
}

std::shared_ptr<ContextTime> Entity::getContextTime() {
  return cTime;
}

}  // namespace zbe
