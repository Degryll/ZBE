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
#include "ZBE/core/tools/tools.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/events/handlers/ActuatorWrapper.h"
#include "ZBE/core/events/generators/util/CollisionData.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"
#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/tools/containers/ResourceManager.h"

namespace zbe {

/** \brief Every Collisioner (an entity involved in a collision) has a collision object defining his "physical shape".
 */
template <typename R>
class Collisioner {
  public:

    using Base = void;

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
template <typename R, typename ...Bases>
class CollisionerCommon : virtual public Collisioner<R> {
  public:
    CollisionerCommon(const CollisionerCommon&) = delete;
    void operator=(const CollisionerCommon&) = delete;

    /** \brief A collisionable entity is defined by a collision object.
      * \param object A collision object that defines the "physical shape" of the entity.
      */
    CollisionerCommon(AvatarEntityContainer<Bases...>* collisioner, std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList) : co(collisionObject), ro(reactObject), al(actuatorsList), c(collisioner), lma(ResourceManager<std::forward_list<ActuatorWrapper<R, Bases...>* > >::getInstance())  {}

    /** \brief Empty destructor.
      */
    virtual ~CollisionerCommon() {delete c;}

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
    AvatarEntityContainer<Bases...>* c;
    ResourceManager<std::forward_list<ActuatorWrapper<R, Bases...>* > >& lma;

};

template <typename R, typename ...Bases>
void CollisionerCommon<R, Bases...>::react(CollisionData * collisionData, ReactObject<R> * reactObject) {
  for (auto a : *(lma.get(al)) ) {
    a->run(c, reactObject, collisionData);
  }
};


} // namespace zbe

#endif  // CORE_ENTITIES_AVATARS_COLLISIONER_H_
