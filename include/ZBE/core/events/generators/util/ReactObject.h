/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ReactObject.h
 * @since 2016-12-12
 * @date 2018-03-15
 * @author Batis Ludo Degryll
 * @brief Object against which to react.
 */

#ifndef CORE_EVENTS_GENERATORS_UTIL_REACTOBJECT_H
#define CORE_EVENTS_GENERATORS_UTIL_REACTOBJECT_H

#include <initializer_list>
#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Object against which to react.
 */
template <typename R>
class ReactObject {
  public:
    /** \brief destructor
     */
    virtual ~ReactObject() {}

    /** \brief Executes the corresponding parts of the actuators.
     * \param reactor The reactive part of the actuator.
     */
		virtual void act(R* reactor) = 0;
};

/** \brief Object against which to react. Common code. All implementations should inherit this Class instead of ReactObject.
 */
template <typename R, typename ...Bases>
class ReactObjectCommon : public ReactObject<R> {
  public:

    /** \brief parametrized constructor
     * \param rObject Container of entity avatars
     */
  	ReactObjectCommon(std::shared_ptr<WeakAvatarEntityContainer<Bases...> > rObject) : rObject(rObject) {}

    /** \brief destructor
     */
    virtual ~ReactObjectCommon() {}

    /** \brief Executes the corresponding parts of the actuators.
     * \param reactor The reactive part of the actuator.
     */
    void act(R* reactor) {

      // This code is using a c ++11 syntax trick to call a method for each template parameter.
      // The list of initializers is being used to allow braces usage.
      // Comma operator is being used to pass a value to the braces.
      // Explanation:
      // This is an initializer list with a single element, a zero. (useless at the moment)
      // std::initializer_list<int>{(0)}
      // What if we want to expand that "(0)" for each template parameter?
      // this does not work, cause 0 is not a parameter pack.
      // std::initializer_list<int>{(0)...}
      // neither does this, cause each element in Bases is a type, not a value.
      // std::initializer_list<int>{(Bases)...}
      // the expresion
      // reactor->act(std::shared_ptr<WeakAvatarEntityContainer<Bases> >(rObject))
      // returns void, so we can not pass this to the initializer list either
      // How can we make that expresion return a value?
      // Using a comma operator: (expression1, expression2)
      // both expressions are evaluated, but only the value of expression2 is returned.
      // so, the next statement creates an initializer_list full of zeroes (one for each type in Bases) that will be ignored by the compiler.
      // In adition, it calls "reactor->act(...)" with each type in Bases. This is what we want.
      // gg eazy!
      std::initializer_list<int>{ (reactor->act(std::shared_ptr<WeakAvatarEntityContainer<Bases> >(rObject)), 0)... };
      reactor->act();
    }

  private:
    std::shared_ptr<WeakAvatarEntityContainer<Bases...> > rObject;
};

/** \brief Object against which to react. Common code. Implementers should use this Class instead of ReactObject.
 */
template <typename R>
class ReactObjectCommon<R> : public ReactObject<R> {
  public:

    /** \brief parametrized constructor
     * \param Container of entity avatars
     */
    ReactObjectCommon(std::shared_ptr<WeakAvatarEntityContainer<void> >) {}

    /** \brief empty constructor
     */
    ReactObjectCommon() {}

    /** \brief Virtual destructor
     */
  	virtual ~ReactObjectCommon() {}

    /** \brief Executes the corresponding parts of the actuators.
     * \param reactor The reactive part of the actuator.
     */
    void act(R* reactor) {
      reactor->act();
    }
};

}  // namespace zbe

#endif  // CORE_EVENTS_GENERATORS_UTIL_REACTOBJECT_H
