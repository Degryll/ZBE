/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EntityWithAttribs.h
 * @since 2016-03-26
 * @date 2016-08-04
 * @author Ludo
 * @brief An entity with associated attributes and flags.
 */

#ifndef CORE_ENTITIES_ENTITYWITHATTRIBS_H_
#define CORE_ENTITIES_ENTITYWITHATTRIBS_H_

#include "ZBE/core/entities/Entity.h"

namespace zbe {


/** \brief An entity with associated attributes and flags.
 */
class EntityWithAttribs : public Entity {
  public:

    /** \brief Empty constructor.
      */
    EntityWithAttribs(){}

    /** \brief Empty destructor.
      */
    virtual ~EntityWithAttribs() {}

    void operator=(const CollisionerEntity&) = delete;

    /** \brief Set the collision object this entity is.
     *  \param object The collision object.
     */
    inline void setCollisionObject(CollisionObject* object) {o = object;}

    /** \brief Return the collision object.
     *  \return Collision object.
     */
    inline CollisionObject* getCollisionObject() {return (o);}

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
    CollisionObject* o;  //!< Collision object
    std::map<uint64_t, uint64_t> al;  //!< Container that identify id with list of actuators

};

}  // namespace zbe

#endif  // CORE_ENTITIES_ENTITYWITHATTRIBS_H_
