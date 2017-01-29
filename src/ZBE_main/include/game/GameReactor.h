#ifndef ZBE_MAIN_GAME_GAMEREACTOR
#define ZBE_MAIN_GAME_GAMEREACTOR

namespace game{

class VoidReactObject;

class GameReactor {
public:
  virtual ~GameReactor() {}

  virtual void act(VoidReactObject*) {}
};

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEREACTOR
