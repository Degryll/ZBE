/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BallRadiusItem.h
 * @since 2017-10-09
 * @date 2017-10-09
 * @author Ludo
 * @brief Daemon capable of increase balls radius
 */

#ifndef ZOMBIENOID_DAEMONS_ITEMS_BALLRADIUSITEM
#define ZOMBIENOID_DAEMONS_ITEMS_BALLRADIUSITEM

#include <memory>
#include <cstdint>
#include <algorithm>

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/tools/containers/ResourceManager.h"

#include "ZBE/entities/avatars/Resizable.h"

namespace zombienoid {

/** \brief Daemon capable of increase balls radius
 */
template <typename BL>
class BallRadiusItem : public zbe::Daemon {
public:

  BallRadiusItem(const BallRadiusItem&) = delete;
  void operator=(const BallRadiusItem&) = delete;

  BallRadiusItem(uint64_t listId, double amount)
    : ballList(zbe::ResourceManager<BL>::getInstance().get(listId)),
      amount(amount) {
  }

  ~BallRadiusItem(){}

  void run(){
    for(auto ball : (*ballList)) {
      zbe::Resizable* resizable;
      assignAvatar((std::shared_ptr<zbe::AvatarEntityContainer<zbe::Resizable> >)ball,&resizable);
      resizable->increaseSize(amount);
    }
  }

private:
  std::shared_ptr<BL> ballList;
  double amount;
};

}  // namespace zombienoid

#endif // ZOMBIENOID_DAEMONS_ITEMS_BALLRADIUSITEM
