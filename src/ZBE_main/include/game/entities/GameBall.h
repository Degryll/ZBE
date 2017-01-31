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
#include "ZBE/archetypes/implementations/SimpleWideMobileAPO.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/entities/adaptorentities/MovableCollisionatorEntity.h"

#include "game/GameReactor.h"
#include "game/reactobjects/GameReactObjects.h"

namespace game{

  class GameBall: public zbe::Drawable,
                  public zbe::SimpleWideMobileAPO<2>,
                  public zbe::SimpleSpriteEntityAdapted<zbe::Drawable>,
                  public zbe::MovableCollisionatorEntityAdapted<GameReactor, zbe::SimpleWideMobileAPO<2>, 2> {
    public:
			GameBall(const GameBall&) = delete;
      void operator=(const GameBall&) = delete;

      GameBall(double x, double y, unsigned radius, double vx, double vy, uint64_t actuators, uint64_t collisionables, int graphics) :
                  SimpleWideMobileAPO({x, y}, {vx, vy}, radius, actuators, collisionables),
                  SimpleSpriteEntityAdapted(this),
                  MovableCollisionatorEntityAdapted(this),
                  g(graphics), r(radius), d(2*radius) {}

      ~GameBall() {}

      int getX() {return (SimpleWideMobileAPO::getPosition()[0]-r);}
      int getY() {return (SimpleWideMobileAPO::getPosition()[1]-r);}
      unsigned getW()        {return (d);}
      unsigned getH()        {return (d);}
      int      getGraphics() {return (g);}

    private:
      int g;    //!< Image index
      unsigned r;
      unsigned d;
  };

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEBALL
