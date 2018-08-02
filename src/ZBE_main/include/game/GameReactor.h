#ifndef ZBE_MAIN_GAME_GAMEREACTOR
#define ZBE_MAIN_GAME_GAMEREACTOR

#include "ZBE/core/events/generators/util/Reactor.h"
#include "ZBE/core/events/generators/util/CollisionObject.h"
#include "ZBE/core/events/generators/util/CollisionData.h"

namespace game{

//class VoidReactObject;

typedef zbe::Reactor<zbe::CollisionData, zbe::CollisionObject, void> GameReactor;

//class GameReactor {
//public:
//  virtual ~GameReactor() {}
//
//  virtual void act() {}
//};

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEREACTOR
