/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameBall.h
 * @since 2017-01-24
 * @date 2017-01-24
 * @author Degryll
 * @brief A ball for an arkanoid.
 */

#ifndef ZBE_MAIN_GAME_GAMEBALL
#define ZBE_MAIN_GAME_GAMEBALL

#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/implementations/SimpleWideBouncingMobileAPO.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/entities/adaptorentities/BouncerMovableCollisionatorEntity.h"

#include "game/GameReactor.h"
#include "game/reactobjects/GameReactObjects.h"

namespace game{

  class GameBall: public zbe::Drawable,
                  public zbe::SimpleSpriteEntityAdapted<zbe::Drawable>,
                  public zbe::SimpleWideBouncingMobileAPO<2>,
                  public zbe::BouncerMovableCollisionatorEntityAdapted<GameReactor, zbe::SimpleWideBouncingMobileAPO<2>, 2> {
    public:
			GameBall(const GameBall&) = delete;
      void operator=(const GameBall&) = delete;

      GameBall(double x, double y, double radius, double vx, double vy, uint64_t actuators, uint64_t collisionables, int graphics) :
                  SimpleSpriteEntityAdapted(this),
                  SimpleWideBouncingMobileAPO({x, y}, {vx, vy}, radius, actuators, collisionables),
                  BouncerMovableCollisionatorEntityAdapted(this),
                  g(graphics), r(radius), d(2*radius) {}

      int64_t getX() {return ((int64_t)SimpleWideBouncingMobileAPO::getPosition()[0]-r);}
      int64_t getY() {return ((int64_t)SimpleWideBouncingMobileAPO::getPosition()[1]-r);}
      int64_t getW()        {return ((int64_t)d);}
      int64_t getH()        {return ((int64_t)d);}
      uint64_t      getGraphics() {return (g);}

    private:
      int g;    //!< Image index
      double r;
      double d;
  };

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEBALL
