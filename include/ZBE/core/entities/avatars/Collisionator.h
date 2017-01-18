/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Collisionator.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Degryll Ludo
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
    Collisionator(CollisionObject<R>* object, uint64_t collisionablesListId) : Collisioner<R>(object), id(collisionablesListId) {}

    virtual ~Collisionator(){};

    /** \brief Returns the global id of the list of Collisionables identify by an id.
     *  \param id Id to identify the list.
     *  \return The global id of the list.
     */
    inline uint64_t getCollisionablesListId() { return (id); }

  private:
    uint64_t id;  //!< Id of list of collisionables

};

/** \brief Every Collisionator (an entity involved in a collision) has a collision object defining his "physical shape".
 */
template <typename T, typename R>
class CollisionatorCommon : public Collisionator<R> {
  public:
    /** \brief A collisionable entity is defined by a collision object.
      * \param object A collision object that defines the "physical shape" of the entity.
      */
    CollisionatorCommon(T* collisionator, CollisionObject<R>* object, std::forward_list<Actuator<T,R>* > * actuators, uint64_t collisionablesListId) : Collisionator<R>(object, collisionablesListId), al(actuators), c(collisionator) {}
    CollisionatorCommon(const CollisionatorCommon<T,R>&) = delete;
    void operator=(const CollisionatorCommon<T,R>&) = delete;

    void react(CollisionData* collisionData, ReactObject<R> * reactObject) {
      for (auto a : (*al)) {
        a->run(c, reactObject, collisionData);
      }
    };

    /** \brief Empty destructor.
      */
    virtual ~CollisionatorCommon() {}

  private:
    std::forward_list<Actuator<T,R>* >* al;
    T* c;

};

}  // namespace zbe

#endif  // CORE_ENTITIES_AVATARS_COLLISIONATOR_H_
