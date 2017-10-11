/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ItemCatcher.h
 * @since 2017-10-09
 * @date 2017-10-09
 * @author Ludo
 * @brief Daemon capable of increase an value.
 */

#ifndef ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_BallAcceleratorItem
#define ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_BallAcceleratorItem

#include <memory>
#include <cstdint>

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/tools/containers/ResourceManager.h"

#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"

namespace zbe {

/** \brief Daemon capable of increase an value.
 */
template <typename BL>
class BallAcceleratorItem : public zbe::Daemon {
public:

  BallAcceleratorItem(const BallAcceleratorItem&) = delete;
  void operator=(const BallAcceleratorItem&) = delete;

  BallAcceleratorItem(uint64_t listId, double ratio)
    : ballList(ResourceManager<BL>::getInstance().get(listId)), ratio(ratio) {
  }

  ~BallAcceleratorItem(){}

  void run(){
    for(auto ball : (*ballList)) {
      zbe::Movable<2>* movable;
      assignAvatar((std::shared_ptr<AvatarEntityContainer<zbe::Movable<2> > >)ball,&movable);
      movable->setVelocity(movable->getVelocity() * ratio);
    }
  }

private:
  std::shared_ptr<BL> ballList;
  double ratio;
};

}  // namespace zbe

#endif // ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_BallAcceleratorItem
