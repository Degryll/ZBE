/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Collsioner.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll Ludo
 * @brief Defines an element that can participate in collisions.
 */

#ifndef CORE_ENTITIES_AVATARS_COLLISIONER_H_
#define CORE_ENTITIES_AVATARS_COLLISIONER_H_

#include <forward_list>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/entities/avatars/ReactObject.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/collisions/CollisionData.h"
#include "ZBE/core/tools/containers/ListManager.h"

namespace zbe {

template <typename R>
class CollisionSelector;
template <typename R>
class StaticAABB2D;
template <typename R>
class ConstantMovingCircle;

template <typename R>
class CollisionObject {
public:
  virtual ~CollisionObject() {}  //!< Empty destructor
// You must add a new "accept" function for any new derived CollisionObject
  virtual bool accept(CollisionSelector<R> &visitor, CollisionObject& param1, uint64_t& time, Point2D& point) = 0;       //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector<R> &visitor, StaticAABB2D<R>& param1, uint64_t& time, Point2D& point) = 0;          //!< Collision solver using the visitor pattern
  virtual bool accept(CollisionSelector<R> &visitor, ConstantMovingCircle<R>& param1, uint64_t& time, Point2D& point) = 0;  //!< Collision solver using the visitor pattern
};

/** \brief Every Collisioner (an entity involved in a collision) has a collision object defining his "physical shape".
 */
template <typename R>
class Collisioner {
  public:
    /** \brief A collisionable entity is defined by a collision object.
     * \param object A collision object that defines the "physical shape" of the entity.
     */
    Collisioner(CollisionObject<R>* object) : o(object) {}
    Collisioner(const Collisioner<R>&) = delete;

    /** \brief Empty destructor.
     */
    virtual ~Collisioner() {}

    void operator=(const Collisioner&) = delete;

    /** \brief Set the collision object this entity is.
     *  \param object The collision object.
     */
    inline void setCollisionObject(CollisionObject<R>* object) {o = object;}

    /** \brief Return the collision object.
     *  \return Collision object.
     */
    inline CollisionObject<R>* getCollisionObject() {return (o);}

    virtual void react(CollisionData * collisionData, ReactObject<R> * reactObject) = 0;

  private:
    CollisionObject<R>* o;  //!< Collision object

};

/** \brief Every Collisioner (an entity involved in a collision) has a collision object defining his "physical shape".
 */
template <typename T, typename R>
class CollisionerCommon : public Collisioner<R> {
  public:
    CollisionerCommon(const CollisionerCommon&) = delete;
    void operator=(const CollisionerCommon&) = delete;

    /** \brief A collisionable entity is defined by a collision object.
      * \param object A collision object that defines the "physical shape" of the entity.
      */
    CollisionerCommon(T * collisioner, CollisionObject<R>* object, uint64_t actuatorsList) : Collisioner<R>(object), al(actuatorsList), c(collisioner), lma(ListManager<std::forward_list<Actuator<T,R>* > >::getInstance())  {}

    void react(CollisionData * collisionData, ReactObject<R> * reactObject);

    /** \brief Empty destructor.
      */
    virtual ~CollisionerCommon() {}

  private:
    uint64_t al;
    T * c;
    ListManager<std::forward_list<Actuator<T,R>* > >& lma;

};

template <typename T, typename R>
void CollisionerCommon<T, R>::react(CollisionData * collisionData, ReactObject<R> * reactObject) {
  for (auto a : *(lma.get(al)) ) {
    a->run(c, reactObject, collisionData);
  }
};


} // namespace zbe

#endif  // CORE_ENTITIES_AVATARS_COLLISIONER_H_
