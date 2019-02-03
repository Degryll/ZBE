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

    BaseAvatar(Entity * entity): e(entity) {}

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
    Entity * e;
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEAVATAR_H_
