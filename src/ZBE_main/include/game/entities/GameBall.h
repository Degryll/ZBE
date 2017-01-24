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
#include "ZBE/archetypes/implementations/SimpleMobileAPO.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/entities/adaptorentities/MovableCollisionatorEntity.h"

#include "game/GameReactor.h"
#include "game/reactobjects/GameReactObjects.h"

namespace game{

  class GameBall: public zbe::Drawable,
                  public zbe::SimpleMobileAPO<GameReactor, 2>,
                  public zbe::SimpleSpriteEntityAdapted<zbe::Drawable>,
                  public zbe::MovableCollisionatorEntityAdapted<GameReactor, zbe::MobileAPO<GameReactor, 2>, 2> {
    public:
			GameBall(const GameBall&) = delete;
      void operator=(const GameBall&) = delete;

      GameBall(double x, double y, unsigned radius, double vx, double vy, uint64_t actuators, uint64_t collisionables, int graphics) :
                  SimpleMobileAPO({x, y}, {vx, vy}, std::make_shared<zbe::ConstantMovingCircle<GameReactor> >(zbe::ConstantMovingCircle<GameReactor>(zbe::Circle({x, y}, radius), {vx, vy})), std::make_shared<VoidReactObject>(), actuators, collisionables),
                  SimpleSpriteEntityAdapted(this),
                  MovableCollisionatorEntityAdapted(this),
                  g(graphics), d(2*radius) {}

      ~GameBall() {}

      int getX() {return (SimpleMobileAPO::getPosition()[0]);}
      int getY() {return (SimpleMobileAPO::getPosition()[1]);}
      unsigned getW()        {return (d);}
      unsigned getH()        {return (d);}
      int      getGraphics() {return (g);}

    private:
      int g;    //!< Image index
      unsigned d;
  };

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEBALL
