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
#include "ZBE/core/entities/avatars/Collisioner.h"

namespace game {

class GameBoard : public zbe::CollisionerCommon<GameBoard, GameReactor> {
public:
  GameBoard(double width, double height, uint64_t actuatorsList)
    : CollisionerCommon(this, std::make_shared<zbe::StaticLimiterAABB2D<GameReactor> >(zbe::AABB2D(zbe::AABB2D({0, 0}, {width, height} ))),
         std::make_shared<VoidReactObject>(),
         actuatorsList) {}
};

} // namespace game

#endif //ZBE_MAIN_GAME_GAMEBOARD
