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
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/avatars/SingleSprite.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/implementations/SimplePositionPO.h"
#include "ZBE/entities/avatars/implementations/BasePositionable.h"
#include "ZBE/entities/avatars/Positionable.h"

#include "game/GameReactor.h"

namespace game {

class GameBlock :  public zbe::Drawable,
                   public zbe::SimplePositionPO<2>,
                   public zbe::AvatarEntityAdapted<zbe::SingleSprite>,
                   public zbe::AvatarEntityAdapted<zbe::Interactioner<GameReactor> >,
                   public zbe::AvatarEntityFixed<zbe::Positionable<2> >{
public:
  GameBlock(double x, double y, double width, double height, uint64_t graphics, uint64_t actuatorsList)
  : SimplePositionPO<2>({x, y}, actuatorsList),
    w(width), h(height), g(graphics) {
      zbe::AvatarEntityFixed<zbe::Positionable<2> >::setAvatar(new zbe::BasePositionable<2>(this));
    }

  int64_t getX()    {return (int64_t)SimplePositionPO::getPosition()[0];}
  int64_t getY()    {return (int64_t)SimplePositionPO::getPosition()[1];}
  int64_t getW()    {return (w);}
  int64_t getH()    {return (h);}
  uint64_t getGraphics() {return (g);}

private:
  int64_t w;
  int64_t h;
  uint64_t g;
};

} // namespace game

#endif //ZBE_MAIN_GAME_GAMEBLOCK
