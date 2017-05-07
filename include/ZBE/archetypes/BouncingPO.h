/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BouncingMobilePO.h
 * @since 2017-03-07
 * @date 2017-03-07
 * @author Batis Degryll Ludo
 * @brief Defines the interface for a Bouncing Mobile Physical Object.
 */

#ifndef ZBE_ARCHETYPES_BOUNCINGMOBILEPO_H
#define ZBE_ARCHETYPES_BOUNCINGMOBILEPO_H

#include <cstdint>

#include "ZBE/archetypes/Bouncing.h"
#include "ZBE/archetypes/MobilePO.h"

namespace zbe {

template <unsigned s, typename R>
class BouncingPO : virtual public Bouncing<s>, virtual public MobilePO<s, R> {
public:
  BouncingPO(std::shared_ptr<CollisionObject<R> > collisionObject, std::shared_ptr<ReactObject<R> > reactObject, uint64_t actuatorsList)
  : PhysicalObject(collisionObject, reactObject, actuatorsList) {}

  virtual ~BouncingMobilePO() {}
};

}  // namespace

#endif //ZBE_ARCHETYPES_BOUNCINGMOBILEPO_H
