/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Actuator.h
 * @since 2016-12-11
 * @date 2016-12-11
 * @author Batis
 * @brief First Actuator interface.
 */

#ifndef CORE_HANDLERS_COLLISION_ACTUATOR_H
#define CORE_HANDLERS_COLLISION_ACTUATOR_H

#include "ZBE/core/entities/avatars/ReactObject.h"
#include "ZBE/core/tools/math/collisions/CollisionData.h"

namespace zbe {

/** \brief Entity that can be seen as a collisionator using an adaptor.
 */
template <typename T, typename R>
class Actuator : public R {
  public:
  	Actuator(const Actuator&) = delete;
  	void operator=(const Actuator&) = delete;

    Actuator() : collisioner(nullptr), cData(nullptr) {}

    void run(T* collisioner, ReactObject* rObject, CollisionData* cData){
			this->collisioner = collisioner;
      this->cData = cData;
      rObject->act(this);
    }

  private:
  	T* collisioner;
    CollisionData* cData;
};

}  // namespace

#endif //CORE_HANDLERS_COLLISION_ACTUATOR_H
