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
#include "ZBE/core/tools/math/collisions/ReactObject.h"
#include "ZBE/archetypes/MobileAPO.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"

namespace zbe {

template <typename R, unsigned s>
class SimpleMobileAPO : public MobileAPO<R, s>, public SimpleMobile<s> {
  public:
    SimpleMobileAPO(const SimpleMobileAPO&) = delete;
    void operator=(const SimpleMobileAPO&) = delete;

    SimpleMobileAPO(std::shared_ptr<CollisionObject<R> > cObject, std::shared_ptr<ReactObject<R> > rObject, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(), co(cObject), ro(rObject), al(actuatorsList), cl(collisionablesList) {}
    SimpleMobileAPO(std::initializer_list<double> position, std::shared_ptr<CollisionObject<R> > cObject, std::shared_ptr<ReactObject<R> > rObject, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position), co(cObject), ro(rObject), al(actuatorsList), cl(collisionablesList) {}
    SimpleMobileAPO(Point<s> position, std::shared_ptr<CollisionObject<R> > cObject, std::shared_ptr<ReactObject<R> > rObject, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position), co(cObject), ro(rObject), al(actuatorsList), cl(collisionablesList) {}
    SimpleMobileAPO(Vector<s> velocity, std::shared_ptr<CollisionObject<R> > cObject, std::shared_ptr<ReactObject<R> > rObject, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(velocity), co(cObject), ro(rObject), al(actuatorsList), cl(collisionablesList) {}
    SimpleMobileAPO(std::initializer_list<double> position, std::initializer_list<double> velocity, std::shared_ptr<CollisionObject<R> > cObject, std::shared_ptr<ReactObject<R> > rObject, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), co(cObject), ro(rObject), al(actuatorsList), cl(collisionablesList) {}
    SimpleMobileAPO(Point<s> position, std::initializer_list<double> velocity, std::shared_ptr<CollisionObject<R> > cObject, std::shared_ptr<ReactObject<R> > rObject, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), co(cObject), ro(rObject), al(actuatorsList), cl(collisionablesList) {}
    SimpleMobileAPO(Point<s> position, Vector<s> velocity, std::shared_ptr<CollisionObject<R> > cObject, uint64_t actuatorsList, std::shared_ptr<ReactObject<R> > rObject, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), co(cObject), ro(rObject), al(actuatorsList), cl(collisionablesList) {}
    SimpleMobileAPO(std::initializer_list<double> position, Vector<s> velocity, std::shared_ptr<CollisionObject<R> > cObject, std::shared_ptr<ReactObject<R> > rObject, uint64_t actuatorsList, uint64_t collisionablesList) : SimpleMobile<s>(position, velocity), co(cObject), ro(rObject), al(actuatorsList), cl(collisionablesList) {}

    virtual ~SimpleMobileAPO(){}

	std::shared_ptr<CollisionObject<R> > getCollisionObject(){ return co;}
	std::shared_ptr<ReactObject<R> > getReactObject(){ return ro;}
  uint64_t getActuatorsList(){ return al;}
	uint64_t getCollisionablesList(){ return cl;}

  private:
    std::shared_ptr<CollisionObject<R> > co;
    std::shared_ptr<ReactObject<R> > ro;
    uint64_t al;
    uint64_t cl;
};

}  // namespace

#endif //ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEMOBILE_H
