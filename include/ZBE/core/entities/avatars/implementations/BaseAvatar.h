/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Avatar.h
 * @since 2017-04-12
 * @date 2018-02-25
 * @author Ludo Batis Degryll
 * @brief Base implementation of avatar that uses an Entity.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEAVATAR_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEAVATAR_H_

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {


/** \brief Base implementation of avatar that uses an Entity.
 */
struct BaseAvatar : virtual public Avatar {

    BaseAvatar(const BaseAvatar&) = delete; //!< Avoid copy.
    void operator=(const BaseAvatar&) = delete; //!< Avoid copy.

    BaseAvatar(std::shared_ptr<Entity> entity): e(entity) {}

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

  private:
    std::shared_ptr<Entity> e;
};

template <unsigned n, typename T, typename... Ts>
class _BaseAvatar : virtual public _Avatar<n, T, Ts...>,
                    virtual public BaseAvatar,
                            public _BaseAvatar<n, T>,
                            public _BaseAvatar<n-1, Ts...>  {
public:
  _BaseAvatar(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) : BaseAvatar(entity), _BaseAvatar<n, T>(entity, ids[0]), _BaseAvatar<n-1, Ts...>(entity, ids.begin()+1) {
     //_BaseAvatar<n, T>::setup();
  }

//  _BaseAvatar(std::shared_ptr<Entity> entity, std::initializer_list<int> il,
//              typename std::enable_if<(il.size() == (sizeof...(Ts)+1)), int>::type * = nullptr)
//   : _BaseAvatar(entity, *(il.begin())), _BaseAvatar(entity, (il.begin()+1)) {}
//
//
//  _BaseAvatar(std::shared_ptr<Entity> entity, std::initializer_list<int> il, typename std::enable_if<(il.size() != (sizeof...(Ts)+1)), int>::type * = nullptr)
//    {static_assert(true, "Initializer list must have the same number of elements as types in BaseAvatar.");}

  virtual ~_BaseAvatar() {}

protected:
  template <unsigned m = n>
  _BaseAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<(m!=2)>::type * = nullptr) : BaseAvatar(entity), _BaseAvatar<m, T>(entity, *idsi), _BaseAvatar<m-1, Ts...>(entity, idsi+1) {
     //_BaseAvatar<m, T>::setup();
  }

  template <unsigned m = n>
  _BaseAvatar(std::shared_ptr<Entity> entity, typename std::array<uint64_t, m>::iterator idsi, typename std::enable_if<!(m!=2), int>::type * = nullptr) : BaseAvatar(entity), _BaseAvatar<m, T>(entity, *idsi), _BaseAvatar<m-1, Ts...>(entity, *(++idsi)) {
     //_BaseAvatar<m, T>::setup();
  }

//  _BaseAvatar(std::shared_ptr<Entity> entity, std::initializer_list<int>::iterator ili, typename std::enable_if<(sizeof...(Ts)!=0), int>::type * = nullptr) : _BaseAvatar(entity, *ili), _BaseAvatar(entity, (ili+1)) {}
//  _BaseAvatar(std::shared_ptr<Entity> entity, std::initializer_list<int>::iterator ili, typename std::enable_if<(sizeof...(Ts)==0), int>::type * = nullptr) : _BaseAvatar(entity, *ili) {}
};

template <unsigned n, typename T>
class _BaseAvatar<n, T> : virtual public BaseAvatar, virtual public _Avatar<n, T> {
public:
  _BaseAvatar(std::shared_ptr<Entity> entity, uint64_t id)
   : BaseAvatar(entity),
     _Avatar<n, T>(&_BaseAvatar::getImpl, (void*)this),
     v(entity->get<T, std::shared_ptr<zbe::Value<T> > >(id)) {
       setup();
     }

  virtual ~_BaseAvatar() {}

  static std::shared_ptr<Value<T> > getImpl(void *instance) {
    return (((_BaseAvatar<n, T>*)instance)->v);
  }

protected:
  void setup() {
    _Avatar<n, T>::setup(&_BaseAvatar::getImpl, (void*)this);
  }
private:
  std::shared_ptr<Value<T> > v;
};

template<typename T, typename... Ts>
using MBaseAvatar = MAvatar<T, Ts...>;

template<typename T>
using SBaseAvatar = SAvatar<T>;

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEAVATAR_H_
