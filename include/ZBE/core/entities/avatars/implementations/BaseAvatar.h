/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseAvatar.h
 * @since 2017-04-12
 * @date 2018-02-25
 * @author Ludo Batis Degryll
 * @brief Base implementation of avatar that uses an Entity.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEAVATAR_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEAVATAR_H_

#include <cstdint>
#include <memory>
#include <assert.h>

#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {


/** \brief Base implementation of avatar that uses an Entity.
 */
struct AvatarImp : virtual public Avatar {

  AvatarImp(std::shared_ptr<Entity> entity) : e(entity) {}

  /** \brief Register a new Ticket from a list.
   *  \param id Id to identify the list.
   *  \param ticket The ticket to be stored.
   */
  void addTicket(uint64_t id, std::shared_ptr<Ticket> ticket) {
    e->addTicket(id, ticket);
  }

  /** \brief Register a new Ticket, if there is a ticket on the id, will be replaced.
   *  \param id Id to identify the ticket origin.
   *  \param ticket The ticket to be stored.
   */
  void replaceTicket(uint64_t id, std::shared_ptr<Ticket> ticket) {
    e->replaceTicket(id, ticket);
  }

  /** \brief Change the state of this avatar in the list identified by id to ACTIVE.
   *  \param id Id to identify the list.
   */
  void setACTIVE(uint64_t id) {
      e->setACTIVE(id);
  }

  /** \brief Change the state of this avatar in the list identified by id to INACTIVE.
   *  \param id Id to identify the list.
   */
  void setINACTIVE(uint64_t id){
      e->setINACTIVE(id);
  }

  /** \brief Change the state of this avatar in the list identified by id to ACTIVE.
   *  \param id Id to identify the list.
   */
  void setERASED(uint64_t id){
      e->setERASED(id);
  }

  /** \brief Change the state of this avatar for all list to ACTIVE.
   */
  void setACTIVE(){
      e->setACTIVE();
  }

  /** \brief Change the state of this avatar for all list to INACTIVE.
   */
  void setINACTIVE(){
      e->setINACTIVE();
  }

  /** \brief Change the state of this avatar for all list to ERASED.
   */
  void setERASED(){
      e->setERASED();
  }

  /** \brief Changes the contextTime of this entity to the value of cTime.
   *  \param cTime Value to put in the Entity's cTime
   */
  void setContextTime(std::shared_ptr<ContextTime> cTime) {
    e->setContextTime(cTime);
  }

  /** \brief Returns the context time of the Entity.
   */
  std::shared_ptr<ContextTime> getContextTime() {
    return e->getContextTime();
  }

  /** \brief Access the underliying entity (if allowed)
   */
  virtual std::shared_ptr<Entity> getEntity() = 0;

protected:
  AvatarImp() : e() {}

  void setupEntity(std::shared_ptr<Entity> entity) { e = entity;}

  std::shared_ptr<Entity> e;
};


/** \brief Base implementation of avatar that uses an Entity.
 */
struct AwareAvatar : public AvatarImp {
public:
  AwareAvatar(std::shared_ptr<Entity> entity) : AvatarImp(entity) {}

  /** \brief Access the underliying entity (if allowed)
   */
  std::shared_ptr<Entity> getEntity() {
    return e;
  }
protected:
  AwareAvatar() : AvatarImp() {}

  void setupEntity(std::shared_ptr<Entity> entity) { AvatarImp::setupEntity(entity); }
};

/** \brief Base implementation of avatar that uses an Entity.
 */
struct BaseAvatar : public AvatarImp {
public:
  BaseAvatar(std::shared_ptr<Entity> entity) : AvatarImp(entity) {}

  /** \brief Access the underliying entity (if allowed)
   */
  std::shared_ptr<Entity> getEntity() {
    assert(false);
  }
protected:
  BaseAvatar() : AvatarImp() {}

  void setupEntity(std::shared_ptr<Entity> entity) { AvatarImp::setupEntity(entity); }
};

template <typename A, unsigned n, typename T, typename... Ts>
class _BaseAvatar : virtual public _Avatar<n, T, Ts...>,
                            public _BaseAvatar<A, n, T>,
                            public _BaseAvatar<A, n-1, Ts...>  {
public:
  _BaseAvatar(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) : A(entity), _BaseAvatar<A, n, T>(entity, ids[0]), _BaseAvatar<A, n-1, Ts...>(entity, ids.begin()+1) {}

  _BaseAvatar() : A(), _BaseAvatar<A, n, T>(), _BaseAvatar<A, n-1, Ts...>() {}

  virtual ~_BaseAvatar() {}

  void setupEntity(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) {
    A::setupEntity(entity);
    _BaseAvatar<A, n, T>::setupEntity(entity, ids[0]);
    _BaseAvatar<A, n-1, Ts...>::setupEntity(entity, ids.begin()+1);
  }

protected:

  template <unsigned m = n>
  _BaseAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<(m!=2)>::type * = nullptr) : A(entity), _BaseAvatar<A, m, T>(entity, *idsi), _BaseAvatar<A, m-1, Ts...>(entity, idsi+1) {}

  template <unsigned m = n>
  _BaseAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<!(m!=2), int>::type * = nullptr) : A(entity), _BaseAvatar<A, m, T>(entity, *idsi), _BaseAvatar<A, m-1, Ts...>(entity, *(++idsi)) {}

  template <unsigned m = n>
  void setupEntity(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<(m!=2)>::type * = nullptr) {
    A::setupEntity(entity);
    _BaseAvatar<A, m, T>::setupEntity(entity, *idsi);
    _BaseAvatar<A, m-1, Ts...>::setupEntity(entity, idsi+1);
  }

  template <unsigned m = n>
  void setupEntity(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<!(m!=2), int>::type * = nullptr) {
    A::setupEntity(entity), _BaseAvatar<A, m, T>::setupEntity(entity, *idsi);
    _BaseAvatar<A, m-1, Ts...>::setupEntity(entity, *(++idsi));
  }

};

template <typename A, unsigned n, typename T>
class _BaseAvatar<A, n, T> : virtual public A, virtual public _Avatar<n, T> {
public:
  _BaseAvatar() : A(), _Avatar<n, T>(), v() { setCallback();}
  _BaseAvatar(std::shared_ptr<Entity> entity, uint64_t id)
   : A(entity),
     _Avatar<n, T>(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, (void*)this),
     v(entity->get<T, std::shared_ptr<zbe::Value<T> > >(id)) {
       setCallback();
     }
 _BaseAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, 1>::iterator idsi)
  : A(entity),
    _Avatar<n, T>(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, (void*)this),
    v(entity->get<T, std::shared_ptr<zbe::Value<T> > >(*idsi)) {
      setCallback();
    }

  virtual ~_BaseAvatar() {}

  void setupEntity(std::shared_ptr<Entity> entity, uint64_t id) {
    A::setupEntity(entity);
    _Avatar<n, T>::setup(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, (void*)this);
    v = entity->get<T, std::shared_ptr<zbe::Value<T> > >(id);
  }

  void setupEntity(std::shared_ptr<Entity> entity, typename std::array<uint64_t, 1>::iterator idsi) {
    A::setupEntity(entity);
    _Avatar<n, T>::setup(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, (void*)this);
    v = entity->get<T, std::shared_ptr<zbe::Value<T> > >(*idsi);
  }

  static std::shared_ptr<Value<T> > getImpl(void *instance) {
    //TODO asegurarse de que este casting es en tiempo de compilación (static cast?)
    return (((_BaseAvatar<A, n, T>*)instance)->v);
  }

  static void setImpl(void *instance, T value) {
    //TODO asegurarse de que este casting es en tiempo de compilación (static cast?)
    ((_BaseAvatar<A, n, T>*)instance)->v->set(value);
  }

protected:
  void setCallback() {
    _Avatar<n, T>::setup(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, (void*)this);
  }
private:
  std::shared_ptr<Value<T> > v;
};

template<typename T, typename... Ts>
using MBaseAvatar = _BaseAvatar<BaseAvatar, sizeof...(Ts)+1, T, Ts...>;

template<typename T>
using SBaseAvatar = _BaseAvatar<BaseAvatar, 1, T>;

template<typename T, typename... Ts>
using MAwareAvatar = _BaseAvatar<AwareAvatar, sizeof...(Ts)+1, T, Ts...>;

template<typename T>
using SAwareAvatar = _BaseAvatar<AwareAvatar, 1, T>;

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEAVATAR_H_
