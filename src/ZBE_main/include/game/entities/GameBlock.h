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
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/SimpleSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleCollisioner.h"
#include "ZBE/reactobjects/VoidReactObject.h"
#include "ZBE/archetypes/Drawable.h"

#include "game/GameReactor.h"

namespace game {

class GameBlock :  public zbe::Drawable,
                   public zbe::AvatarEntityAdapted<zbe::SimpleSprite>,
                   public zbe::AvatarEntityFixed<zbe::Collisioner<GameReactor> > {
public:
  GameBlock(double x, double y, double width, double height, uint64_t graphics, uint64_t actuatorsList) :
     zbe::AvatarEntityFixed<zbe::Collisioner<GameReactor> >(new zbe::SimpleCollisioner<GameReactor>(std::make_shared<zbe::StaticSolidAABB2D<GameReactor> >(zbe::AABB2D({x, y}, {x + width, y + height} )),
                                                            std::make_shared<zbe::VoidReactObject<GameReactor> >(),
                                                            actuatorsList)),
      x(x), y(y), w(width), h(height), g(graphics) {}

  int64_t getX()    {return (x);}
  int64_t getY()    {return (y);}
  int64_t getW()    {return (w);}
  int64_t getH()    {return (h);}
  uint64_t getGraphics() {return (g);}

private:
  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;
  uint64_t g;
};

} // namespace game

#endif //ZBE_MAIN_GAME_GAMEBLOCK
