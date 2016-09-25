/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollsionerEntity.h
 * @since 2016-03-26
 * @date 2016-08-04
 * @author Degryll
 * @brief Every Collisioner (an entity involved in a collision) has a type.
 */

#ifndef CORE_ENTITIES_COLLISIONERENTITY_H_
#define CORE_ENTITIES_COLLISIONERENTITY_H_

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

class CollisionSelector;
class StaticAABB2D;
class ConstantMovingCircle;

class CollisionObject {
public:
  virtual ~CollisionObject() {}  //!< Empty destructor
// You must add a new "accept" function for any new derived CollisionObject
  virtual bool accept(CollisionSelector &visitor, CollisionObject& param1, uint64_t& time, Point2D& point) = 0;       //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector &visitor, StaticAABB2D& param1, uint64_t& time, Point2D& point) = 0;          //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector &visitor, ConstantMovingCircle& param1, uint64_t& time, Point2D& point) = 0;  //!< Collision solver using the visitor pattern
};

/** \brief Every Collisioner (an entity involved in a collision) has a collision object defining his "physical shape".
 */
class CollisionerEntity : public Entity {
  public:
    /** \brief A collisionable entity is defined by a collision object.
      * \param object A collision object that defines the "physical shape" of the entity.
      */
    CollisionerEntity(CollisionObject* object) : Entity(), o(object), al() {}
    CollisionerEntity(const CollisionerEntity&) = delete;

    /** \brief Empty destructor.
      */
    virtual ~CollisionerEntity() {}

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

#endif  // CORE_ENTITIES_COLLISIONERENTITY_H_
