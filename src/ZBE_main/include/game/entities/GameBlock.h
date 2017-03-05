/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameBlock.h
 * @since 2017-03-05
 * @date 2017-03-05
 * @author Degryll Batis Ludo
 * @brief A solid block.
 */

#ifndef ZBE_MAIN_GAME_GAMEBLOCK
#define ZBE_MAIN_GAME_GAMEBLOCK

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/entities/adaptorentities/CollisionerEntity.h"
#include "ZBE/core/entities/avatars/implementations/SimpleCollisioner.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/reactobjects/VoidReactObject.h"
#include "ZBE/archetypes/Drawable.h"

#include "game/GameReactor.h"

namespace game {

class GameBlock :  public zbe::Drawable,
                   public zbe::SimpleSpriteEntityAdapted<zbe::Drawable>,
  								 public zbe::CollisionerEntity<GameReactor> {
public:
  GameBlock(double x, double y, double width, double height, uint64_t graphics, uint64_t actuatorsList)
    : SimpleSpriteEntityAdapted(this),
      c(new zbe::SimpleCollisioner<GameReactor>(std::make_shared<zbe::StaticSolidAABB2D<GameReactor> >(zbe::AABB2D({x, y}, {x + width, y + height} )),
         std::make_shared<zbe::VoidReactObject<GameReactor> >(),
         actuatorsList)),
      x(x), y(y), w(width), h(height), g(graphics) {}

  std::shared_ptr<zbe::Collisioner<GameReactor> > getCollisioner() {return (c);}

  int64_t getX()    {return (x);}
  int64_t getY()    {return (y);}
  int64_t getW()    {return (w);}
  int64_t getH()    {return (h);}
  uint64_t getGraphics() {return (g);}

private:
  std::shared_ptr<zbe::Collisioner<GameReactor> > c;
  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;
  uint64_t g;
};

} // namespace game

#endif //ZBE_MAIN_GAME_GAMEBLOCK
