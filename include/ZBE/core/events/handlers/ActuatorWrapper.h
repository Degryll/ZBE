/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Actuator.h
 * @since 2017-04-27
 * @date 2018-03-18
 * @author Batis Degryll Ludo
 * @brief Generic Actuator wraper base functionality.
 */

#ifndef ZBE_CORE_EVENT_HANDLERS_COLLISION_ACTUATORWRAPPER_H
#define ZBE_CORE_EVENT_HANDLERS_COLLISION_ACTUATORWRAPPER_H

#include <memory>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Actuator base functionality.
 */
template <typename R, typename TEnt>
class ZBEAPI ActuatorWrapper {
  public:

    /** \brief Empty constructor
    */
    virtual ~ActuatorWrapper() {}

    /** \brief Calls the Actuator's run method.
    */
    virtual void run(std::shared_ptr<TEnt> container, std::shared_ptr<ReactObject<R> > rObject, CollisionData* cData) = 0;

};

/** \brief Actuator base functionality.
 */
template <typename R, typename TAct, typename TEnt>
class ZBEAPI ActuatorWrapperCommon: virtual public ActuatorWrapper<R, TEnt>{
public:
  ActuatorWrapperCommon(const ActuatorWrapperCommon&) = delete; //!< Avoid copy.
  void operator=(const ActuatorWrapperCommon&) = delete; //!< Avoid copy.

  /** \brief Parametrized constructor.
   *  \param actuator The actuator.
   */
  ActuatorWrapperCommon(Actuator<TAct, R> * actuator) : a(actuator) {}

  /** \brief Empty destructor.
   */
  virtual ~ActuatorWrapperCommon() {} //TODO delete a;

  /** \brief Calls the Actuator's run method.
  */
  void run(std::shared_ptr<TEnt> entity, std::shared_ptr<ReactObject<R> > rObject, CollisionData* cData) {
    std::shared_ptr<TAct> act = std::make_shared<TAct>(entity);
    a->run(act,rObject,cData);
  }

private:
  Actuator<TAct, R>* a;
};

}  // namespace

#endif  // ZBE_CORE_EVENT_HANDLERS_COLLISION_ACTUATORWRAPPER_H
