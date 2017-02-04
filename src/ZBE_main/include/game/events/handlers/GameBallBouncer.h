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
#include <stdlib.h>

#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/entities/avatars/MovableCollisioner.h"
#include "ZBE/reactobjects/VoidReactObject.h"

#include "game/GameReactor.h"

namespace game {

/** \brief Actuator capable of making a MovableCollisioner bounce in a Bounceable.
 */
class GameBallBouncer: public zbe::Actuator<zbe::MovableCollisioner<game::GameReactor, 2>, GameReactor> {
  public:
    void act(zbe::VoidReactObject<game::GameReactor>*) {
      zbe::MovableCollisioner<game::GameReactor, 2> * gb = zbe::Actuator<zbe::MovableCollisioner<game::GameReactor, 2>, GameReactor>::getCollisioner();
      zbe::CollisionData * cd = zbe::Actuator<zbe::MovableCollisioner<game::GameReactor, 2>, GameReactor>::getCollisionData();

      zbe::Vector<2> v = gb->getVelocity();
      zbe::Point<2> p = cd->getPoint();
      zbe::Point<2> c = gb->getPosition();
      zbe::Vector<2> n = c - p;
      //n.setPolars(1.0, n.getRads()+RECTRADS);
      zbe::Vector<2> vP = v;
      v.reflect(n);
      gb->setVelocity(v);
      if( v[0] == vP[0] && v[1] == vP[1] ){
        printf("Mal!\n");
        printf("Vel antes: %ld x %ld\n", vP[0], vP[1]);fflush(stdout);
        printf("Vel despues: %ld x %ld\n", v[0], v[1]);fflush(stdout);
        printf("Colision: %ld x %ld\n", p[0], p[1]);fflush(stdout);
        printf("Centro: %ld x %ld\n", c[0], c[1]);fflush(stdout);
        printf("Normal: %ld x %ld\n", n[0], n[1]);fflush(stdout);
        vP.reflect(n);
        printf("Vel requetedespues : %ld x %ld\n", vP[0], vP[1]);fflush(stdout);
      }
    }
};

}  // namespace

#endif //GAME_EVENTS_HANDLERS_GAMEBALLBOUNCER
