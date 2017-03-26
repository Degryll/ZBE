/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameBall.h
 * @since 2017-03-20
 * @date 2017-03-20
 * @author Batis Degryll Ludo
 * @brief A ball for an arkanoid.
 */

#ifndef ZBE_MAIN_GAME_GAMEBALL
#define ZBE_MAIN_GAME_GAMEBALL

#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/implementations/SimpleWideBouncingAPO.h"
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/avatars/implementations/BaseBouncer.h"
#include "ZBE/core/entities/avatars/SimpleSprite.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "game/GameReactor.h"
#include "game/reactobjects/GameReactObjects.h"

namespace game{

class GameBall: public zbe::Drawable,
                public zbe::SimpleWideBouncingAPO<2>,
                public zbe::AvatarEntityAdapted<zbe::SimpleSprite>,
                public zbe::AvatarEntityFixed<zbe::Bouncer<2> >,
                public zbe::AvatarEntityAdapted<zbe::Collisionator<game::GameReactor> > {
public:
  GameBall(const GameBall&) = delete;
  void operator=(const GameBall&) = delete;

  GameBall(double x, double y, double radius, double vx, double vy, uint64_t actuators, uint64_t collisionables, int graphics) :
      SimpleWideBouncingAPO({x, y}, {vx, vy}, radius, actuators, collisionables),
      g(graphics), r(radius), d(2*radius) {
      AvatarEntityFixed<zbe::Bouncer<2> >::setAvatar(new zbe::BaseBouncer<2>(this));
  }

  int64_t getX() {return ((int64_t)SimpleWideBouncingAPO::getPosition()[0]-r);}
  int64_t getY() {return ((int64_t)SimpleWideBouncingAPO::getPosition()[1]-r);}
  int64_t getW() {return ((int64_t)d);}
  int64_t getH() {return ((int64_t)d);}
  uint64_t getGraphics() {return (g);}

private:
  int g;    //!< Image index
  double r;
  double d;
};

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEBALL
