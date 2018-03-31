/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InitialBallMagnetizer.h
 * @since 2017-08-05
 * @date 2017-08-05
 * @author Degryll Ludo Batis
 * @brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */

#ifndef ZOMBIENOID_BEHAVIORS_INITIALBALLMAGENTIZER_H_
#define ZOMBIENOID_BEHAVIORS_INITIALBALLMAGENTIZER_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Positionable.h"

#include "ZBE/core/entities/avatars/Avatar.h"

namespace zombienoid {

/** \brief Implements a behavior that kills the entity when it reaches a state lower than a nummber.
 */
template <typename R, typename LT, typename ...Avatars>
class InitialBallMagnetizer : virtual public zbe::Behavior<Avatars...> {// : public Behavior<Element2D<R> > {
public:
  /**\brief Will erase entity from newId and reactivate it on oldId
     \param oldId Previous list id
     \param newId Old list id
  */
  InitialBallMagnetizer(std::shared_ptr<LT> list, int64_t oldBhvId, int64_t newBhvId, double xMin, double yMin, double xMax, double yMax, zbe::Vector2D offset)
    :list(list), oldBhvId(oldBhvId), newBhvId(newBhvId), xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax), offset(offset) {}

  ~InitialBallMagnetizer(){}

  /**\brief If entity state down limit is reached, entity is erased and an attempt to create an item is made.
  */
  void apply(std::shared_ptr<zbe::AvatarEntityContainer<Avatars...> > entity) {
    zbe::Avatar* avatar;
    zbe::Positionable<2>* positionable;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Avatar> > aeca = entity;
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Positionable<2> > > aecp2 = entity;
    aeca->get()->assignAvatar(&avatar);
    aecp2->get()->assignAvatar(&positionable);
    zbe::Positionable<2>* wrapper = new BoundedWrapperPositionable2D(aecp2->get(), xMin, yMin, xMax, yMax, offset.x, 0);
    std::shared_ptr<zbe::AvatarEntity<zbe::Positionable<2> > > aep2 = std::make_shared<zbe::AvatarEntityFixed<zbe::Positionable<2> > >(wrapper);
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Positionable<2>, zbe::Avatar> > aecp2a = std::make_shared<zbe::AvatarEntityContainer<zbe::Positionable<2>, zbe::Avatar> >(aep2, aeca->get());
    avatar->addToList(newBhvId, list->push_front(aecp2a));
    avatar->setINACTIVE(oldBhvId);
  }
private:
  std::shared_ptr<LT> list;
  int64_t oldBhvId;
  int64_t newBhvId;
  double xMin;
  double yMin;
  double xMax;
  double yMax;
  zbe::Vector2D offset;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_BEHAVIORS_INITIALBALLMAGENTIZER_H_
