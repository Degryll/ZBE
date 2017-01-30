#ifndef ZBE_MAIN_GAME_GAMEREACTOR
#define ZBE_MAIN_GAME_GAMEREACTOR

#include "ZBE/reactobjects/VoidReactObject.h"

namespace game{

class VoidReactObject;

class GameReactor {
public:
  virtual ~GameReactor() {}

  virtual void act(zbe::VoidReactObject<GameReactor>*) {}
};

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEREACTOR
