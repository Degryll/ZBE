/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameBoard.h
 * @since 2017-01-25
 * @date 2017-01-25
 * @author Degryll Batis Ludo
 * @brief The gameboard map for an arkanoid.
 */

#ifndef ZBE_MAIN_GAME_GAMEBOARD
#define ZBE_MAIN_GAME_GAMEBOARD

#include <cstdint>
#include <memory>

#include "game/GameReactor.h"
#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/entities/adaptorentities/CollisionerEntity.h"
#include "ZBE/core/entities/avatars/implementations/SimpleCollisioner.h"
#include "ZBE/reactobjects/VoidReactObject.h"

namespace game {

class GameBoard : public zbe::CollisionerEntity<GameReactor> {
public:
  GameBoard(double width, double height, uint64_t actuatorsList)
    : c(new zbe::SimpleCollisioner<GameReactor>(std::make_shared<zbe::StaticLimiterAABB2D<GameReactor> >(zbe::AABB2D(zbe::AABB2D({0.0, 0.0}, {width, height} ))),
         std::make_shared<zbe::VoidReactObject<GameReactor> >(),
         actuatorsList)) {}

  std::shared_ptr<zbe::Collisioner<GameReactor> > getCollisioner() {return (c);}

private:
  std::shared_ptr<zbe::Collisioner<GameReactor> > c;
};

} // namespace game

#endif //ZBE_MAIN_GAME_GAMEBOARD
