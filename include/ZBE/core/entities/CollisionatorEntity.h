/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionatorEntity.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Degryll
 * @brief Define the basic functionality of every Collisionable entity.
 */

#ifndef CORE_ENTITIES_COLLISIONATORENTITY_H_
#define CORE_ENTITIES_COLLISIONATORENTITY_H_

#include <cstdint>
#include <forward_list>

#include "ZBE/core/entities/CollisionerEntity.h"

namespace zbe {

/** \brief Define the basic functionality of every Collisionable entity.
 */
class CollisionatorEntity : public CollisionerEntity {
  public:
    /** \brief Register a new list of collisionables.
     *  \param id Internal id to identify the list.
     *  \param listId Global id of the List.
     */
    inline void addToCollisionablesList(uint64_t id) {cl.push_front(id);}

    /** \brief Remove a list of collisionables.
     *  \param id Internal id to identify the list to be removed.
     */
    inline void removeFromCollisionablesList(uint64_t id) {cl.remove(id);}

    /** \brief Returns the global id of the list of Collisionable identify by the Internal id.
     *  \param id Internal id to identify the list.
     *  \return The global id of the list.
     */
    inline const std::forward_list<uint64_t>& getCollisionablesList() {return (cl);}

    /** \brief Register a new list of Actuators.
     *  \param id Internal id to identify the list.
     *  \param listId Global id of the List.
     */
    void addToActuatorsList(uint64_t id, uint64_t listId);

    /** \brief Remove a list of Actuators.
     *  \param id Internal id to identify the list to be removed.
     */
    void removeFromActuatorsList(uint64_t id);

    /** \brief Returns the global id of the list of Actuators identify by the Internal id.
     *  \param id Internal id to identify the list.
     *  \return The global id of the list.
     */
    uint64_t getActuatorsList(uint64_t id);

  private:
    std::forward_list<uint64_t> cl;  //!< Container that identify id with list of collisionables
    //std::map<uint64_t, uint64_t> cl;  //!< Container that identify id with list of collisionables
    std::map<uint64_t, uint64_t> al;  //!< Container that identify id with list of actuators

};

}  // namespace zbe

#endif  // CORE_ENTITIES_COLLISIONATORENTITY_H_
