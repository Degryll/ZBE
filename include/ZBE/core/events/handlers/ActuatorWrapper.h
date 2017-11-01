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
template <typename R, typename TEnt>
class ActuatorWrapper {
  public:

    virtual ~ActuatorWrapper() {};

    virtual void run(std::shared_ptr<TEnt> container, std::shared_ptr<ReactObject<R> > rObject, CollisionData* cData) = 0;

};

/** \brief Actuator base functionality.
 */
template <typename R, typename TAct, typename TEnt>
class ActuatorWrapperCommon: virtual public ActuatorWrapper<R, TEnt>{
public:
  ActuatorWrapperCommon(const ActuatorWrapperCommon&) = delete;
  void operator=(const ActuatorWrapperCommon&) = delete;

  ActuatorWrapperCommon(Actuator<TAct, R> * actuator):a(actuator){};
  virtual ~ActuatorWrapperCommon() {}; //TODO delete a;

  void run(std::shared_ptr<TEnt> entity, std::shared_ptr<ReactObject<R> > rObject, CollisionData* cData) {
    std::shared_ptr<TAct> act = std::make_shared<TAct>(entity);
    a->run(act,rObject,cData);
  }
private:
  Actuator<TAct, R>* a;
};

}  // namespace

#endif //CORE_HANDLERS_COLLISION_ACTUATORWRAPPER_H

