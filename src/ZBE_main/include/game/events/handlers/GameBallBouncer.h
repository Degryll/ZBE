/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameBallBouncer.h
 * @since 2016-12-17
 * @date 2016-12-18
 * @author Ludo
 * @brief Actuator capable of making a Movable bounce in a Bounceable.
 */

#ifndef GAME_EVENTS_HANDLERS_GAMEBALLBOUNCER
#define GAME_EVENTS_HANDLERS_GAMEBALLBOUNCER

#include <cstdio>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/entities/avatars/MovableCollisioner.h"

#include "game/reactobjects/GameReactObjects.h"
#include "game/GameReactor.h"

namespace game {


/** \brief Actuator capable of making a MovableCollisioner bounce in a Bounceable.
 */
class GameBallBouncer: public zbe::Actuator<zbe::MovableCollisioner<game::GameReactor, 2>, GameReactor> {
  public:
    void act(VoidReactObject*) {
      printf("Bounce\n");fflush(stdout);
      zbe::MovableCollisioner<game::GameReactor, 2> * gb = zbe::Actuator<zbe::MovableCollisioner<game::GameReactor, 2>, GameReactor>::getCollisioner();
      zbe::CollisionData * cd = zbe::Actuator<zbe::MovableCollisioner<game::GameReactor, 2>, GameReactor>::getCollisionData();

      zbe::Vector<2> v = gb->getVelocity();
      zbe::Vector<2> n = gb->getPosition() - cd->getPoint();
      //n.setPolars(1.0, n.getRads()+RECTRADS);
      v = v.reflect(n);
      gb->setVelocity(v);
    }
};

}  // namespace

#endif //GAME_EVENTS_HANDLERS_GAMEBALLBOUNCER
