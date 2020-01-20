/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Entity.h
 * @since 2016-03-24
 * @date 2018-03-06
 * @author Degryll
 * @brief Define the basic functionality of every entity.
 */

#ifndef ZBE_CORE_ENTITIES_ENTITY_H_
#define ZBE_CORE_ENTITIES_ENTITY_H_

#include <cstdint>
#include <memory>
#include <array>
#include <unordered_map>

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the basic functionality of every entity.
 */
class ZBEAPI Entity {
  public:
    /** \brief Empty constructor.
      */
    Entity() : tl(), dv(), fv(), uv(), iv(), v3v() {}
    /** \brief The destructor make sure the entity is marked as ERASED in every Ticket.
      */
    virtual ~Entity();

    /** \brief Register a new Ticket from a list.
     *  \param id Id to identify the list.
     *  \param ticket The ticket to be stored.
     */
    void addTicket(uint64_t id, std::shared_ptr<Ticket> ticket);

    /** \brief Register a new Ticket, if there is a ticket on the id, will be replaced.
     *  \param id Id to identify the ticket origin.
     *  \param ticket The ticket to be stored.
     */
    void replaceTicket(uint64_t id, std::shared_ptr<Ticket> ticket);

    /** \brief Change the state of this entity in the list identified by id to ACTIVE.
     *  \param id Id to identify the list.
     */
    void setACTIVE(uint64_t id);

    /** \brief Change the state of this entity in the list identified by id to INACTIVE.
     *  \param id Id to identify the list.
     */
    void setINACTIVE(uint64_t id);

    /** \brief Change the state of this entity in the list identified by id to ACTIVE.
     *  \param id Id to identify the list.
     */
    void setERASED(uint64_t id);

    /** \brief Change the state of this entity for all list to ACTIVE.
     */
    void setACTIVE();

    /** \brief Change the state of this entity for all list to INACTIVE.
     */
    void setINACTIVE();

    /** \brief Change the state of this entity for all list to ERASED.
     */
    void setERASED();

    /** \brief Sets a Value<double> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<double> to be set.
     *  \sa getDobule, setFloat, setUint, setInt
     */
     void setDouble(uint64_t id, std::shared_ptr<Value<double> > val);
     template<typename T>
     typename std::enable_if<std::is_same<double, T>::value, void>::type
     set(uint64_t id, std::shared_ptr<Value<T> > val) {setDouble(id, val);}

    /** \brief Sets a Value<float> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<float> to be set.
     *  \sa getFloat, setDouble, setUint, setInt
     */
     void setFloat(uint64_t id, std::shared_ptr<Value<float> > val);
     template<typename T>
     typename std::enable_if<std::is_same<float, T>::value, void>::type
     set(uint64_t id, std::shared_ptr<Value<T> > val) {setFloat(id, val);}

    /** \brief Sets a Value<uint64_t> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<uint64_t> to be set.
     *  \sa getUint, setInt, setDouble, setFloat
     */
     void setUint(uint64_t id, std::shared_ptr<Value<uint64_t> > val);
     template<typename T>
     typename std::enable_if<std::is_same<uint64_t, T>::value, void>::type
     set(uint64_t id, std::shared_ptr<Value<T> > val) {setUint(id, val);}

    /** \brief Sets a Value<int64_t> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<int64_t> to be set.
     *  \sa getInt, setUint, setDouble, setFloat
     */
    void setInt(uint64_t id, std::shared_ptr<Value<int64_t> > val);
    template<typename T>
    typename std::enable_if<std::is_same<int64_t, T>::value, void>::type
    set(uint64_t id, std::shared_ptr<Value<T> > val) {setInt(id, val);}

    /** \brief Sets a Value<Vector3D> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<Vector3D> to be set.
     *  \sa getInt, setUint, setDouble, setFloat
     */
    void setVector3D(uint64_t id, std::shared_ptr<Value<Vector3D> > val);
    template<typename T>
    typename std::enable_if<std::is_same<Vector3D, T>::value, void>::type
    set(uint64_t id, std::shared_ptr<Value<T> > val) {setVector3D(id, val);}

    /** \brief Returns the Value<double> associated the identifier id.
     *  \param id identifier
     *  \return Value<double>.
     *  \sa setDouble, getFloat, getUint, getInt
     */
    std::shared_ptr<Value<double> > getDouble(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, double>::value && std::is_same<U, std::shared_ptr<Value<T> >>::value, U>::type
    get(uint64_t id) {return getDouble(id);}

    /** \brief Returns the Value<uint64_t> associated the identifier id.
     *  \param id identifier
     *  \return Value<uint64_t>.
     *  \sa setUint, getInt, getDouble, getFloat
     */
     std::shared_ptr<Value<uint64_t> > getUint(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, uint64_t>::value && std::is_same<U, std::shared_ptr<Value<T> >>::value, U>::type
    get(uint64_t id) {return getUint(id);}
//     template<typename T>
//     typename std::enable_if<std::is_same<uint64_t, T>::value, std::shared_ptr<Value<T> > >::value
//     get(uint64_t id) {return getUint(id);}

    /** \brief Returns the Value<int64_t> associated the identifier id.
     *  \param id identifier
     *  \return Value<int64_t>.
     *  \sa setInt, getUint, getDouble, getFloat
     */
    std::shared_ptr<Value<int64_t> > getInt(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, int64_t>::value && std::is_same<U, std::shared_ptr<Value<T> >>::value, U>::type
    get(uint64_t id) {return getInt(id);}
//     template<typename T>
//     typename std::enable_if<std::is_same<int64_t, T>::value, std::shared_ptr<Value<T> > >::value
//     get(uint64_t id) {return getInt(id);}

    /** \brief Returns the Value<float> associated the identifier id.
     *  \param id identifier
     *  \return Value<float>.
     *  \sa setFloat, getDouble, getUint, getInt
     */
    std::shared_ptr<Value<float> > getFloat(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, float>::value && std::is_same<U, std::shared_ptr<Value<T> >>::value, U>::type
    get(uint64_t id) {return getFloat(id);}
//    template<typename T>
//    typename std::enable_if<std::is_same<float, T>::value, std::shared_ptr<Value<T> > >::value
//    get(uint64_t id) {return getFloat(id);}

    /** \brief Returns the Value<Vector3D> associated the identifier id.
     *  \param id identifier
     *  \return Value<Vector3D>.
     *  \sa setFloat, getDouble, getUint, getInt
     */
    std::shared_ptr<Value<Vector3D> > getVector3D(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, Vector3D>::value && std::is_same<U, std::shared_ptr<Value<T> >>::value, U>::type
    get(uint64_t id) {return getVector3D(id);}
//    template<typename T>
//    typename std::enable_if<std::is_same<Vector3D, T>::value, std::shared_ptr<Value<T> > >::value
//    get(uint64_t id) {return getVector3D(id);}

  private:
    std::unordered_map<uint64_t, std::shared_ptr<Ticket> > tl;

    /* WARNING */
    /* If you are going to add more attribs here, look for a way to make it generic */
    /* We have already tried it ... good luck */

    std::unordered_map<uint64_t, std::shared_ptr<Value<double> > > dv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<float> > > fv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<uint64_t> > > uv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<int64_t> > > iv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<Vector3D> > > v3v;
};

template<unsigned n>
struct EntityIds {
 EntityIds(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) : e(entity), ids(ids) {}

 std::shared_ptr<Entity> e;
 std::array<uint64_t, n> ids;
};

class _Entity2;

template <typename T, typename... Ts>
class _Entity : public _Entity<T>, public _Entity<Ts...> {
public:
  _Entity() : _Entity2(this) {}

  template <typename U>
  void set(uint64_t id, std::shared_ptr<Value<U> > val) {
    this->_Entity<U>::set(id, val);
  }

  template <typename U>
  std::shared_ptr<Value<U> > get(uint64_t id) {
    return (this->_Entity<U>::get(id));
  }
};

/*****************************/
/** \brief Define the basic functionality of every entity.
 */
class ZBEAPI _Entity2 {
public:
//  /** \brief Empty constructor.
//    */
//  _Entity2() : tl() {}

  _Entity2(const _Entity2&) = delete;
  void operator=(const _Entity2&) = delete;

  /** \brief The destructor make sure the entity is marked as ERASED in every Ticket.
    */
  virtual ~_Entity2();

  /** \brief Register a new Ticket from a list.
   *  \param id Id to identify the list.
   *  \param ticket The ticket to be stored.
   */
  void addTicket(uint64_t id, std::shared_ptr<Ticket> ticket);

  /** \brief Register a new Ticket, if there is a ticket on the id, will be replaced.
   *  \param id Id to identify the ticket origin.
   *  \param ticket The ticket to be stored.
   */
  void replaceTicket(uint64_t id, std::shared_ptr<Ticket> ticket);

  /** \brief Change the state of this entity in the list identified by id to ACTIVE.
   *  \param id Id to identify the list.
   */
  void setACTIVE(uint64_t id);

  /** \brief Change the state of this entity in the list identified by id to INACTIVE.
   *  \param id Id to identify the list.
   */
  void setINACTIVE(uint64_t id);

  /** \brief Change the state of this entity in the list identified by id to ACTIVE.
   *  \param id Id to identify the list.
   */
  void setERASED(uint64_t id);

  /** \brief Change the state of this entity for all list to ACTIVE.
   */
  void setACTIVE();

  /** \brief Change the state of this entity for all list to INACTIVE.
   */
  void setINACTIVE();

  /** \brief Change the state of this entity for all list to ERASED.
   */
  void setERASED();


//  template<typename T>
//  void set(uint64_t id, std::shared_ptr<Value<T> > val) {
//    ((_Entity<T>*)instance)->set(id, val);
//  }

  /** \brief Returns the Value<double> associated the identifier id.
     *  \param id identifier
     *  \return Value<double>.
     *  \sa setDouble, getFloat, getUint, getInt
     */
    //std::shared_ptr<Value<double> > getDouble(uint64_t id);
//    template<typename T, typename U>
//    typename std::enable_if<std::is_same<T, double>::value && std::is_same<U, std::shared_ptr<Value<T> >>::value, U>::type
//    get(uint64_t id) {return getDouble(id);}
//    template<typename T>
//    std::shared_ptr<Value<T> > get(uint64_t id) {
//      return (((_Entity<T>*)instance)->get(id));
//    }

    template<typename T>
    std::shared_ptr<Value<T> > get(uint64_t id) {return (((_Entity<T>*)instance)->_Entity<T>::get(id));}

protected:
  _Entity2(void *instance) : tl(), instance(instance) {}
//  void setup(void *instance) {
//    this->instance = instance;
//  }

private:
  std::unordered_map<uint64_t, std::shared_ptr<Ticket> > tl;
  void *instance;
};

template <typename T>
class _Entity<T> : virtual public _Entity2 {
public:
  _Entity() : _Entity2(this), v() {}

  template <typename U = T>
  std::shared_ptr<Value<U> > get(uint64_t id) {
    auto it = v.find(id);
    if (it == v.end()) {
      SysError::setError("Entity has no double value at given index " +  std::to_string(id) + ".");
      return (std::shared_ptr<Value<U> >());
    } else {
      return (v[id]);
    }
  }

  template <typename U = T>
  void set(uint64_t id, std::shared_ptr<Value<U> > val) {
  auto it = v.find(id);
  if (it != v.end()) {
    SysError::setError("Overriding entity int value not allowed.");
  } else {
    v[id] = val;
  }
}


private:
  std::unordered_map<uint64_t, std::shared_ptr<Value<T> > > v;
};

//template <typename T, typename ...Ts>
//class Entity2 : public Entity2<T>, public Entity2<Ts...> {
//};
//
//template <typename T>
//class Entity2<T> : virtual public _Entity<T>, public _Entity2 {
//  template <typename U = T>
//  std::shared_ptr<Value<U> > get(uint64_t id) {return _Entity<U>::v[id];}
//};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_ENTITY_H_
