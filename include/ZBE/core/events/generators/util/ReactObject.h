/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ReactObject.h
 * @since 2016-12-12
 * @date 2016-12-20
 * @author Batis Ludo
 * @brief Object against which to react.
 */

#ifndef CORE_EVENTS_GENERATORS_UTIL_REACTOBJECT_H
#define CORE_EVENTS_GENERATORS_UTIL_REACTOBJECT_H

#include <initializer_list>

#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Object against which to react.
 */
template <typename R>
class ReactObject {
  public:
    virtual ~ReactObject() {}
		virtual void act(R* reactor) = 0;
};

/** \brief Object against which to react. Common code. Implementers should use this Class instead of ReactObject.
 */
template <typename R, typename ...Bases>
class ReactObjectCommon : public ReactObject<R> {
  public:
    ReactObjectCommon(const ReactObjectCommon&) = delete;
    void operator=(const ReactObjectCommon&) = delete;

    virtual ~ReactObjectCommon(){};

  	ReactObjectCommon(std::shared_ptr<WeakAvatarEntityContainer<Bases...> > rObject) : rObject(rObject) {}

    void act(R* reactor) {
      // This code is using a c ++11 syntax trick to call a method for each template parameter.
      // The list of initializers is being used to allow braces usage.
      // Comma operator is being used to pass a value to the braces.
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
    ReactObjectCommon(const ReactObjectCommon&) = delete;
    void operator=(const ReactObjectCommon&) = delete;

  	virtual ~ReactObjectCommon() {}

    ReactObjectCommon(std::shared_ptr<WeakAvatarEntityContainer<void> >){};
    ReactObjectCommon(){};

    void act(R* reactor) {
      reactor->act();
    }
};

}  // namespace

#endif //CORE_EVENTS_GENERATORS_UTIL_REACTOBJECT_H
