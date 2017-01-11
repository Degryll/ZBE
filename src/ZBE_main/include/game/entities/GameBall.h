#ifndef ZBE_MAIN_GAME_GAMEBALL
#define ZBE_MAIN_GAME_GAMEBALL

#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/implementations/SimpleDrawable.h"
#include "ZBE/archetypes/Position.h"
#include "ZBE/archetypes/implementations/SimplePosition.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/entities/adaptorentities/PositionableEntity.h"

namespace game{

  class GameBall: public zbe::SimpleDrawable, public zbe::SimplePosition<2>, public  zbe::SimpleSpriteEntityAdapted<zbe::Drawable>, public zbe::PositionableEntityAdapted<zbe::Position<2>, 2> {
    public:
      GameBall(int x, int y, unsigned w, unsigned h, int graphics) : SimpleDrawable(x,y,w,h,graphics), SimplePosition(), SimpleSpriteEntityAdapted(this), PositionableEntityAdapted(this) {}
      ~GameBall(){};
  };

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEBALL
