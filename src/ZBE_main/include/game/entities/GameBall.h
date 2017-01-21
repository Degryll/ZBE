#ifndef ZBE_MAIN_GAME_GAMEBALL
#define ZBE_MAIN_GAME_GAMEBALL

#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/Position.h"
#include "ZBE/archetypes/ActivePhysicalObject.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/entities/adaptorentities/PositionableEntity.h"
#include "ZBE/entities/adaptorentities/MovableEntity.h"
//#include "ZBE/entities/adaptorentities/MovableCollisionatorEntity.h"

#include "game/GameReactor.h"

namespace game{

  class GameBall: public zbe::Drawable, public zbe::SimpleMobile<2>,
  				  public zbe::ActivePhysicalObject<GameReactor>,
                  public zbe::SimpleSpriteEntityAdapted<zbe::Drawable>,
                  public zbe::PositionableEntityAdapted<zbe::Position<2>, 2>,
                  public zbe::MovableEntityAdapted<zbe::Mobile<2>, 2> {
    public:
			GameBall(double x, double y, unsigned radius, double vx, double vy, uint64_t actuators, uint64_t collisionables, int graphics) :
                  SimpleMobile({x, y}, {vx, vy}), //CollisionObject& object, uint64_t actuators, uint64_t collisionables
                  SimpleSpriteEntityAdapted(this),
                  PositionableEntityAdapted(this),
                  MovableEntityAdapted(this),
                  o(zbe::ConstantMovingCircle<GameReactor>(zbe::Circle({x, y}, radius), {vx, vy})),
                  a(actuators), c(collisionables),
                  graphics(graphics), d(2*radius) {}

      ~GameBall(){};

      int getX() {return (SimpleMobile::getPosition()[0]);}
      int getY() {return (SimpleMobile::getPosition()[1]);}
      unsigned getW()        {return (d);}
      unsigned getH()        {return (d);}
      int      getGraphics() {return (graphics);}

      zbe::CollisionObject<GameReactor>* getCollisionObject();
      uint64_t getActuatorsList() {return (a);}
      uint64_t getCollisionablesList() {return (c);}

    private:
      zbe::ConstantMovingCircle<GameReactor> o;
      uint64_t a;
      uint64_t c;
      int graphics;    //!< Image index
      unsigned d;
  };


  zbe::CollisionObject<GameReactor>* GameBall::getCollisionObject() {
    o.getCircle().c = SimpleMobile::getPosition();
    o.getDirection() = SimpleMobile::getVelocity();

    return (&o);
  }

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEBALL
