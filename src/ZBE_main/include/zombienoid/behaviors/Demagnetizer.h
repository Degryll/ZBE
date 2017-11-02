/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Demagnetizer.h
 * @since 2017-08-05
 * @date 2017-08-05
 * @author Degryll Ludo Batis
 * @brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */

#ifndef ZOMBIENOID_BEHAVIORS_DEMAGNETIZER_H_
#define ZOMBIENOID_BEHAVIORS_DEMAGNETIZER_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Positionable.h"

#include "ZBE/core/entities/avatars/Avatar.h"

namespace zombienoid {

/** \brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */

class Demagnetizer : virtual public zbe::Behavior<zbe::Avatar> {// : public Behavior<Element2D<R> > {
public:
  /**\brief Will erase entity from newId and reactivate it on oldId
     \param oldId Previous list id
     \param newId Old list id
  */
  Demagnetizer(int64_t activateId, int64_t eraseId) : activateId(activateId), eraseId(eraseId) {}

  ~Demagnetizer(){}

  /**\brief If entity state down limit is reached, entity is erased and an attempt to create an item is made.
  */
  void apply(std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar> > entity) {
    zbe::Avatar* avatar;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar> > aeca = entity;
    assignAvatar(aeca, &avatar);
    avatar->setACTIVE(activateId);
    avatar->setERASED(eraseId);
  }
private:
  int64_t activateId;
  int64_t eraseId;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_BEHAVIORS_DEMAGNETIZER_H_
