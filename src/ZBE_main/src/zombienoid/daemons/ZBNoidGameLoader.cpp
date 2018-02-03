/**
 * Copyright ZBNoidGameLoader Batis Degryll Ludo
 * @file ZBNoidTitleBuilder.cpp
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief .
 */

#include "zombienoid/daemons/ZBNoidGameLoader.h"

namespace zombienoid {

void ZBNoidGameLoader::run() {
  using namespace zbe;

  // entities
  // wrappers--------------------------------------------------------------------------------------------------

  std::shared_ptr<AEC<Positionable<2>, Avatar> > aecp2a;
  std::shared_ptr<AEC<AnimatedSprite> > aecas;
  std::shared_ptr<AEC<SingleTextSprite> > aecsts;
  std::shared_ptr<AEC<Stated> > aecs;

  // board----------------------------------------------------------------------------------------------------

  std::shared_ptr<Element2D<ZombienoidReactor> > board(new Element2D<ZombienoidReactor>({MARGIN, MARGIN}, ZBNCfg::BOARD_ACTUATORS_LIST, BOARD_WIDTH, BOARD_HEIGHT, ZBNCfg::BOARD_SS));
  std::shared_ptr<Element2D<ZombienoidReactor> > securityBoard(new Element2D<ZombienoidReactor>({SECURITY_MARGIN, SECURITY_MARGIN},ZBNCfg::BOARD_ACTUATORS_LIST, SECURITY_WIDTH, SECURITY_HEIGHT, ZBNCfg::BOARD_SS));

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > boardCollisionerAdaptor(new BoardConerAdaptor<ZombienoidReactor>(board));
  setAdaptor(board, boardCollisionerAdaptor);

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > securityBoardCollisionerAdaptor(new BoardConerAdaptor<ZombienoidReactor>(securityBoard));
  setAdaptor(securityBoard, securityBoardCollisionerAdaptor);

  std::shared_ptr<Adaptor<AnimatedSprite> > boardSpriteAdaptor(new Element2DDisplacedAnimatedSpriteAdaptor<ZombienoidReactor>(board, BOARD_SPRITE_DISPLACEMENT));
  setAdaptor(board, boardSpriteAdaptor);

  wrapAEC(&aecas, board);

  board->addToList(ZBNCfg::COLLISION_TICKET, ZBNCfg::rmTFAEConer.get(ZBNCfg::BOARD_COLLISIONER_LIST)->push_front(board));
  board->addToList(ZBNCfg::DRAW_TICKET, ZBNCfg::rmTFAECAnimSprt.get(ZBNCfg::BOARD_AS_LIST)->push_front(aecas));

  securityBoard->addToList(ZBNCfg::COLLISION_TICKET, ZBNCfg::rmTFAEConer.get(ZBNCfg::BOARD_COLLISIONER_LIST)->push_front(securityBoard));
  // bar------------------------------------------------------------------------------------------------------

  std::shared_ptr<Element2D<ZombienoidReactor> > bar(new Element2D<ZombienoidReactor>({(WIDTH-BAR_I_WIDTH)/2, HEIGHT-BAR_MARGIN-(BAR_HEIGHT/2)},   ZBNCfg::BAR_ACTUATORS_LIST, BAR_I_WIDTH, BAR_HEIGHT, ZBNCfg::BAR_SS));

  std::shared_ptr<Adaptor<AnimatedSprite> > barSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(bar));
  setAdaptor(bar, barSpriteAdaptor);

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > barCollisionerAdaptor(new BarConerAdaptor<ZombienoidReactor>(bar));
  setAdaptor(bar, barCollisionerAdaptor);

  wrapAEC(&aecas, bar);
  wrapAEC(&aecp2a, bar);
  wrapAEC(&aecs, bar);

  bar->addToList(ZBNCfg::COLLISION_TICKET, ZBNCfg::rmTFAEConer.get(ZBNCfg::BAR_COLLISIONER_LIST)->push_front(bar));
  bar->addToList(ZBNCfg::DRAW_TICKET, ZBNCfg::rmTFAECAnimSprt.get(ZBNCfg::BAR_AS_LIST)->push_front(aecas));
  bar->addToList(ZBNCfg::BEHAVE_TICKET, ZBNCfg::rmTFAECPos2DAvt.get(ZBNCfg::BALL_MOUSE_CONTROL_LIST)->push_front(aecp2a));
  bar->addToList(ZBNCfg::STICKY_LIST_TICKET, ZBNCfg::rmTFAECStat.get(ZBNCfg::STICKY_STATE_LIST)->push_front(aecs));

  // ball spawner---------------------------------------------------------------------------------------------

  for(unsigned i = 0; i < INITBALLS; i++) {
    // int64_t vel = 600;
    // double vAngleL = (rand()%1800)+900;
    // vAngleL/=10;
    // double vAngleR = rand()%100;
    // vAngleR/=1000;
    // double vAngle = vAngleL + vAngleR;
    // int64_t vx = sin(vAngle*PI/180)*vel;
    // int64_t vy = cos(vAngle*PI/180)*vel;

    Mobile<2>* spawnData = new SimpleMobile<2>();
    spawnData->setPosition({WIDTH/2.0, HEIGHT-BAR_MARGIN-BAR_HEIGHT-(BALL_SIZE/2)});//HEIGHT*5.0/6.0});
    //spawnData->setVelocity({(double)vx, (double)vy});
    spawnData->setVelocity({0.0, -600.0});
    Movable<2>* spawnAvatar = new BaseMovable<2>(spawnData);
    std::shared_ptr<AEFixed<Movable<2> > > spawner = std::make_shared<AEFixed<Movable<2> > >(spawnAvatar);
    std::shared_ptr<AEC<Movable<2> > > aecm2;
    wrapAEC(&aecm2, spawner);
    ZBNCfg::rmTFAECMov2D.get(ZBNCfg::BALLSPAWN_LIST)->push_front(aecm2);
  }

  // HUD
  std::shared_ptr<LifeCounter> lifeCountEnt(new LifeCounter(TEXT_BOX_MARGIN, TEXT_BOX_MARGIN, TEXT_CHAR_W * LIFE_BOX_CHARS, TEXT_CHAR_H, LIFE_BOX_CHARS, rsrcIDDic->getId(ZBNCfg::TEXT_FONT),  ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES)));
  std::shared_ptr<LifeCounter> pointsEnt(new LifeCounter(WIDTH - (POINT_BOX_CHARS * TEXT_CHAR_W) - TEXT_BOX_MARGIN, TEXT_BOX_MARGIN, POINT_BOX_CHARS * TEXT_CHAR_W, TEXT_CHAR_H, POINT_BOX_CHARS, rsrcIDDic->getId(ZBNCfg::TEXT_FONT),  ZBNCfg::rmVInt64.get(ZBNCfg::NPOINTS)));

  wrapAEC(&aecsts, lifeCountEnt);

  ZBNCfg::rmTFAECSTextSprt.get(ZBNCfg::TEXT_TS_LIST)->push_front(aecsts);

  wrapAEC(&aecsts, pointsEnt);

  ZBNCfg::rmTFAECSTextSprt.get(ZBNCfg::TEXT_TS_LIST)->push_front(aecsts);

  ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE)->setValue(GAMELOADSUCCESS);

}

} //namespace zombienoid
