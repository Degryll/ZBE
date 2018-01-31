/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidTitleBuilder.cpp
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief .
 */

#include "zombienoid/daemons/ZBNoidLevelLoader.h"

namespace zombienoid {

void ZBNoidLevelLoader::run() {
  using namespace zbe;

  // entities
  // wrappers--------------------------------------------------------------------------------------------------

  std::shared_ptr<AEC<AnimatedSprite> > aecas;
  std::shared_ptr<AEC<Stated> > aecs;

  // bricks---------------------------------------------------------------------------------------------------
  // bricks counter---------------------------------------------------------------------------------------------

  for(int i = 0; i < NBRICKS_X; i++) {
    for(int j = 0; j < NBRICKS_Y; j++) {

      std::shared_ptr<AEC<Stated, Avatar, Positionable<2> > > aecsap2;
      std::shared_ptr<AEC<AnimatedSprite> > aecas;

      // int state = (rand() % (BRICK_MAX_LEVEL + SPECIAL_STATES) - SPECIAL_STATES);
      // const int NO_BRICK = -1;
      // const int BOOMBIZER_BRICK = -2;
      int state = (rand() % (BRICK_MAX_LEVEL + 1)-SPECIAL_STATES);
      if(state == -1){
          continue;
      }
      if(state == -2){
          state = BRICK_BOOMBIZER_STATE;
      }
      // Adaptar las constantes de posicion de ladrillos (margin, brick_x_margin, etc...) a las usadas en html (margin, pad, border ...)
      std::shared_ptr<Element2D<ZombienoidReactor> > brick(new CElement2D<ZombienoidReactor>( ZBNCfg::rmVInt64.get(ZBNCfg::NBRICKS), {(double)(BRICK_WIDTH*i)+MARGIN + (BRICK_WIDTH/2) + BRICKS_X_MARGIN, (double)BRICKS_Y_MARGIN+(double)(BRICK_HEIGHT*j)+MARGIN + (BRICK_HEIGHT/2)}, ZBNCfg::BRICK_ACTUATORS_LIST, (double)BRICK_WIDTH, (double)BRICK_HEIGHT, ZBNCfg::BRICK_SS));
      std::shared_ptr<Adaptor<AnimatedSprite> > brickSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(brick));
      setAdaptor(brick, brickSpriteAdaptor);
      brick->setState( state );

      std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > brickCollisionerAdaptor(new BlockConerAdaptor<ZombienoidReactor>(brick, BRICK_BOOMBIZER_STATE));
      setAdaptor(brick, brickCollisionerAdaptor);

      wrapAEC(&aecas, brick);
      wrapAEC(&aecsap2, brick);

      brick->addToList(ZBNCfg::COLLISION_TICKET, ZBNCfg::rmTFAEConer.get(ZBNCfg::BRICK_COLLISIONER_LIST)->push_front(brick));
      brick->addToList(ZBNCfg::DRAW_TICKET, ZBNCfg::rmTFAECAnimSprt.get(ZBNCfg::BRICK_AS_LIST)->push_front(aecas));
      brick->addToList(ZBNCfg::BEHAVE_TICKET, ZBNCfg::rmTFAECStatAvtPos2D.get(ZBNCfg::BRICK_LIST)->push_front(aecsap2));
    }
  }

  // ball-----------------------------------------------------------------------------------------------------

  ZBNCfg::rmD.get(ZBNCfg::BALL_BUILDER_DAEMON)->run();

  ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES)->setValue(INITIAL_LIFES);

  ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE)->setValue(LEVELLOADSUCCESS);
}

} //namespace zombienoid
