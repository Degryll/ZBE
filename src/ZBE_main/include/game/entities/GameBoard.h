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

#include "ZBE/core/events/generators/util/CollisionBodies.h"

#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "game/GameReactor.h"

namespace game {

class GameBoard : public zbe::AvatarEntityFixed<zbe::Interactioner<GameReactor> > {
public:
  GameBoard(double x, double y, double width, double height, uint64_t actuatorsList) :
    zbe::AvatarEntityFixed<zbe::Interactioner<GameReactor> >(new zbe::InteractionerCommon<GameReactor, void>(std::make_shared<zbe::WeakAvatarEntityContainer<void> >(), std::make_shared<zbe::StaticLimiterAABB2D>(zbe::AABB2D({x, y}, {width, height} )),
         std::make_shared<zbe::ReactObjectCommon<GameReactor> >(),
         actuatorsList)) {}
};

} // namespace game

#endif //ZBE_MAIN_GAME_GAMEBOARD
