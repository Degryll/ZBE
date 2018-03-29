/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Actuator.h
 * @since 2016-12-11
 * @date 2018-03-18
 * @author Batis, Degryll, Ludo
 * @brief Actuator base functionality.
 */

#ifndef ZBE_CORE_EVENT_HANDLERS_COLLISION_ACTUATOR_H
#define ZBE_CORE_EVENT_HANDLERS_COLLISION_ACTUATOR_H

#include <memory>

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

namespace zbe {

/** \brief Actuator base functionality.
 */
template <typename T, typename R>
class Actuator : public R {
  public:
  	Actuator(const Actuator&) = delete;  //!< Avoid copy.
  	void operator=(const Actuator&) = delete;  //!< Avoid copy.

    /** \brief Empty constructor.
    */
    Actuator() : collisioner(), cData(nullptr) {}

    /** \brief Empty destructor.
     */
  	virtual ~Actuator() {};

    /** \brief Getter for a collisioner attribute.
     */
  	std::shared_ptr<T> getCollisioner() { return collisioner; }

    /** \brief Getter for a collisionData attribute.
     */
    CollisionData* getCollisionData() { return cData; }

    /** \brief It executes the actuator's logic.
     */
    void run(std::shared_ptr<T> collisioner, std::shared_ptr<ReactObject<R> > rObject, CollisionData* cData){
			this->collisioner = collisioner;
      this->cData = cData;
      rObject->act(this);
    }

  protected:
  	std::shared_ptr<T> collisioner;
    CollisionData* cData;
};

}  // namespace zbe

#endif  // ZBE_CORE_EVENT_HANDLERS_COLLISION_ACTUATOR_H
