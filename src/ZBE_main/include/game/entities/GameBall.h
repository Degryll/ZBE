#ifndef ZBE_MAIN_GAME_GAMEBALL
#define ZBE_MAIN_GAME_GAMEBALL

#include "ZBE/archetypes/implementations/SimpleDrawable.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"

namespace game{

  class GameBall: public zbe::SimpleDrawable, public  zbe::SimpleSpriteEntityAdapted<zbe::Drawable>{
    public:
      GameBall(int x, int y, unsigned w, unsigned h, int graphics) : SimpleDrawable(x,y,w,h,graphics), SimpleSpriteEntityAdapted(this) {}
      ~GameBall(){};
  };

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEBALL
