/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Collisionator.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Degryll
 * @brief Defines a Collisioner that collide with others Collisioner.
 */

#ifndef CORE_ENTITIES_AVATARS_COLLISIONATOR_H_
#define CORE_ENTITIES_AVATARS_COLLISIONATOR_H_

#include <cstdint>
#include <forward_list>

#include "ZBE/core/entities/avatars/Collisioner.h"

namespace zbe {

/** \brief Define the basic functionality of every Collisionable entity.
 */
template <typename R>
class Collisionator : public Collisioner<R> {
  public:
    Collisionator(CollisionObject<R>* object) : Collisioner<R>(object), cl() {}

    virtual ~Collisionator(){};

    /** \brief Register a new list of collisionables.
     *  \param id Internal id to identify the list.
     *  \param listId Global id of the List.
     */
    inline void addToCollisionablesLists(uint64_t id) { cl.push_front(id); }

    /** \brief Remove a list of collisionables.
     *  \param id Internal id to identify the list to be removed.
     */
    inline void removeFromCollisionablesLists(uint64_t id) { cl.remove(id); }  // TODO not has efficient has one may expect.

    /** \brief Returns the global id of the list of Collisionable identify by the Internal id.
     *  \param id Internal id to identify the list.
     *  \return The global id of the list.
     */
    inline const std::forward_list<uint64_t>& getCollisionablesLists() { return (cl); }

  private:
    std::forward_list<uint64_t> cl;  //!< Container with ids of list of collisionables

};

}  // namespace zbe

#endif  // CORE_ENTITIES_AVATARS_COLLISIONATOR_H_
