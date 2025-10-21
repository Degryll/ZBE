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
struct ZBEAPI AvatarImp : virtual public Avatar {

  explicit AvatarImp(std::shared_ptr<Entity> entity) : e(entity) {}

  /** \brief Register a new Ticket from a list.
   *  \param id Id to identify the list.
   *  \param ticket The ticket to be stored.
   */
  void addTicket(uint64_t id, std::shared_ptr<Ticket> ticket) override {
    e->addTicket(id, ticket);
  }

  /** \brief Register a new Ticket, if there is a ticket on the id, will be replaced.
   *  \param id Id to identify the ticket origin.
   *  \param ticket The ticket to be stored.
   */
  void replaceTicket(uint64_t id, std::shared_ptr<Ticket> ticket) override {
    e->replaceTicket(id, ticket);
  }

  /** \brief Change the state of this avatar in the list identified by id to ACTIVE.
   *  \param id Id to identify the list.
   */
  void setACTIVE(uint64_t id) override {
      e->setACTIVE(id);
  }

  /** \brief Change the state of this avatar in the list identified by id to INACTIVE.
   *  \param id Id to identify the list.
   */
  void setINACTIVE(uint64_t id) override {
      e->setINACTIVE(id);
  }

  /** \brief Change the state of this avatar in the list identified by id to ACTIVE.
   *  \param id Id to identify the list.
   */
  void setERASED(uint64_t id) override {
      e->setERASED(id);
  }

  /** \brief Change the state of this avatar for all list to ACTIVE.
   */
  void setACTIVE() override {
      e->setACTIVE();
  }

  /** \brief Change the state of this avatar for all list to INACTIVE.
   */
  void setINACTIVE() override {
      e->setINACTIVE();
  }

  /** \brief Change the state of this avatar for all list to ERASED.
   */
  void setERASED() override {
      e->setERASED();
  }

  /** \brief Changes the contextTime of this entity to the value of cTime.
   *  \param cTime Value to put in the Entity's cTime
   */
  void setContextTime(std::shared_ptr<ContextTime> cTime) override {
    e->setContextTime(cTime);
  }

  /** \brief Returns the context time of the Entity.
   */
  std::shared_ptr<ContextTime> getContextTime() override {
    return e->getContextTime();
  }

  /** \brief Access the underliying entity (if allowed)
   */
  virtual std::shared_ptr<Entity> getEntity() override = 0;

protected:
DISABLE_DLL_WARN
  AvatarImp() = default;

  void setupEntity(std::shared_ptr<Entity> entity) { e = entity;}

  std::shared_ptr<Entity> e;
DISABLE_WARNING_POP()
};


/** \brief Base implementation of avatar that uses an Entity.
 */
struct AwareAvatar : public AvatarImp {
public:
  explicit AwareAvatar(std::shared_ptr<Entity> entity) : AvatarImp(entity) {}

  /** \brief Access the underliying entity (if allowed)
   */
  std::shared_ptr<Entity> getEntity() override {
    return e;
  }
protected:
  AwareAvatar() = default;

  void setupEntity(std::shared_ptr<Entity> entity) { AvatarImp::setupEntity(entity); }
};

/** \brief Base implementation of avatar that uses an Entity.
 */
struct BaseAvatar : public AvatarImp {
public:
  explicit BaseAvatar(std::shared_ptr<Entity> entity) : AvatarImp(entity) {}

  /** \brief Access the underliying entity (if allowed)
   */
  std::shared_ptr<Entity> getEntity() override {
    assert(false);
    return 0;
  }
protected:
  BaseAvatar() = default;

  void setupEntity(std::shared_ptr<Entity> entity) { AvatarImp::setupEntity(entity); }
};

// --------- BaseAvatar

DISABLE_WARNING_PUSH(4250) // inherits via dominance. It advises us of things we want to do
template <typename A, unsigned n, typename T, typename... Ts>
class _BaseAvatar : virtual public _Avatar<n, T, Ts...>,
                            public _BaseAvatar<A, n, T>,
                            public _BaseAvatar<A, n-1, Ts...>  {
public:
  _BaseAvatar(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) : A(entity), _BaseAvatar<A, n, T>(entity, ids[0]), _BaseAvatar<A, n-1, Ts...>(entity, ids.begin()+1) {}

  // _BaseAvatar() : A(), _BaseAvatar<A, n, T>(), _BaseAvatar<A, n-1, Ts...>() {}
  _BaseAvatar() = default;

  virtual ~_BaseAvatar() = default;

  void setupEntity(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) {
    A::setupEntity(entity);
    _BaseAvatar<A, n, T>::setupEntity(entity, ids[0]);
#ifdef _WIN32
    std::array<uint64_t, n-1> dest;
    std::copy(std::next(ids.begin()), ids.end(), dest.begin());
    _BaseAvatar<A, n-1, Ts...>::setupEntity(entity, dest.begin());
#else
    typename std::array<uint64_t, n-1>::iterator it = std::next(ids.begin());
    _BaseAvatar<A, n-1, Ts...>::setupEntity(entity, it);
#endif // OS
  }

  constexpr static unsigned size() {
    return n;
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
#ifdef _WIN32
    std::array<uint64_t, m-1> dest;
    std::copy(std::next(idsi), idsi + m, dest.begin());
    _BaseAvatar<A, m-1, Ts...>::setupEntity(entity, dest.begin());
#else
    _BaseAvatar<A, m-1, Ts...>::setupEntity(entity, std::next(idsi));
#endif // OS
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
     _Avatar<n, T>(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, static_cast<void*>(this)),
     v(entity->get<T, std::shared_ptr<zbe::Value<T> > >(id)) {
       setCallback();
     }
 _BaseAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, 1>::iterator idsi)
  : A(entity),
    _Avatar<n, T>(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, static_cast<void*>(this)),
    v(entity->get<T, std::shared_ptr<zbe::Value<T> > >(*idsi)) {
      setCallback();
    }

  virtual ~_BaseAvatar() = default;

  void setupEntity(std::shared_ptr<Entity> entity, uint64_t id) {
    A::setupEntity(entity);
    _Avatar<n, T>::setup(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, static_cast<void*>(this));
    v = entity->get<T, std::shared_ptr<zbe::Value<T> > >(id);
  }

  void setupEntity(std::shared_ptr<Entity> entity, typename std::array<uint64_t, 1>::iterator idsi) {
    A::setupEntity(entity);
    _Avatar<n, T>::setup(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, static_cast<void*>(this));
    v = entity->get<T, std::shared_ptr<zbe::Value<T> > >(*idsi);
  }

  static std::shared_ptr<Value<T> > getImpl(void *instance) {
    //TODO asegurarse de que este casting es en tiempo de compilación (static cast?)
    return (static_cast<_BaseAvatar<A, n, T>*>(instance)->v);
  }

  static void setImpl(void *instance, T value) {
    //TODO asegurarse de que este casting es en tiempo de compilación (static cast?)
    static_cast<_BaseAvatar<A, n, T>*>(instance)->v->set(value);
  }

  constexpr static unsigned size() {
    return 1;
  }

protected:
  void setCallback() {
    _Avatar<n, T>::setup(&_BaseAvatar::getImpl, &_BaseAvatar::setImpl, static_cast<void*>(this));
  }
private:
  std::shared_ptr<Value<T> > v;
};


// --------- DyanmicAvatar

template <typename A, unsigned n, typename T, typename... Ts>
class _DynamicAvatar : virtual public _Avatar<n, T, Ts...>,
                            public _DynamicAvatar<A, n, T>,
                            public _DynamicAvatar<A, n-1, Ts...>  {
public:
  _DynamicAvatar(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) : A(entity), _DynamicAvatar<A, n, T>(entity, ids[0]), _DynamicAvatar<A, n-1, Ts...>(entity, ids.begin()+1) {}

  // _DynamicAvatar() : A(), _DynamicAvatar<A, n, T>(), _DynamicAvatar<A, n-1, Ts...>() {}
  _DynamicAvatar() = default;

  virtual ~_DynamicAvatar() = default;

  void setupEntity(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) {
    A::setupEntity(entity);
    _DynamicAvatar<A, n, T>::setupEntity(entity, ids[0]);
#ifdef _WIN32
    std::array<uint64_t, n-1> dest;
    std::copy(std::next(ids.begin()), ids.end(), dest.begin());
    _DynamicAvatar<A, n-1, Ts...>::setupEntity(entity, dest.begin());
#else
    _DynamicAvatar<A, n-1, Ts...>::setupEntity(entity, std::next(ids.begin()));
#endif // OS
  }

  constexpr static unsigned size() {
    return n;
  }

protected:

  template <unsigned m = n>
  _DynamicAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<(m!=2)>::type * = nullptr) : A(entity), _DynamicAvatar<A, m, T>(entity, *idsi), _DynamicAvatar<A, m-1, Ts...>(entity, idsi+1) {}

  template <unsigned m = n>
  _DynamicAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<!(m!=2), int>::type * = nullptr) : A(entity), _DynamicAvatar<A, m, T>(entity, *idsi), _DynamicAvatar<A, m-1, Ts...>(entity, *(++idsi)) {}

  template <unsigned m = n>
  void setupEntity(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<(m!=2)>::type * = nullptr) {
    A::setupEntity(entity);
    _DynamicAvatar<A, m, T>::setupEntity(entity, *idsi);
#ifdef _WIN32
    std::array<uint64_t, m-1> dest;
    std::copy(std::next(idsi), idsi + m, dest.begin());
    _DynamicAvatar<A, m-1, Ts...>::setupEntity(entity, dest.begin());
#else
    _DynamicAvatar<A, m-1, Ts...>::setupEntity(entity, std::next(idsi));
#endif // OS
  }

  template <unsigned m = n>
  void setupEntity(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<!(m!=2), int>::type * = nullptr) {
    A::setupEntity(entity), _DynamicAvatar<A, m, T>::setupEntity(entity, *idsi);
    _DynamicAvatar<A, m-1, Ts...>::setupEntity(entity, *(++idsi));
  }

};

template <typename A, unsigned n, typename T>
class _DynamicAvatar<A, n, T> : virtual public A, virtual public _Avatar<n, T> {
public:
  _DynamicAvatar() : A(), _Avatar<n, T>(), entity(), id() { setCallback();}
  _DynamicAvatar(std::shared_ptr<Entity> entity, uint64_t id)
   : A(entity),
     _Avatar<n, T>(&_DynamicAvatar::getImpl, &_DynamicAvatar::setImpl, static_cast<void*>(this)),
     entity(entity), id(id) {
       setCallback();
     }
 _DynamicAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, 1>::iterator idsi)
  : A(entity),
    _Avatar<n, T>(&_DynamicAvatar::getImpl, &_DynamicAvatar::setImpl, static_cast<void*>(this)),
    entity(entity), id(idsi[0]) {
      setCallback();
    }

  virtual ~_DynamicAvatar() = default;

  void setupEntity(std::shared_ptr<Entity> entity, uint64_t id) {
    A::setupEntity(entity);
    _Avatar<n, T>::setup(&_DynamicAvatar::getImpl, &_DynamicAvatar::setImpl, static_cast<void*>(this));
    this->entity = entity;
    this->id = id;
  }

  void setupEntity(std::shared_ptr<Entity> entity, typename std::array<uint64_t, 1>::iterator idsi) {
    A::setupEntity(entity);
    _Avatar<n, T>::setup(&_DynamicAvatar::getImpl, &_DynamicAvatar::setImpl, static_cast<void*>(this));
    this->entity = entity;
    this->id = idsi[0];
  }

  static std::shared_ptr<Value<T> > getImpl(void *instance) {
    auto da = static_cast<_DynamicAvatar<A, n, T>*>(instance);
    auto& ent = *(da->entity.get());
    uint64_t id = da->id;
    return (ent.template get<T, std::shared_ptr<zbe::Value<T> >>(id));
  }

  static void setImpl(void *instance, T value) {
    auto da = static_cast<_DynamicAvatar<A, n, T>*>(instance);
    auto& ent = *(da->entity.get());
    uint64_t id = da->id;
    (ent.template get<T, std::shared_ptr<zbe::Value<T> >>(id))->set(value);
  }

  constexpr static unsigned size() {
    return 1;
  }

protected:
  void setCallback() {
    _Avatar<n, T>::setup(&_DynamicAvatar::getImpl, &_DynamicAvatar::setImpl, static_cast<void*>(this));
  }
private:
  std::shared_ptr<Entity> entity;
  uint64_t id;
};

template<typename T, typename... Ts>
using MBaseAvatar = _BaseAvatar<BaseAvatar, sizeof...(Ts)+1, T, Ts...>;

template<typename T>
using SBaseAvatar = _BaseAvatar<BaseAvatar, 1, T>;

template<typename T, typename... Ts>
using MAwareAvatar = _BaseAvatar<AwareAvatar, sizeof...(Ts)+1, T, Ts...>;

template<typename T>
using SAwareAvatar = _BaseAvatar<AwareAvatar, 1, T>;

template<typename T, typename... Ts>
using MDynamicAvatar = _DynamicAvatar<BaseAvatar, sizeof...(Ts)+1, T, Ts...>;

template<typename T>
using SDynamicAvatar = _DynamicAvatar<BaseAvatar, 1, T>;

template<typename T, typename... Ts>
using MDynamicAwareAvatar = _DynamicAvatar<AwareAvatar, sizeof...(Ts)+1, T, Ts...>;

template<typename T>
using SDynamicAwareAvatar = _DynamicAvatar<AwareAvatar, 1, T>;

DISABLE_WARNING_POP()
}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEAVATAR_H_
