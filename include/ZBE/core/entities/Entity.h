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
#include <string>
#include <unordered_map>
#include <vector>

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/time/ContextTime.h"

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the basic functionality of every entity.
 */
class ZBEAPI Entity {
  public:
    /** \brief Empty constructor.
     */
    Entity() : tl(), cTime(SysTime::getInstance()), dv(), fv(), uv(), iv(), bv(), v3v(), v2v(), sv(), svv() {}

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

    /** \brief Changes the state of this entity in the list identified by id to ACTIVE.
     *  \param id Id to identify the list.
     */
    void setACTIVE(uint64_t id);

    /** \brief Changes the state of this entity in the list identified by id to INACTIVE.
     *  \param id Id to identify the list.
     */
    void setINACTIVE(uint64_t id);

    /** \brief Changes the state of this entity in the list identified by id to ACTIVE.
     *  \param id Id to identify the list.
     */
    void setERASED(uint64_t id);

    /** \brief Changes the state of this entity for all lists to ERASED.
     *  \param id Id to identify the list.
     */
    void setACTIVE();

    /** \brief Changes the state of this entity for all lists to INACTIVE.
     */
    void setINACTIVE();

    /** \brief Changes the state of this entity for all lists to ERASED.
     */
    void setERASED();

    /** \brief Changes the contextTime of this entity to the value of cTime.
     *  \param cTime Value to put in the Entity's cTime
     */
    void setContextTime(std::shared_ptr<ContextTime> cTime);

    /** \brief Returns the context time of the Entity.
     */
    std::shared_ptr<ContextTime> getContextTime();

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

    /** \brief Sets a Value<int64_t> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<int64_t> to be set.
     *  \sa getInt, setUint, setDouble, setFloat
     */
    void setBool(uint64_t id, std::shared_ptr<Value<bool> > val);
    template<typename T>
    typename std::enable_if<std::is_same<bool, T>::value, void>::type
    set(uint64_t id, std::shared_ptr<Value<T> > val) {setBool(id, val);}

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

    /** \brief Sets a Value<Vector2D> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<Vector2D> to be set.
     *  \sa getInt, setUint, setDouble, setFloat
     */
    void setVector2D(uint64_t id, std::shared_ptr<Value<Vector2D> > val);
    template<typename T>
    typename std::enable_if<std::is_same<Vector2D, T>::value, void>::type
    set(uint64_t id, std::shared_ptr<Value<T> > val) {setVector2D(id, val);}

    /** \brief Sets a Value<Vector2D> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<Vector2D> to be set.
     *  \sa getInt, setUint, setDouble, setFloat
     */
    void setString(uint64_t id, std::shared_ptr<Value<std::string> > val);
    template<typename T>
    typename std::enable_if<std::is_same<std::string, T>::value, void>::type
    set(uint64_t id, std::shared_ptr<Value<T> > val) {setString(id, val);}

    /** \brief Sets a Value<std::vector<std::string> > at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<std::vector<std::string> > to be set.
     *  \sa getInt, setUint, setDouble, setFloat, setString
     */
    void setStringVector(uint64_t id, std::shared_ptr<Value<std::vector<std::string> > > val);
    template<typename T>
    typename std::enable_if<std::is_same<std::vector<std::string> , T>::value, void>::type
    set(uint64_t id, std::shared_ptr<Value<T> > val) {setStringVector(id, val);}

    /** \brief Returns the Value<double> associated the identifier id.
     *  \param id identifier
     *  \return Value<double>.
     *  \sa setDouble, getFloat, getUint, getInt
     */
    std::shared_ptr<Value<double> > getDouble(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, double>::value && std::is_same<U, std::shared_ptr<Value<T> > >::value, U>::type
    get(uint64_t id) {return getDouble(id);}

    /** \brief Returns the Value<uint64_t> associated the identifier id.
     *  \param id identifier
     *  \return Value<uint64_t>.
     *  \sa setUint, getInt, getDouble, getFloat
     */
    std::shared_ptr<Value<uint64_t> > getUint(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, uint64_t>::value && std::is_same<U, std::shared_ptr<Value<T> > >::value, U>::type
    get(uint64_t id) {return getUint(id);}

    /** \brief Returns the Value<int64_t> associated the identifier id.
     *  \param id identifier
     *  \return Value<int64_t>.
     *  \sa setInt, getUint, getDouble, getFloat
     */
    std::shared_ptr<Value<int64_t> > getInt(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, int64_t>::value && std::is_same<U, std::shared_ptr<Value<T> >>::value, U>::type
    get(uint64_t id) {return getInt(id);}

    /** \brief Returns the Value<float> associated the identifier id.
     *  \param id identifier
     *  \return Value<float>.
     *  \sa setFloat, getDouble, getUint, getInt
     */
    std::shared_ptr<Value<float> > getFloat(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, float>::value && std::is_same<U, std::shared_ptr<Value<T> > >::value, U>::type
    get(uint64_t id) {return getFloat(id);}

    /** \brief Returns the Value<bool> associated the identifier id.
     *  \param id identifier
     *  \return Value<bool>.
     *  \sa setFloat, getDouble, getUint, getInt
     */
    std::shared_ptr<Value<bool> > getBool(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, bool>::value && std::is_same<U, std::shared_ptr<Value<T> > >::value, U>::type
    get(uint64_t id) {return getBool(id);}

    /** \brief Returns the Value<Vector3D> associated the identifier id.
     *  \param id identifier
     *  \return Value<Vector3D>.
     *  \sa setFloat, getDouble, getUint, getInt
     */
    std::shared_ptr<Value<Vector3D> > getVector3D(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, Vector3D>::value && std::is_same<U, std::shared_ptr<Value<T> > >::value, U>::type
    get(uint64_t id) {return getVector3D(id);}

    /** \brief Returns the Value<Vector2D> associated the identifier id.
     *  \param id identifier
     *  \return Value<Vector2D>.
     *  \sa setFloat, getDouble, getUint, getInt
     */
    std::shared_ptr<Value<Vector2D> > getVector2D(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, Vector2D>::value && std::is_same<U, std::shared_ptr<Value<T> > >::value, U>::type
    get(uint64_t id) {return getVector2D(id);}

    /** \brief Returns the Value<std::string> associated the identifier id.
     *  \param id identifier
     *  \return Value<std::string>.
     *  \sa setFloat, getDouble, getUint, getInt
     */
    std::shared_ptr<Value<std::string> > getString(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, std::string>::value && std::is_same<U, std::shared_ptr<Value<T> > >::value, U>::type
    get(uint64_t id) {return getString(id);}

    /** \brief Returns the Value<std::vector<std::string> > associated the identifier id.
     *  \param id identifier
     *  \return Value<std::vector<std::string> >.
     *  \sa setFloat, getDouble, getUint, getInt, getString
     */
    std::shared_ptr<Value<std::vector<std::string> > > getStringVector(uint64_t id);
    template<typename T, typename U>
    typename std::enable_if<std::is_same<T, std::vector<std::string> >::value && std::is_same<U, std::shared_ptr<Value<T> > >::value, U>::type
    get(uint64_t id) {return getStringVector(id);}

  private:
    std::unordered_map<uint64_t, std::shared_ptr<Ticket> > tl;

    /* WARNING */
    /* If you are going to add more attribs here, look for a way to make it generic */
    /* We have already tried it ... good luck */

    std::shared_ptr<ContextTime> cTime;

    std::unordered_map<uint64_t, std::shared_ptr<Value<double> > > dv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<float> > > fv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<uint64_t> > > uv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<int64_t> > > iv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<bool> > > bv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<Vector3D> > > v3v;
    std::unordered_map<uint64_t, std::shared_ptr<Value<Vector2D> > > v2v;
    std::unordered_map<uint64_t, std::shared_ptr<Value<std::string> > > sv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<std::vector<std::string> > > > svv;
};

template<unsigned n>
struct EntityIds {
 EntityIds(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) : e(entity), ids(ids) {}

 std::shared_ptr<Entity> e;
 std::array<uint64_t, n> ids;
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_ENTITY_H_
