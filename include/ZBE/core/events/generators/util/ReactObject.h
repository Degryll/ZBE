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
template <typename R, typename T>
class ReactObjectCommon : public ReactObject<R> {
  public:
    ReactObjectCommon(const ReactObjectCommon&) = delete;
    void operator=(const ReactObjectCommon&) = delete;

    virtual ~ReactObjectCommon(){};

  	ReactObjectCommon(T* rObject) : rObject(rObject) {}

    void act(R* reactor) {
      reactor->act(rObject);
    }

  private:
    T* rObject;
};

}  // namespace

#endif //CORE_EVENTS_GENERATORS_UTIL_REACTOBJECT_H
