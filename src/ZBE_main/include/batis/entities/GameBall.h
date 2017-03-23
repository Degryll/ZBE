///**
// * Copyright 2012 Batis Degryll Ludo
// * @file GameBall.h
// * @since 2017-01-24
// * @date 2017-01-24
// * @author Degryll
// * @brief A ball for an arkanoid.
// */
//
//#ifndef ZBE_MAIN_BATIS_GAMEBALL
//#define ZBE_MAIN_BATIS_GAMEBALL
//
//#include "ZBE/archetypes/Drawable.h"
//#include "ZBE/archetypes/implementations/SimpleWideMobileAPO.h"
//#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
//#include "ZBE/entities/adaptorentities/MovableCollisionatorEntity.h"
//
//#include "game/GameReactor.h"
//#include "game/reactobjects/GameReactObjects.h"
//
//namespace batis{
//
//  class GameBall: public zbe::Drawable,
//                  public zbe::SimpleSpriteEntityAdapted<zbe::Drawable>,
//                  public zbe::SimpleWideMobileAPO<2>,
//                  public zbe::MovableCollisionatorEntityAdapted<game::GameReactor, zbe::SimpleWideMobileAPO<2>, 2> {
//    public:
//			GameBall(const GameBall&) = delete;
//      void operator=(const GameBall&) = delete;
//
//      GameBall(double x, double y, double radius, double vx, double vy, uint64_t actuators, uint64_t collisionables, int graphics, int id) :
//                  SimpleSpriteEntityAdapted(this),
//                  SimpleWideMobileAPO({x, y}, {vx, vy}, radius, actuators, collisionables),
//                  MovableCollisionatorEntityAdapted(this),
//                  g(graphics), r(radius), d(2*radius), idBall(id) {}
//
//      int64_t getX() {return ((int64_t)SimpleWideMobileAPO::getPosition()[0]-r);}
//      int64_t getY() {return ((int64_t)SimpleWideMobileAPO::getPosition()[1]-r);}
//      int64_t getW()        {return ((int64_t)d);}
//      int64_t getH()        {return ((int64_t)d);}
//      uint64_t      getGraphics() {return (g);}
//      int getId()    {return (idBall);}
//
//    private:
//      int g;    //!< Image index
//      double r;
//      double d;
//      int idBall;
//  };
//
//}  // namespace batis
//
//#endif // ZBE_MAIN_BATIS_GAMEBALL
