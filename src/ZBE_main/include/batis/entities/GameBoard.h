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

#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/avatars/Interactioner.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/reactobjects/VoidReactObject.h"

#include "game/GameReactor.h"

namespace batis {

struct Board {
  int32_t margin;
  int32_t space;
  int32_t brickWidth;
  int32_t brickHeight;
  int32_t cols;
  int32_t rows;
  int32_t brickAreaWidth;
  int32_t brickAreaHeight;
};

class GameBoard : public zbe::AvatarEntityFixed<zbe::Interactioner<game::GameReactor> > {
public:
  Board board;
  GameBoard(double x, double y, double width, double height, uint64_t actuatorsList, Board board) :
    zbe::AvatarEntityFixed<zbe::Interactioner<game::GameReactor> >(new zbe::VoidInteractioner<game::GameReactor>(std::make_shared<zbe::StaticLimiterAABB2D<game::GameReactor> >(zbe::AABB2D({x, y}, {width, height} )),
         std::make_shared<zbe::VoidReactObject<game::GameReactor> >(),
         actuatorsList)), board(board){}

};

} // namespace batis

#endif //ZBE_MAIN_GAME_GAMEBOARD
