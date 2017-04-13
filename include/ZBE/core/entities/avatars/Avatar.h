/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Avatar.h
 * @since 2017-04-12
 * @date 2017-04-12
 * @author Ludo
 * @brief This define an avatar that can be used to deactivate/activate or erase the corresponding entity.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_
#define ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_

#include "ZBE/core/tools/containers/Ticket.h"

namespace zbe {

/** \brief This define an avatar that can be used to deactivate/activate or erase the corresponding entity.
 */
struct Avatar {
    using Base = void;

    /** \brief Change the state of this avatar in the list identified by id to ACTIVE.
     *  \param id Id to identify the list.
     */
    void setACTIVE(uint64_t id);

    /** \brief Change the state of this avatar in the list identified by id to INACTIVE.
     *  \param id Id to identify the list.
     */
    void setINACTIVE(uint64_t id);

    /** \brief Change the state of this avatar in the list identified by id to ACTIVE.
     *  \param id Id to identify the list.
     */
    void setERASED(uint64_t id);

    /** \brief Change the state of this avatar for all list to ACTIVE.
     */
    void setACTIVE();

    /** \brief Change the state of this avatar for all list to INACTIVE.
     */
    void setINACTIVE();

    /** \brief Change the state of this avatar for all list to ERASED.
     */
    void setERASED();

};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_
