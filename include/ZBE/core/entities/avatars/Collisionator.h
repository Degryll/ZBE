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
class Collisionator : virtual public Collisioner<R> {
  public:

    virtual ~Collisionator(){};

    /**  \brief Returns the global id of the list of Collisionables identify by an id.
      *  \param id Id to identify the list.
      *  \return The global id of the list.
      */
    virtual uint64_t getCollisionablesListId() = 0;
};

/** \brief Every Collisionator (an entity involved in a collision) has a collision object defining his "physical shape".
 */
template <typename T, typename R>
class CollisionatorCommon : public Collisionator<R>, public CollisionerCommon<T, R> {
  public:
    CollisionatorCommon(const CollisionatorCommon<T,R>&) = delete;
    void operator=(const CollisionatorCommon<T,R>&) = delete;

    /** \brief A collisionable entity is defined by a collision object.
      * \param object A collision object that defines the "physical shape" of the entity.
      */
    CollisionatorCommon(T* collisionator, std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList, uint64_t collisionablesListId)
      : CollisionerCommon<T, R>(collisionator, collisionObject, reactObject, actuatorsList), id(collisionablesListId), c(collisionator) {}

    /** \brief Empty destructor.
      */
    virtual ~CollisionatorCommon() {}

   /**  \brief Returns the global id of the list of Collisionables identify by an id.
     *  \param id Id to identify the list.
     *  \return The global id of the list.
     */
    uint64_t getCollisionablesListId() {return (id);}

  private:
    uint64_t id;  //!< Id of list of collisionables
    T* c;
};

}  // namespace zbe

#endif  // CORE_ENTITIES_AVATARS_COLLISIONATOR_H_
