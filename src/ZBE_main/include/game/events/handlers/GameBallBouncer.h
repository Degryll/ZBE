/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameBallBouncer.h
 * @since 2016-12-17
 * @date 2017-03-20
 * @author Batis Degryll Ludo
 * @brief Actuator capable of making a Bouncer bounce in a Bounceable.
 */

#ifndef GAME_EVENTS_HANDLERS_GAMEBALLBOUNCER
#define GAME_EVENTS_HANDLERS_GAMEBALLBOUNCER

#include <cstdio>
#include <stdlib.h>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/entities/avatars/Bouncer.h"

#include "game/GameReactor.h"

namespace game {

/** \brief Actuator capable of making a BouncerCollisioner bounce in a Bounceable.
 */
class GameBallBouncer: public zbe::Actuator<zbe::Bouncer<2>, GameReactor> {
  public:
    void act() {
      zbe::Bouncer<2> * gb = zbe::Actuator<zbe::Bouncer<2>, GameReactor>::getCollisioner();
      zbe::CollisionData * cd = zbe::Actuator<zbe::Bouncer<2>, GameReactor>::getCollisionData();
      zbe::Vector<2> n = gb->getPosition() - cd->getPoint();
      gb->addNormal(n);
    }
};

}  // namespace

#endif //GAME_EVENTS_HANDLERS_GAMEBALLBOUNCER
