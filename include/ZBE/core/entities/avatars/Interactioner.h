/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Interactioner.h
 * @since 2016-11-22
 * @date 2018-02-25
 * @author Degryll Batis Ludo
 * @brief Defines an element that can participate in interactions.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_COLLISIONER_H_
#define ZBE_CORE_ENTITIES_AVATARS_COLLISIONER_H_

#include <forward_list>
#include <memory>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/tools.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/events/handlers/ActuatorWrapper.h"
#include "ZBE/core/events/generators/util/ReactObject.h"

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Every Interactioner (an entity involved in a interaction) has a interaction object defining his "physical shape".
 */
template <typename R>
class Interactioner {
public:

  using Base = void; //!< Inheritance info.

  /** \brief Empty destructor.
   */
  virtual ~Interactioner() {}

  /** \brief Return the interaction object.
   *  \return Interaction object.
   */
  virtual std::shared_ptr<typename R::InteractionObject > getInteractionObject() = 0;

  /** \brief Return the react object.
   *  \return React object.
   */
  virtual std::shared_ptr<ReactObject<R> > getReactObject() = 0;

  virtual void react(typename R::InteractionData * interactionData, std::shared_ptr<ReactObject<R> > reactObject) = 0;
};

/** \brief Every Interactioner (an entity involved in a interaction) has a interaction object defining his "physical shape".
*/
template <typename R, typename ...Bases>
class InteractionerCommon : virtual public Interactioner<R> {
public:
  InteractionerCommon(const InteractionerCommon&) = delete;
  void operator=(const InteractionerCommon&) = delete;

  /** \brief A interactionable entity is defined by a interaction object.
    * \param object A interaction object that defines the "physical shape" of the entity.
    */
  InteractionerCommon(std::shared_ptr<WeakAvatarEntityContainer<Bases...> > interactioner, std::shared_ptr<typename R::InteractionObject> interactionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList)
    : co(interactionObject), ro(reactObject), al(actuatorsList), c(interactioner),
      lma(RsrcStore<std::forward_list<ActuatorWrapper<R, WeakAvatarEntityContainer<Bases...> >* > >::getInstance())  {}

  /** \brief Empty destructor.
    */
  virtual ~InteractionerCommon() {}

  /** \brief Set the interaction object this entity is.
   *  \param object The interaction object.
   */
  inline void setInteractionObject(std::shared_ptr<typename R::InteractionObject > object) {co = object;}

  /** \brief Set the react object this entity is.
   *  \param object The react object.
   */
  inline void setReactObject(std::shared_ptr<ReactObject<R> > object) {ro = object;}

  /** \brief Return the interaction object.
   *  \return Interaction object.
   */
  inline std::shared_ptr<typename R::InteractionObject > getInteractionObject() {return (co);}

  /** \brief Return the react object.
   *  \return React object.
   */
  inline std::shared_ptr<ReactObject<R> > getReactObject() {return (ro);}

  void react(typename R::InteractionData * interactionData, std::shared_ptr<ReactObject<R> > reactObject);

private:
  std::shared_ptr<typename R::InteractionObject > co;  //!< Interaction object
  std::shared_ptr<ReactObject<R> > ro;  //!< Interaction object
  uint64_t al;
  std::shared_ptr<WeakAvatarEntityContainer<Bases...> > c;
  RsrcStore<std::forward_list<ActuatorWrapper<R, WeakAvatarEntityContainer<Bases...> >* > >& lma;
};

template <typename R, typename ...Bases>
void InteractionerCommon<R, Bases...>::react(typename R::InteractionData * interactionData, std::shared_ptr<ReactObject<R> > reactObject) {
  for (auto a : *(lma.get(al)) ) {
    a->run(c, reactObject, interactionData);
  }
}

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_COLLISIONER_H_
