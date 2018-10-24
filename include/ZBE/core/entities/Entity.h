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
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Define the basic functionality of every entity.
 */
class ZBEAPI Entity : virtual public Avatar {
  public:
    /** \brief Empty constructor.
      */
    Entity() : tl(), dv(), fv(), uv(), iv() {}
    /** \brief The destructor make sure the entity is marked as ERASED in every Ticket.
      */
    virtual ~Entity();

    /** \brief Register a new Ticket from a list.
     *  \param id Id to identify the list.
     *  \param ticket The ticket to be stored.
     */
    void addToList(uint64_t id, std::shared_ptr<Ticket> ticket);

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

    /** \brief Sets a Value<float> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<float> to be set.
     *  \sa getFloat, setDouble, setUint, setInt
     */
    void setFloat(uint64_t id, std::shared_ptr<Value<float> > val);

    /** \brief Sets a Value<uint64_t> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<uint64_t> to be set.
     *  \sa getUint, setInt, setDouble, setFloat
     */
    void setUint(uint64_t id, std::shared_ptr<Value<uint64_t> > val);

    /** \brief Sets a Value<int64_t> at identifier id.
     * This method should be called only once per id.
     *  \param id identifier
     *  \param val Value<int64_t> to be set.
     *  \sa getInt, setUint, setDouble, setFloat
     */
    void setInt(uint64_t id, std::shared_ptr<Value<int64_t> > val);

    /** \brief Returns the Value<double> associated the identifier id.
     *  \param id identifier
     *  \return Value<double>.
     *  \sa setDouble, getFloat, getUint, getInt
     */
    std::shared_ptr<Value<double> > getDouble(uint64_t id);

    /** \brief Returns the Value<uint64_t> associated the identifier id.
     *  \param id identifier
     *  \return Value<uint64_t>.
     *  \sa setUint, getInt, getDouble, getFloat
     */
    std::shared_ptr<Value<uint64_t> > getUint(uint64_t id);

    /** \brief Returns the Value<int64_t> associated the identifier id.
     *  \param id identifier
     *  \return Value<int64_t>.
     *  \sa setInt, getUint, getDouble, getFloat
     */
    std::shared_ptr<Value<int64_t> > getInt(uint64_t id);

    /** \brief Returns the Value<float> associated the identifier id.
     *  \param id identifier
     *  \return Value<float>.
     *  \sa setFloat, getDouble, getUint, getInt
     */
    std::shared_ptr<Value<float> > getFloat(uint64_t id);

  private:

    std::unordered_map<uint64_t, std::shared_ptr<Ticket> > tl;

    std::unordered_map<uint64_t, std::shared_ptr<Value<double> > > dv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<float> > > fv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<uint64_t> > > uv;
    std::unordered_map<uint64_t, std::shared_ptr<Value<int64_t> > > iv;
};

template<unsigned n>
struct EntityIds {
 EntityIds(std::shared_ptr<Entity> entity, std::array<uint64_t, n> ids) : e(entity), ids(ids) {}

 std::shared_ptr<Entity> e;
 std::array<uint64_t, n> ids;
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_ENTITY_H_
