/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Actuator.h
 * @since 2017-04-27
 * @date 2017-04-27
 * @author Batis Degryll Ludo
 * @brief Generic Actuator wraper base functionality.
 */

#ifndef CORE_HANDLERS_COLLISION_ACTUATORWRAPPER_H
#define CORE_HANDLERS_COLLISION_ACTUATORWRAPPER_H

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

namespace zbe {

/** \brief Actuator base functionality.
 */
template <typename R, typename... Bases>
class ActuatorWrapper {
  public:

    virtual ~ActuatorWrapper() {};

    virtual void run(AvatarEntityContainer<Bases...> * container, ReactObject<R>* rObject, CollisionData* cData) = 0;

};

/** \brief Actuator base functionality.
 */
template <typename R, typename T, typename... Bases>
class ActuatorWrapperCommon: virtual public ActuatorWrapper<R, Bases...>{
public:
  ActuatorWrapperCommon(const ActuatorWrapperCommon&) = delete;
  void operator=(const ActuatorWrapperCommon&) = delete;

  ActuatorWrapperCommon(Actuator<T, R> * actuator):a(actuator){};
  virtual ~ActuatorWrapperCommon() {};

  void run(AvatarEntityContainer<Bases...> * container, ReactObject<R>* rObject, CollisionData* cData) {
    T* t;
    AvatarEntityContainer<T>* tcont = container;
    assignAvatar(tcont->get(), &t);
    a->run(t,rObject,cData);
  }
private:
  Actuator<T, R>* a;
};

}  // namespace

#endif //CORE_HANDLERS_COLLISION_ACTUATORWRAPPER_H

