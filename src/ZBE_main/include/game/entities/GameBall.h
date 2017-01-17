#ifndef ZBE_MAIN_GAME_GAMEBALL
#define ZBE_MAIN_GAME_GAMEBALL

#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/Position.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/entities/adaptorentities/PositionableEntity.h"
#include "ZBE/entities/adaptorentities/MovableEntity.h"

#include "game/GameReactor.h"

namespace game{

  class GameBall: public zbe::Drawable, public zbe::SimpleMobile<2>,
                  public  zbe::SimpleSpriteEntityAdapted<zbe::Drawable>,
                  public zbe::PositionableEntityAdapted<zbe::Position<2>, 2>,
                  public zbe::MovableEntityAdapted<zbe::Mobile<2>, 2> {
    public:
      GameBall(int x, int y, unsigned w, unsigned h, int graphics) :
                  SimpleMobile({(double)x,(double)y}),
                  SimpleSpriteEntityAdapted(this),
                  PositionableEntityAdapted(this),
                  MovableEntityAdapted(this),
                  w(w), h(h), graphics(graphics) {}

      ~GameBall(){};

      int getX() {return (SimpleMobile::getPosition()[0]);}
      int getY() {return (SimpleMobile::getPosition()[1]);}
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
