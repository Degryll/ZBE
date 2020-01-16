/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Avatar.h
 * @since 2017-04-12
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief This define an avatar that can be used to deactivate/activate or erase the corresponding entity.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_
#define ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be used to deactivate/activate or erase the corresponding entity.
 */
class Avatar {
public:
    using Base = void; //!< Inheritance info.

    /** \brief Virtual destructor.
     */
    virtual ~Avatar() {}

    /** \brief Register a new Ticket.
     *  \param id Id to identify the ticket origin.
     *  \param ticket The ticket to be stored.
     */
    virtual void addTicket(uint64_t id, std::shared_ptr<Ticket> ticket) = 0;

    /** \brief Register a new Ticket, if there is a ticket on the id, will be replaced.
     *  \param id Id to identify the ticket origin.
     *  \param ticket The ticket to be stored.
     */
    virtual void replaceTicket(uint64_t id, std::shared_ptr<Ticket> ticket) = 0;

    /** \brief Change the state of this avatar in the list identified by id to ACTIVE.
     *  \param id Id to identify the list.
     */
    virtual void setACTIVE(uint64_t id) = 0;

    /** \brief Change the state of this avatar in the list identified by id to INACTIVE.
     *  \param id Id to identify the list.
     */
    virtual void setINACTIVE(uint64_t id) = 0;

    /** \brief Change the state of this avatar in the list identified by id to ACTIVE.
     *  \param id Id to identify the list.
     */
    virtual void setERASED(uint64_t id) = 0;

    /** \brief Change the state of this avatar for all list to ACTIVE.
     */
    virtual void setACTIVE() = 0;

    /** \brief Change the state of this avatar for all list to INACTIVE.
     */
    virtual void setINACTIVE() = 0;

    /** \brief Change the state of this avatar for all list to ERASED.
     */
    virtual void setERASED() = 0;
};

template <unsigned n, typename T, typename... Ts>
class _Avatar : virtual public _Avatar<n, T>, virtual public _Avatar<n-1, Ts...> {
public:
  using Base = _Avatar<n+1, Ts...>;
  //_Avatar() : _Avatar<n, T>(nullptr, nullptr) {}
  virtual ~_Avatar() {}

  template <unsigned m, typename U>
  std::shared_ptr<Value<U> > get() {
    return (this->_Avatar<m, U>::get());
  }
};

template <unsigned n, typename T>
class _Avatar<n, T> : virtual public Avatar {
public:
  using Base = Avatar;
  _Avatar(const _Avatar&) = delete;
  void operator=(const _Avatar&) = delete;

  virtual ~_Avatar() {}

  template <unsigned m = n, typename U = T>
  std::shared_ptr<Value<U> > get() {
   return ((*subGetter)(instance));
  }

protected:
  using SubGetter = std::shared_ptr<Value<T> > (*)(void*);
  void setup(SubGetter subGetter, void *instance) {
    this->subGetter = subGetter;
    this->instance = instance;
  }
  //_Avatar() = delete;
   _Avatar() : subGetter(nullptr), instance(nullptr) {}
  //   static_assert(false, "_Avatar empty constructor called.");
  // }
  _Avatar(SubGetter subGetter, void *instance) : subGetter(subGetter), instance(instance) {}
  SubGetter subGetter;
  void *instance;
};

template<typename T, typename... Ts>
using MAvatar = _Avatar<sizeof...(Ts)+1, T, Ts...>;

template<typename T>
using SAvatar = _Avatar<1, T>;

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_
