/**
 * Copyright 2012 Batis Degryll Ludo
 * @file GameReactObjects.h
 * @since 2017-01-24
 * @date 2017-01-24
 * @author Degryll
 * @brief Simple implementations of react objects.
 */

#ifndef ZBE_MAIN_GAME_REACTOBJECTS_GAMEREACTOBJECTS
#define ZBE_MAIN_GAME_REACTOBJECTS_GAMEREACTOBJECTS

#include "ZBE/core/tools/math/collisions/ReactObject.h"

#include "game/GameReactor.h"

namespace game {

class VoidReactObject : public zbe::ReactObjectCommon<VoidReactObject, GameReactor> {
public:
  VoidReactObject() : zbe::ReactObjectCommon<VoidReactObject, GameReactor>(this) {}
};

} //namespace game

#endif //ZBE_MAIN_GAME_REACTOBJECTS_GAMEREACTOBJECTS
