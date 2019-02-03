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

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This define an avatar that can be used to deactivate/activate or erase the corresponding entity.
 */
struct Avatar {

    using Base = void; //!< Inheritance info.

    /** \brief Virtual destructor.
     */
    virtual ~Avatar(){}

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

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_
