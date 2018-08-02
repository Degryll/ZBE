/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CollisionBodies.h
 * @since 2018-07-31
 * @date 2018-07-31
 * @author Ludo Degryll Batis
 * @brief Base reactor.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_UTIL_REACTOR_H_
#define ZBE_CORE_EVENTS_GENERATORS_UTIL_REACTOR_H_

#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

template<typename D, typename O, typename RO, typename... ROS>
class Reactor : public Reactor<D, O, ROS...> {
public:
  virtual ~Reactor() {}

  using Reactor<D, O, ROS...>::act;

  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<RO> >) {}
};

template<typename D, typename O, typename RO>
class Reactor<D, O, RO> {
public:
  virtual ~Reactor() {}

  using InteractionData = D;
  using InteractionObject = O;

  virtual void act() {}
  virtual void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<RO> >) {}
};

template<typename D, typename O>
class Reactor<D, O, void> {
public:
  virtual ~Reactor() {}

  using InteractionData = D;
  using InteractionObject = O;

  virtual void act() {}
};



}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_UTIL_REACTOR_H_
