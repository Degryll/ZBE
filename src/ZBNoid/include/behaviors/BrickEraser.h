/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BrickEraser.h
 * @since 2017-08-05
 * @date 2017-08-05
 * @author Degryll Ludo Batis
 * @brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */

#ifndef ZOMBIENOID_BEHAVIORS_BRICKERASER_H_
#define ZOMBIENOID_BEHAVIORS_BRICKERASER_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/Positionable.h"

#include "ZBE/core/entities/avatars/Avatar.h"

namespace zombienoid {

/** \brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */

class BrickEraser : virtual public zbe::Behavior<zbe::Stated, zbe::Avatar, zbe::Positionable<2> > {// : public Behavior<Element2D<R> > {
public:
  /**\brief Will erase the brick when its state is lower than the limit.
    It also have an oportunity to create an entity.
     \param limit Limit below which the entity will be killed.
     \param succes positive cases amount for item creation.
     \param total total cases amount for item creation.
  */
  BrickEraser(int64_t limit, uint64_t succes, uint64_t total, std::shared_ptr<zbe::Behavior<zbe::Positionable<2> > > builder) : limit(limit), succes(succes), total(total), builder(builder) {}

  ~BrickEraser(){}

  /**\brief If entity state down limit is reached, entity is erased and an attempt to create an item is made.
  */
  void apply(std::shared_ptr<zbe::AvatarEntityContainer<zbe::Stated, zbe::Avatar, zbe::Positionable<2> > > entity) override {
    zbe::Stated* stated;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Stated> > aecs = entity;
    assignAvatar(aecs , &stated);
    zbe::Avatar* avatar;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar> > aeca = entity;
    assignAvatar(aeca, &avatar);
    if(stated->getState() < limit){
      avatar->setERASED();
      attemptItemCreation(entity);
    }
  }
private:

  void attemptItemCreation(std::shared_ptr<zbe::AvatarEntityContainer<zbe::Positionable<2> > > entity){
      int64_t sample = (rand() % total);
      if(sample<succes) {
        builder->apply(entity);
      }
  }

  int64_t limit;
  int64_t succes;
  int64_t total;
  std::shared_ptr<zbe::Behavior<zbe::Positionable<2> > > builder;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_BEHAVIORS_BRICKERASER_H_
