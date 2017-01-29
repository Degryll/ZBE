/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Collsioner.h
 * @since 2016-11-22
 * @date 2017-01-19
 * @author Ludo Degryll
 * @brief Defines an element that can participate in collisions.
 */

#ifndef CORE_ENTITIES_AVATARS_COLLISIONER_H_
#define CORE_ENTITIES_AVATARS_COLLISIONER_H_

#include <forward_list>
#include <memory>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/collisions/CollisionData.h"
#include "ZBE/core/tools/math/collisions/CollisionObject.h"
#include "ZBE/core/tools/math/collisions/ReactObject.h"
#include "ZBE/core/tools/containers/ListManager.h"

namespace zbe {

/** \brief Every Collisioner (an entity involved in a collision) has a collision object defining his "physical shape".
 */
template <typename R>
class Collisioner {
  public:
    /** \brief Empty destructor.
     */
    virtual ~Collisioner() {}

    /** \brief Return the collision object.
     *  \return Collision object.
     */
    virtual std::shared_ptr<CollisionObject<R> > getCollisionObject() = 0;

    /** \brief Return the react object.
     *  \return React object.
     */
    virtual std::shared_ptr<ReactObject<R> > getReactObject() = 0;

    virtual void react(CollisionData * collisionData, ReactObject<R> * reactObject) = 0;
};

/** \brief Every Collisioner (an entity involved in a collision) has a collision object defining his "physical shape".
 */
template <typename T, typename R>
class CollisionerCommon : virtual public Collisioner<R> {
  public:
    CollisionerCommon(const CollisionerCommon&) = delete;
    void operator=(const CollisionerCommon&) = delete;

    /** \brief A collisionable entity is defined by a collision object.
      * \param object A collision object that defines the "physical shape" of the entity.
      */
    CollisionerCommon(T * collisioner, std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList) : co(collisionObject), ro(reactObject), al(actuatorsList), c(collisioner), lma(ListManager<std::forward_list<Actuator<T,R>* > >::getInstance())  {}

    /** \brief Empty destructor.
      */
    virtual ~CollisionerCommon() {}

    /** \brief Set the collision object this entity is.
     *  \param object The collision object.
     */
    inline void setCollisionObject(std::shared_ptr<CollisionObject<R> > object) {co = object;}

    /** \brief Set the react object this entity is.
     *  \param object The react object.
     */
    inline void setReactObject(std::shared_ptr<ReactObject<R> > object) {ro = object;}

    /** \brief Return the collision object.
     *  \return Collision object.
     */
    inline std::shared_ptr<CollisionObject<R> > getCollisionObject() {return (co);}

    /** \brief Return the react object.
     *  \return React object.
     */
    inline std::shared_ptr<ReactObject<R> > getReactObject() {return (ro);}

    void react(CollisionData * collisionData, ReactObject<R> * reactObject);

  private:
    std::shared_ptr<CollisionObject<R> > co;  //!< Collision object
    std::shared_ptr<ReactObject<R> > ro;  //!< Collision object
    uint64_t al;
    T * c;
    ListManager<std::forward_list<Actuator<T,R>* > >& lma;

};

template <typename T, typename R>
void CollisionerCommon<T, R>::react(CollisionData * collisionData, ReactObject<R> * reactObject) {
  printf("%s\n", typeid(lma.get(al)).name());fflush(stdout);
  for (auto a : *(lma.get(al)) ) {
    a->run(c, reactObject, collisionData);
  }
};


} // namespace zbe

#endif  // CORE_ENTITIES_AVATARS_COLLISIONER_H_
