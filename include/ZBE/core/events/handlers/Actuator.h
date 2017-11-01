/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Actuator.h
 * @since 2016-12-11
 * @date 2016-12-11
 * @author Batis
 * @brief Actuator base functionality.
 */

#ifndef CORE_HANDLERS_COLLISION_ACTUATOR_H
#define CORE_HANDLERS_COLLISION_ACTUATOR_H

#include "ZBE/core/events/generators/util/ReactObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

namespace zbe {

/** \brief Actuator base functionality.
 */
template <typename T, typename R>
class Actuator : public R {
  public:
  	Actuator(const Actuator&) = delete;
  	void operator=(const Actuator&) = delete;
  	virtual ~Actuator() {};

    Actuator() : collisioner(nullptr), cData(nullptr) {}

  	std::shared_ptr<T> getCollisioner() { return collisioner; }
    CollisionData* getCollisionData() { return cData; }

    void run(std::shared_ptr<T> collisioner, std::shared_ptr<ReactObject<R> > rObject, CollisionData* cData){
			this->collisioner = collisioner;
      this->cData = cData;
      rObject->act(this);
    }

  protected:
  	std::shared_ptr<T> collisioner;
    CollisionData* cData;
};

}  // namespace

#endif //CORE_HANDLERS_COLLISION_ACTUATOR_H
