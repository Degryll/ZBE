/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BallAcceleratorItem.h
 * @since 2017-10-09
 * @date 2017-10-09
 * @author Ludo
 * @brief Daemon capable of increase speed of a list of entities.
 */

#ifndef ZOMBIENOID_DAEMONS_ITEMS_BALLACELERATORITEM
#define ZOMBIENOID_DAEMONS_ITEMS_BALLACELERATORITEM

#include <memory>
#include <cstdint>

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/tools/containers/ResourceManager.h"

#include "ZBE/entities/avatars/Movable.h"

namespace zombienoid {

/** \brief Daemon capable of increase speed of a list of entities.
 */
template <typename BL>
class BallAcceleratorItem : public zbe::Daemon {
public:

  BallAcceleratorItem(const BallAcceleratorItem&) = delete;
  void operator=(const BallAcceleratorItem&) = delete;

  BallAcceleratorItem(uint64_t listId, double ratio)
    : ballList(zbe::ResourceManager<BL>::getInstance().get(listId)), ratio(ratio) {
  }

  ~BallAcceleratorItem(){}

  void run(){
    for(auto ball : (*ballList)) {
      zbe::Movable<2>* movable;
      assignAvatar((std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2> > >)ball,&movable);
      movable->setVelocity(movable->getVelocity() * ratio);
    }
  }

private:
  std::shared_ptr<BL> ballList;
  double ratio;
};

}  // namespace zombienoid

#endif // ZOMBIENOID_DAEMONS_ITEMS_BALLACELERATORITEM
