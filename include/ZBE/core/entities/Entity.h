/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Entity.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Degryll
 * @brief Define the basic functionality of every entity.
 */

#ifndef CORE_ENTITIES_ENTITY_H_
#define CORE_ENTITIES_ENTITY_H_

#include <map>
#include "ZBE/core/tools/containers/Ticket.h"

namespace zbe {

/** \brief Define the basic functionality of every entity.
 */
class Entity {
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
    void addToList(uint64_t id, Ticket *ticket);

    /** \brief Change the state of this entity in the list identified by id.
     *  \param id Id to identify the list.
     *  \param state New state of the entity in the list.
     */
    void setState(uint64_t id, zbe::Ticket::State state);

  private:
    std::map<uint64_t, Ticket*> tl;  //!< Container that identify id with tickets
};

}  // namespace zbe

#endif  // CORE_ENTITIES_ENTITY_H_
