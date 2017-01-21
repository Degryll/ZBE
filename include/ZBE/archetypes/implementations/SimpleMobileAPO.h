/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleMobileAPO.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Simple implementation of the Mobile active physical object interface.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILEAPO_H
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILEAPO_H

#include <cstdint>

#include "ZBE/core/tools/math/collisions/CollisionObject.h"
#include "ZBE/archetypes/MobileAPO.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"

namespace zbe {

template <typename R, unsigned s>
class SimpleMobileAPO : virtual public MobileAPO<s>, public SimpleMobile<s> {
  public:
    SimpleMobileAPO(CollisionObject<R>* object, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(), o(object), al(actuatorsList, cl(collisionablesList)) {}
    SimpleMobileAPO(std::initializer_list<double> position, CollisionObject<R>* object, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position), o(object), al(actuatorsList, cl(collisionablesList) {}
    SimpleMobileAPO(Point<s> position, CollisionObject<R>* object, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position), o(object), al(actuatorsList, cl(collisionablesList) {}
    SimpleMobileAPO(Vector<s> velocity, CollisionObject<R>* object, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(velocity), o(object), al(actuatorsList, cl(collisionablesList) {}
    SimpleMobileAPO(std::initializer_list<double> position, std::initializer_list<double> velocity, CollisionObject<R>* object, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), o(object), al(actuatorsList, cl(collisionablesList) {}
    SimpleMoSimpleMobileAPObile(Point<s> position, std::initializer_list<double> velocity, CollisionObject<R>* object, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), o(object), al(actuatorsList, cl(collisionablesList) {}
    SimpleMobileAPO(Point<s> position, Vector<s> velocity, CollisionObject<R>* object, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), o(object), al(actuatorsList, cl(collisionablesList) {}
    SimpleMobileAPO(std::initializer_list<double> position, Vector<s> velocity, CollisionObject<R>* object, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), o(object), al(actuatorsList, cl(collisionablesList) {}

		CollisionObject<R>* getCollisionObject(){ return o;}
    uint64_t getActuatorsList(){ return al;}
		uint64_t getCollisionablesList(){ return cl;}

  private:
    CollisionObject<R> * o;
		uint64_t al;
    uint64_t cl;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE_H
