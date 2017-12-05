/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Entity.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Degryll
 * @brief Define the basic functionality of every entity.
 */

#ifndef ZBE_CORE_ENTITIES_ENTITY_H_
#define ZBE_CORE_ENTITIES_ENTITY_H_

#include <memory>
#include <map>

#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/entities/avatars/Avatar.h"

namespace zbe {

/** \brief Define the basic functionality of every entity.
 */
class Entity : virtual public Avatar {
  public:
    /** \brief Empty constructor.
      */
    Entity() : tl() {}
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

  private:
    inline void _setState(zbe::Ticket::State state);
    inline void _setState(uint64_t id, zbe::Ticket::State state);
    std::map<uint64_t, std::shared_ptr<Ticket> > tl;  //!< Container that identify id with tickets
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_ENTITY_H_
