/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Avatar.h
 * @since 2017-04-12
 * @date 2017-04-12
 * @author Ludo
 * @brief Base implementation of avatar that uses an Entity.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_
#define ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"

namespace zbe {

/** \brief Base implementation of avatar that uses an Entity.
 */
struct BaseAvatar : public Avatar{

    BaseAvatar(Entity * entity): e(entity) {}

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

#endif  // ZBE_CORE_ENTITIES_AVATARS_AVATAR_H_
