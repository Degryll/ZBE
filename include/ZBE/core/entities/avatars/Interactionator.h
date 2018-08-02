/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Interactionator.h
 * @since 2016-03-24
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Defines a Interactioner that collide with others Interactioner.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_COLLISIONATOR_H_
#define ZBE_CORE_ENTITIES_AVATARS_COLLISIONATOR_H_

#include <cstdint>
#include <memory>
#include <forward_list>

#include "ZBE/core/entities/avatars/Interactioner.h"

namespace zbe {

/** \brief Define the basic functionality of every Interactionable entity.
 */
template <typename R>
class Interactionator : virtual public Interactioner<R> {
public:

  using Base = Interactioner<R>; //!< Inheritance info.

  /** \brief Virtual destructor.
   */
  virtual ~Interactionator(){};

  /**  \brief Returns the global id of the list of Interactionables identify by an id.
    *  \param id Id to identify the list.
    *  \return The global id of the list.
    */
  virtual uint64_t getInteractionablesListId() = 0;
};

/** \brief Every Interactionator (an entity involved in a collision) has a collision object defining his "physical shape".
*/
template <typename R, typename ...Bases>
class InteractionatorCommon : virtual public Interactionator<R>, public InteractionerCommon<R, Bases...> {
public:
  InteractionatorCommon(const InteractionatorCommon<R, Bases...>&) = delete;
  void operator=(const InteractionatorCommon<R, Bases...>&) = delete;

  /** \brief A collisionable entity is defined by a collision object.
    * \param object A collision object that defines the "physical shape" of the entity.
    */
  InteractionatorCommon(std::shared_ptr<WeakAvatarEntityContainer<Bases...> > collisionator, std::shared_ptr<typename R::InteractionObject> collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList, uint64_t collisionablesListId)
    : InteractionerCommon<R, Bases...>(collisionator, collisionObject, reactObject, actuatorsList), id(collisionablesListId) {}

  /** \brief Empty destructor.
    */
  virtual ~InteractionatorCommon() {}

 /**  \brief Returns the global id of the list of Interactionables identify by an id.
   *  \param id Id to identify the list.
   *  \return The global id of the list.
   */
  uint64_t getInteractionablesListId() {return (id);}

private:
  uint64_t id;  //!< Id of list of collisionables
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_COLLISIONATOR_H_
