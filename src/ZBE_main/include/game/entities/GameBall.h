#ifndef ZBE_MAIN_GAME_GAMEBALL
#define ZBE_MAIN_GAME_GAMEBALL

#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/Position.h"
#include "ZBE/archetypes/implementations/SimplePosition.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/entities/adaptorentities/PositionableEntity.h"

namespace game{

  class GameBall: public zbe::Drawable, public zbe::SimplePosition<2>, public  zbe::SimpleSpriteEntityAdapted<zbe::Drawable>, public zbe::PositionableEntityAdapted<zbe::Position<2>, 2> {
    public:
      GameBall(int x, int y, unsigned w, unsigned h, int graphics) : SimplePosition({(double)x,(double)y}), SimpleSpriteEntityAdapted(this), PositionableEntityAdapted(this), w(w), h(h), graphics(graphics) {}
      ~GameBall(){};

    int getX() {return (SimplePosition::getPosition()[0]);}
    int getY() {return (SimplePosition::getPosition()[1]);}
    unsigned getW()        {return (w);}
    unsigned getH()        {return (h);}
    int      getGraphics() {return (graphics);}

  private:
    unsigned w; //!< width
    unsigned h; //!< height
    int graphics;    //!< Image index
  };

}  // namespace game

#endif // ZBE_MAIN_GAME_GAMEBALL
