/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateLTEraser.h
 * @since 2017-08-05
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */

#ifndef ZBE_BEHAVIORS_STATELTERASER_H_
#define ZBE_BEHAVIORS_STATELTERASER_H_

#include <cstdint>
#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */
class StateLTEraser : virtual public Behavior<Avatar, Stated> {
public:
  /** \brief Parametrized constructor.
      \param limit Limit below which the entity will be killed.
   */
  StateLTEraser(int64_t limit) : limit(limit){}

  /** \brief Erases given entity if its stata is less that expected one.
   */
  void apply(std::shared_ptr<AvatarEntityContainer<Avatar, Stated> > entity) {
    zbe::Stated* stated;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Stated> > aecs = entity;
    assignAvatar(aecs, &stated);
    Avatar* avatar;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar> > aeca = entity;
    assignAvatar(aeca, &avatar);
    if(stated->getState() < limit){
      avatar->setERASED();
    }
  }

private:
  int64_t limit;
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_STATELTERASER_H_
