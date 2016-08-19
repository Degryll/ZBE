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
    CollisionerEntity(CollisionObject* object) : Entity(), o(object) {}
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

  private:
    CollisionObject* o;  //!< Collision object
};

}  // namespace zbe

#endif  // CORE_ENTITIES_COLLISIONERENTITY_H_
