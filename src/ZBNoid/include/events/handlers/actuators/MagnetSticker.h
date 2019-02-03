/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MagnetSticker.h
 * @since 2017-06-25
 * @date 2017-06-25
 * @author Batis Degryll Ludo
 * @brief Actuator capable of stick a Positionable<2>-Avatar to a magnet.
 */

#ifndef ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_MAGNETSTICKER_H
#define ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_MAGNETSTICKER_H

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Positionable.h"

#include "entities/avatars/Magnet.h"
#include "entities/avatars/implementations/BoundedWrapperPositionable2D.h"

namespace zombienoid {

/** \brief Actuator capable of stick a Positionable<2>-Avatar to a magnet.
 */
template <typename R, typename LT>
class MagnetSticker : public zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Positionable<2>, zbe::Avatar>, R>  {
public:

  MagnetSticker(std::shared_ptr<LT> list, int64_t oldBhvId, int64_t newBhvId, double xMin, double yMin, double xMax, double yMax)
    : list(list), oldBhvId(oldBhvId), newBhvId(newBhvId), xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax) {}

  void act(std::shared_ptr<zbe::WeakAvatarEntityContainer<Magnet<2> > > magnetWAEC) {
    Magnet<2>* magnet;
    magnetWAEC->get()->assignAvatar(&magnet);
    zbe::Point2D center = magnet->getPosition();
    zbe::Avatar* avatar;
    zbe::Positionable<2>* positionable;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Avatar> >            waeca = zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Positionable<2>, zbe::Avatar>, R>::getCollisioner();
    std::shared_ptr<zbe::WeakAvatarEntityContainer<zbe::Positionable<2> > > waecp2 = zbe::Actuator<zbe::WeakAvatarEntityContainer<zbe::Positionable<2>, zbe::Avatar>, R>::getCollisioner();
    waeca->get()->assignAvatar(&avatar);
    waecp2->get()->assignAvatar(&positionable);
    zbe::Vector2D offset = positionable->getPosition() - center;
    zbe::Positionable<2>* wrapper = new BoundedWrapperPositionable2D(waecp2->get(), xMin, yMin, xMax, yMax, offset.x, 0);
    std::shared_ptr<zbe::AvatarEntity<zbe::Positionable<2> > > aep2 = std::make_shared<zbe::AvatarEntityFixed<zbe::Positionable<2> > >(wrapper);
    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Positionable<2>, zbe::Avatar> > aecp2a = std::make_shared<zbe::AvatarEntityContainer<zbe::Positionable<2>, zbe::Avatar> >(aep2, waeca->get());
    avatar->addTicket(newBhvId, list->push_front(aecp2a));
    avatar->setINACTIVE(oldBhvId);
  }
public:
    std::shared_ptr<LT> list;
    int64_t oldBhvId;
    int64_t newBhvId;
    double xMin;
    double yMin;
    double xMax;
    double yMax;

};

}  // namespace zombienoid

#endif // ZOMBIENOID_EVENTS_HANDLERS_ACTUATORS_MAGNETSTICKER_H
