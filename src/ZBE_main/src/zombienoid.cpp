/**
 * Copyright 2012 Batis Degryll Ludo
 * @file zombienoid.cpp
 * @since 2017-12-13
 * @date 2017-12-13
 * @author degryll batis ludo
 * @brief Zombienoid main.
 */

#include "zombienoid.h"

#include <memory>

#include "zombienoid/ZBNoid.h"

namespace zombienoid {

int zombienoidmain(int, char*[]) {
  using namespace zbe;

  //Fonts
  const char fontFileName[] = "data/fonts/PublicEnemyNF.ttf";

  const int64_t INITIAL_LIFES = 3;
  double BALL_SIZE_MIN = 0.25;
  double BALL_SIZE_MAX = 2;
  double BALL_SIZE_STEP = 0.25;
  double BALL_XPLODE_RATIO = 64.0;

  srand(time(0));

  ZBNCfg::initIds();

  SDLWindow window(WIDTH, HEIGHT);
  std::shared_ptr<SDLImageStore> imgStore = std::make_shared<SDLImageStore>(window.getRenderer());

  std::shared_ptr<RsrcIDDictionary> rsrcIDDic = std::make_shared<RsrcIDDictionary>(20);
  ZBNoidResourceLoader resourceLoader(rsrcIDDic, imgStore);

  SDLTextFontStore textFontStore(imgStore, window.getRenderer());

  resourceLoader.run();

  std::shared_ptr<DaemonMaster> eventGenerator(new DaemonMaster());
  std::shared_ptr<DaemonMaster> commonBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> reactBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> drawMaster(new DaemonMaster());

  SDLEventDispatcher& sdlEDispatcher = SDLEventDispatcher::getInstance();
  InputBuffer* inputBuffer = sdlEDispatcher.getInputBuffer();
  std::shared_ptr<InputEventGenerator> ieg(new InputEventGenerator(inputBuffer, ZBNCfg::INPUTEVENT));

  std::shared_ptr<TimeEventGenerator> teg(new TimeEventGenerator(ZBNCfg::TIMEEVENT));

  std::shared_ptr<InteractionGenerator> iaeg(new InteractionGenerator(ZBNCfg::CTS_JOINT, ZBNCfg::COLLISIONEVENT, new BaseCollisionSelector<ZombienoidReactor>()));

  eventGenerator->addDaemon(ieg);
  eventGenerator->addDaemon(teg);
  eventGenerator->addDaemon(iaeg);

  ResourceManager<JointAE<Collisionator<ZombienoidReactor> > >& rmct = ResourceManager<JointAE<Collisionator<ZombienoidReactor> > >::getInstance();
  std::shared_ptr<JointAE<Collisionator<ZombienoidReactor> > > ctsJoint(new JointAE<Collisionator<ZombienoidReactor> >());
  rmct.insert(ZBNCfg::CTS_JOINT, ctsJoint);

  ResourceManager<JointAE<Collisioner<ZombienoidReactor> > >& rmcn = ResourceManager<JointAE<Collisioner<ZombienoidReactor> > >::getInstance();
  std::shared_ptr<JointAE<Collisioner<ZombienoidReactor> > > ballCBSJoint(new JointAE<Collisioner<ZombienoidReactor> >());
  rmcn.insert(ZBNCfg::BALL_CBS_JOINT, ballCBSJoint);
  std::shared_ptr<JointAE<Collisioner<ZombienoidReactor> > > itemCBSJoint(new JointAE<Collisioner<ZombienoidReactor> >());
  rmcn.insert(ZBNCfg::ITEM_CBS_JOINT, itemCBSJoint);

  ResourceManager<JointAEC<AnimatedSprite> >& rmas = ResourceManager<JointAEC<AnimatedSprite> >::getInstance();
  std::shared_ptr<JointAEC<AnimatedSprite> > asJoint (new JointAEC<AnimatedSprite>());
  rmas.insert(ZBNCfg::AS_JOINT, asJoint);

  ResourceManager<JointAEC<SingleTextSprite> >& rmJAECSTS = ResourceManager<JointAEC<SingleTextSprite> >::getInstance();
  std::shared_ptr<JointAEC<SingleTextSprite> > atsJoint (new JointAEC<SingleTextSprite>());
  rmJAECSTS.insert(ZBNCfg::ATS_JOINT, atsJoint);

  ResourceManager<SpriteSheet<AnimatedSprite> >& rmss = ResourceManager<SpriteSheet<AnimatedSprite> >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >& rmact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* > >& rmawlabs = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* > >::getInstance();
  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > >& rmawlabss = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > >::getInstance();

  zombienoid::ExitInputHandler terminator;
  ieg->addHandler(ZBEK_ESCAPE, &terminator);

  //drawing----------------------------------------------------------------------------------------------------
  std::shared_ptr<Daemon> drawerDaemon(new  BehaviorDaemon<AnimatedSprite, JointAEC<AnimatedSprite> >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(&window, imgStore), ZBNCfg::AS_JOINT));
  std::shared_ptr<Daemon> writerDaemon(new  BehaviorDaemon<SingleTextSprite, JointAEC<SingleTextSprite> >(std::make_shared<SingleTextSDLDrawer>(&window, &textFontStore), ZBNCfg::ATS_JOINT));
  drawMaster->addDaemon(drawerDaemon);
  drawMaster->addDaemon(writerDaemon);

  //wrappers--------------------------------------------------------------------------------------------------

  std::shared_ptr<AEC<Positionable<2>, Avatar> > aecp2a;
  std::shared_ptr<AEC<AnimatedSprite> > aecas;
  std::shared_ptr<AEC<SingleTextSprite> > aecsts;

  //board----------------------------------------------------------------------------------------------------

  ImgSrcDef boardGraphics;
  boardGraphics.frameAmount = 8;
  boardGraphics.frameDisplacemet = Vector2D({800.0,0.0});
  boardGraphics.frameTime = 16000;
  boardGraphics.intialRegion = Region2D({0.0,0.0},{800.0,600.0});
  boardGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::BOARD_GRAPHICS);

  MultiSpriteSheet* boardSheet = new MultiSpriteSheet(2, boardGraphics);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > boardSS(boardSheet);
  rmss.insert(ZBNCfg::BOARD_SS, boardSS);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > boardAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > > boardActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* >());

  rmact.insert(ZBNCfg::BOARD_ACTUATORS_LIST, boardActuatorsList);

  std::shared_ptr<Element2D<ZombienoidReactor> > board(new Element2D<ZombienoidReactor>({MARGIN, MARGIN}, ZBNCfg::BOARD_ACTUATORS_LIST, WIDTH - (MARGIN * 2), HEIGHT /*- (MARGIN * 2)*/, ZBNCfg::BOARD_SS));

  double secondMargin = MARGIN - BALL_SIZE_MAX * BALL_SIZE;
  std::shared_ptr<Element2D<ZombienoidReactor> > securityBoard(new Element2D<ZombienoidReactor>({secondMargin, secondMargin},ZBNCfg::BOARD_ACTUATORS_LIST, WIDTH - (secondMargin * 2), HEIGHT * 2, ZBNCfg::BOARD_SS));

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > boardCollisionerAdaptor(new BoardConerAdaptor<ZombienoidReactor>(board));
  setAdaptor(board, boardCollisionerAdaptor);

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > securityBoardCollisionerAdaptor(new BoardConerAdaptor<ZombienoidReactor>(securityBoard));
  setAdaptor(securityBoard, securityBoardCollisionerAdaptor);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > boardCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());
  std::shared_ptr<Adaptor<AnimatedSprite> > boardSpriteAdaptor(new Element2DDisplacedAnimatedSpriteAdaptor<ZombienoidReactor>(board, Vector2D({0, 0})));
  setAdaptor(board, boardSpriteAdaptor);

  wrapAEC(&aecas, board);

  board->addToList(ZBNCfg::COLLISION_TICKET, boardCollisionerList->push_front(board));
  board->addToList(ZBNCfg::DRAW_TICKET, boardAnimatedSpriteList->push_front(aecas));

  securityBoard->addToList(ZBNCfg::COLLISION_TICKET, boardCollisionerList->push_front(securityBoard));

  ballCBSJoint->add(boardCollisionerList);
  itemCBSJoint->add(boardCollisionerList);

  //Items --------------------
  ResourceManager<TicketedFAEC<Movable<2> > > & rmm2 = ResourceManager<TicketedFAEC<Movable<2> > >::getInstance();
  std::shared_ptr<TicketedFAEC<Movable<2> > > itemList(new TicketedFAEC<Movable<2> >());
  rmm2.insert(ZBNCfg::ITEM_LIST, itemList);

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* > > itemActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* >());

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* itemAgainsBoardEraser = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated> >(new EraserActuator<ZombienoidReactor, InteractionTester >());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* itemAgainsBarEraser   = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated> >(new EraserActuator<ZombienoidReactor, CustomVector>());
  itemActuatorsList->push_front(itemAgainsBoardEraser);
  itemActuatorsList->push_front(itemAgainsBarEraser);

  rmawlabs.insert(ZBNCfg::ITEM_ACTUATORS_LIST, itemActuatorsList);

  std::shared_ptr<Daemon> itemULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2> > >(std::make_shared<UniformLinearMotion<2> >(), ZBNCfg::ITEM_LIST));
  commonBehaviorMaster->addDaemon(itemULM);

  ImgSrcDef itemGraphics;
  itemGraphics.frameAmount = 1;
  itemGraphics.frameDisplacemet = Vector2D({0.0,0.0});
  itemGraphics.frameTime = 1000;
  itemGraphics.intialRegion = Region2D({0.0,0.0},{32.0,64.0});
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_LIFE_GRAPHICS);

  MultiSpriteSheet* itemSheet = new MultiSpriteSheet(ITEM_TYPES, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_MULTIPLIER_GRAPHICS);
  itemSheet->setImgSrcDef(1,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_ACCEL_GRAPHICS);
  itemSheet->setImgSrcDef(2,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_DECEL_GRAPHICS);
  itemSheet->setImgSrcDef(3,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_BIGGER_GRAPHICS);
  itemSheet->setImgSrcDef(4,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_SMALLER_GRAPHICS);
  itemSheet->setImgSrcDef(5,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_MAGNET_GRAPHICS);
  itemSheet->setImgSrcDef(6,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P100_GRAPHICS);
  itemSheet->setImgSrcDef(7,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P200_GRAPHICS);
  itemSheet->setImgSrcDef(8,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P500_GRAPHICS);
  itemSheet->setImgSrcDef(9,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P999_GRAPHICS);
  itemSheet->setImgSrcDef(10,itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_PN5000_GRAPHICS);
  itemSheet->setImgSrcDef(11,itemGraphics);


  std::shared_ptr<SpriteSheet<AnimatedSprite> > itemSS(itemSheet);
  rmss.insert(ZBNCfg::ITEM_SS, itemSS);

  std::shared_ptr<TicketedFAE<Collisionator<ZombienoidReactor> > > itemCollisionatorsList(new TicketedFAE<Collisionator<ZombienoidReactor> >());
  ctsJoint->add(itemCollisionatorsList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > itemAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  std::shared_ptr<CustomItemBuilder> itemBuilder= std::make_shared<CustomItemBuilder>(ZBNCfg::ITEM_ACTUATORS_LIST, ZBNCfg::ITEM_CBS_JOINT, ZBNCfg::ITEM_SS,
                                                                                      ITEM_WIDTH, ITEM_HEIGHT, ITEM_TYPES,
                                                                                      (double) ITEM_FALL_SPEED , ZBNCfg::COLLISION_TICKET,
                                                                                      ZBNCfg::DRAW_TICKET, ZBNCfg::BEHAVE_TICKET, itemCollisionatorsList,
                                                                                      itemAnimatedSpriteList, itemList);

  //bricks---------------------------------------------------------------------------------------------------

  //bricks counter---------------------------------------------------------------------------------------------
  std::shared_ptr<Value<int64_t> > brickCount(new SimpleValue<int64_t>(0));

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > > brickActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* >());

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* brickEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Stated>, WAEC<Avatar, Positionable<2>, Stated> >(new BrickHitStateActuator<ZombienoidReactor, Solid>(-1,10,-1));
  brickActuatorsList->push_front(brickEraserWrapper);

  rmact.insert(ZBNCfg::BRICK_ACTUATORS_LIST, brickActuatorsList);



  std::shared_ptr<SpriteSheet<AnimatedSprite> > brickSS(new SimpleSpriteSheet(rsrcIDDic->getId(ZBNCfg::BRICK_GRAHPICS)));

  rmss.insert(ZBNCfg::BRICK_SS, brickSS);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > brickCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());
  ballCBSJoint->add(brickCollisionerList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > brickAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  ResourceManager<TicketedFAEC<Stated, Avatar, Positionable<2> > >& rmsam2 = ResourceManager<TicketedFAEC<Stated, Avatar, Positionable<2> > >::getInstance();
  std::shared_ptr<TicketedFAEC<Stated, Avatar, Positionable<2> > > brickList(new TicketedFAEC<Stated, Avatar, Positionable<2> >());
  rmsam2.insert(ZBNCfg::BRICK_LIST, brickList);

  std::shared_ptr<Daemon> brickEraserLT(new PunisherDaemon<Behavior<Stated, Avatar, Positionable<2> >, TicketedFAEC<Stated, Avatar, Positionable<2> > >(std::make_shared<BrickEraser>(0, BRICK_ITEM_SUCCES, BRICK_ITEM_TOTAL, itemBuilder), ZBNCfg::BRICK_LIST));
  reactBehaviorMaster->addDaemon(brickEraserLT);
  for(int i = 0; i < NBRICKS_X; i++) {
    for(int j = 0; j < NBRICKS_Y; j++) {

      std::shared_ptr<AEC<Stated, Avatar, Positionable<2> > > aecsap2;
      std::shared_ptr<AEC<AnimatedSprite> > aecas;

      int state = (rand() % (BRICK_MAX_LEVEL + 1)-SPECIAL_STATES);
      if(state == -1){
          continue;
      }
      if(state == -2){
          state = BRICK_BOOMBIZER_STATE;
      }
      std::shared_ptr<Element2D<ZombienoidReactor> > brick(new CElement2D<ZombienoidReactor>(brickCount, {(double)(BRICK_WIDTH*i)+MARGIN + (BRICK_WIDTH/2) + BRICKS_X_MARGIN, (double)BRICKS_Y_MARGIN+(double)(BRICK_HEIGHT*j)+MARGIN + (BRICK_HEIGHT/2)}, ZBNCfg::BRICK_ACTUATORS_LIST, (double)BRICK_WIDTH, (double)BRICK_HEIGHT, ZBNCfg::BRICK_SS));
      std::shared_ptr<Adaptor<AnimatedSprite> > brickSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(brick));
      setAdaptor(brick, brickSpriteAdaptor);
      brick->setState( state );

      std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > brickCollisionerAdaptor(new BlockConerAdaptor<ZombienoidReactor>(brick, BRICK_BOOMBIZER_STATE));
      setAdaptor(brick, brickCollisionerAdaptor);

      wrapAEC(&aecas, brick);
      wrapAEC(&aecsap2, brick);

      brick->addToList(ZBNCfg::COLLISION_TICKET, brickCollisionerList->push_front(brick));
      brick->addToList(ZBNCfg::DRAW_TICKET, brickAnimatedSpriteList->push_front(aecas));
      brick->addToList(ZBNCfg::BEHAVE_TICKET, brickList->push_front(aecsap2));
    }
  }

  //ball spawner---------------------------------------------------------------------------------------------
  ResourceManager<TicketedFAEC<Movable<2> > > & rmaecM2d = ResourceManager<TicketedFAEC<Movable<2> > >::getInstance();
  std::shared_ptr<TicketedFAEC<Movable<2> > > spawnList(new TicketedFAEC<Movable<2> >());
  rmaecM2d.insert(ZBNCfg::BALLSPAWN_LIST, spawnList);

  for(int i = 0; i < NBALLS; i++) {
    int64_t vt = 600;
    double vAngleL = (rand()%1800)+900;
    vAngleL/=10;
    double vAngleR = rand()%100;
    vAngleR/=1000;
    double vAngle = vAngleL + vAngleR;
    int64_t vx = sin(vAngle*PI/180)*vt;
    int64_t vy = cos(vAngle*PI/180)*vt;

    Mobile<2>* spawnData = new SimpleMobile<2>();
    spawnData->setPosition({WIDTH/2.0, HEIGHT*5.0/6.0});
    spawnData->setVelocity({(double)vx, (double)vy});
    Movable<2>* spawnAvatar = new BaseMovable<2>(spawnData);
    std::shared_ptr<AEFixed<Movable<2> > > spawner = std::make_shared<AEFixed<Movable<2> > >(spawnAvatar);
    std::shared_ptr<AEC<Movable<2> > > aecm2;
    wrapAEC(&aecm2, spawner);
    spawnList->push_front(aecm2);
  }
  //bar------------------------------------------------------------------------------------------------------
  std::shared_ptr<Value<double> > mouseXPos(new SimpleValue<double>());

  ResourceManager<JointAEC<Positionable<2>, Avatar> >& rmjp2a = ResourceManager<JointAEC<Positionable<2>, Avatar > >::getInstance();
  std::shared_ptr<JointAEC<Positionable<2>, Avatar> > p2aJoint(new JointAEC<Positionable<2>, Avatar>());
  rmjp2a.insert(ZBNCfg::MOUSE_CONTROL_LIST, p2aJoint);
  std::shared_ptr<TicketedFAEC<Positionable<2>, Avatar> > mouseControlList(new TicketedFAEC<Positionable<2> , Avatar>());
  p2aJoint->add(mouseControlList);

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > > barActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* >());
  rmact.insert(ZBNCfg::BAR_ACTUATORS_LIST, barActuatorsList);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > barCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());
  ballCBSJoint->add(barCollisionerList);
  itemCBSJoint->add(barCollisionerList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > barAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());



  ImgSrcDef barGrapDef;
  barGrapDef.frameAmount = 1;
  barGrapDef.frameDisplacemet = Vector2D({0.0,0.0});
  barGrapDef.frameTime = 1000;
  barGrapDef.intialRegion = Region2D({0.0,0.0},{161.0,32.0});
  barGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BAR_GRAPHICS);

  MultiSpriteSheet* barSheet = new MultiSpriteSheet(2, barGrapDef);
  barGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BAR_GRAPHICS_GREY);
  barSheet->setImgSrcDef(1,barGrapDef);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > barSS(barSheet);
  rmss.insert(ZBNCfg::BAR_SS, barSS);

  std::shared_ptr<Element2D<ZombienoidReactor> > bar(new Element2D<ZombienoidReactor>({(WIDTH-BAR_I_WIDTH)/2, HEIGHT-BAR_MARGIN-(BAR_HEIGHT/2)},   ZBNCfg::BAR_ACTUATORS_LIST, BAR_I_WIDTH, BAR_HEIGHT, ZBNCfg::BAR_SS));

  std::shared_ptr<Adaptor<AnimatedSprite> > barSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(bar));
  setAdaptor(bar, barSpriteAdaptor);

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > barCollisionerAdaptor(new BarConerAdaptor<ZombienoidReactor>(bar));
  setAdaptor(bar, barCollisionerAdaptor);

  wrapAEC(&aecas, bar);
  wrapAEC(&aecp2a, bar);

  bar->addToList(ZBNCfg::COLLISION_TICKET, barCollisionerList->push_front(bar));
  bar->addToList(ZBNCfg::DRAW_TICKET, barAnimatedSpriteList->push_front(aecas));
  bar->addToList(ZBNCfg::BEHAVE_TICKET, mouseControlList->push_front(aecp2a));

  std::shared_ptr<Daemon> mouseControllDaemon(new  BehaviorDaemon<Positionable<2>, JointAEC<Positionable<2>, Avatar > >(std::make_shared<XSetter>(mouseXPos), ZBNCfg::MOUSE_CONTROL_LIST ));

  //things that stick to the bar
  ResourceManager<TicketedFAEC<Positionable<2>, Avatar> >& rmp2a = ResourceManager<TicketedFAEC<Positionable<2>, Avatar > >::getInstance();
  std::shared_ptr<TicketedFAEC<Positionable<2>, Avatar> > demagnetizeList(new TicketedFAEC<Positionable<2> , Avatar>());
  p2aJoint->add(demagnetizeList);
  rmp2a.insert(ZBNCfg::DEMAGNETIZE_LIST, demagnetizeList);
  std::shared_ptr<Daemon> demagnetizeDaemon(new  BehaviorDaemon<Avatar, TicketedFAEC<Positionable<2>, Avatar> >(std::make_shared<Demagnetizer>(ZBNCfg::BEHAVE_TICKET, ZBNCfg::MAGNET_TICKET), ZBNCfg::DEMAGNETIZE_LIST));

  DaemonInputHandler demagnetizeDaemonInputHandler(demagnetizeDaemon);
  ieg->addHandler(ZBEK_MOUSE_LEFT, &demagnetizeDaemonInputHandler);

  //Points counter-------------------------------------------------------------------------------------------
  std::shared_ptr<Value<int64_t> > pointsValue(new SimpleValue<int64_t>(0));

  //ball counter---------------------------------------------------------------------------------------------
  std::shared_ptr<Value<int64_t> > ballCount(new SimpleValue<int64_t>());

  //ball-----------------------------------------------------------------------------------------------------

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > > ballActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* >());

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballCustomBouncerVoidWrapper;
  ballCustomBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Bouncer<2> >, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new CustomVectorBouncerActuator<ZombienoidReactor>());

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballMagnetWrapper;
  ballMagnetWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Positionable<2>, Avatar>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new MagnetSticker<ZombienoidReactor, TicketedFAEC<Positionable<2>, Avatar> >(demagnetizeList, ZBNCfg::BEHAVE_TICKET, ZBNCfg::MAGNET_TICKET, MARGIN + 64, MARGIN + 64, WIDTH - (2*MARGIN), HEIGHT));

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBouncerVoidWrapper;
  ballBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Bouncer<2> >, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BouncerActuator<ZombienoidReactor, Solid>());

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBouncerITWrapper;
  ballBouncerITWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Bouncer<2> >, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BouncerActuator<ZombienoidReactor, InteractionTester>());

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballEraserWrapper;
  ballEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new ConditionalEraserActuator<ZombienoidReactor>());

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballScorerWrapper;
  ballScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Scorer>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BallScorer<ZombienoidReactor>(pointsValue, P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > boomAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());
  ResourceManager<TicketedFAEC<AnimatedSprite> >& rmTFAECAS = ResourceManager<TicketedFAEC<AnimatedSprite> >::getInstance();
  rmTFAECAS.insert(ZBNCfg::BOOM_AS_LIST, boomAnimatedSpriteList);
  ResourceManager<TicketedFAE<Collisioner<ZombienoidReactor> > > & rmTFAECN = ResourceManager<TicketedFAE<Collisioner<ZombienoidReactor> > >::getInstance();
  rmTFAECN.insert(ZBNCfg::BRICK_COLLISIONER_LIST, brickCollisionerList);
  ResourceManager<TicketedFAE<Collisionator<ZombienoidReactor> > > & rmTFAECT = ResourceManager<TicketedFAE<Collisionator<ZombienoidReactor> > >::getInstance();
  rmTFAECT.insert(ZBNCfg::BOOM_COLLISIONATOR_LIST, std::make_shared<TicketedFAE<Collisionator<ZombienoidReactor> > >());

  auto explosionAvatarList = std::make_shared<TicketedFAEC<Avatar, Scorer> >();
  ResourceManager<TicketedFAEC<Avatar, Scorer> >& rmTFAECA = ResourceManager<TicketedFAEC<Avatar, Scorer> >::getInstance();
  rmTFAECA.insert(ZBNCfg::EXPLSION_ERASE_LIST, explosionAvatarList);
  std::shared_ptr<Daemon> explosionEraser(new BehaviorDaemon<Avatar, TicketedFAEC<Avatar, Scorer> >(std::make_shared<Erase>(), ZBNCfg::EXPLSION_ERASE_LIST));

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Scorer> >*> >& rsmng = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, zbe::WAEC<Scorer> >*> >::getInstance();
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Scorer> >*> > explosionActuatorsList(new std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<Scorer> >*>());
  rsmng.insert(ZBNCfg::EXPLOSION_ACTUATORS_LIST, explosionActuatorsList);
  ActuatorWrapper<ZombienoidReactor, WAEC<Scorer> >* explosionScorerWrapper;
  explosionScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Scorer>, WAEC<Scorer> >(new BallScorer<ZombienoidReactor>(pointsValue, P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));
  explosionActuatorsList->push_front(explosionScorerWrapper);

  SDL_Color boomTextColor;
  boomTextColor.r = 255;
  boomTextColor.g = 255;
  boomTextColor.b = 0;
  boomTextColor.a = 192;
  int BOOM_TEXT_FONT = textFontStore.loadFont(fontFileName, TEXT_B_SIZE, boomTextColor);
  auto ballBombizer = new BallBoombizer<ZombienoidReactor,
                                        TicketedFAEC<Avatar, Scorer>,
                                        TicketedFAE<Collisionator<ZombienoidReactor> >,
                                        TicketedFAE<Collisioner<ZombienoidReactor> >, TicketedFAEC<SingleTextSprite>,
                                        TicketedFAEC<AnimatedSprite> >
                                        (teg, ZBNCfg::COLLISIONEVENT, ZBNCfg::BOOM_TEXTSPRITE_TICKET, ZBNCfg::EXPLOSION_ACTUATORS_LIST,
                                         ZBNCfg::COLLISION_TICKET, ZBNCfg::BEHAVE_TICKET, ZBNCfg::EXPLSION_ERASE_LIST, ZBNCfg::BOOM_COLLISIONATOR_LIST,
                                         ZBNCfg::BRICK_COLLISIONER_LIST, ZBNCfg::BOOM_AS_LIST, ZBNCfg::TEXT_TS_LIST, ZBNCfg::EXPLSION_SS, BOOM_TIME,
                                         BOOM_TEXT_FONT, TEXT_B_SIZE, TEXT_B_SIZE, BALL_BOOM_STATE, BALL_XPLODE_RATIO, BALL_SIZE_STEP);
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBoombizerWrapper;
  ballBoombizerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated, Resizable>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(ballBombizer);

  ballActuatorsList->push_front(ballCustomBouncerVoidWrapper);
  ballActuatorsList->push_front(ballMagnetWrapper);
  ballActuatorsList->push_front(ballBouncerVoidWrapper);
  ballActuatorsList->push_front(ballBouncerITWrapper);
  ballActuatorsList->push_front(ballEraserWrapper);
  ballActuatorsList->push_front(ballScorerWrapper);
  ballActuatorsList->push_front(ballBoombizerWrapper);

  rmawlabss.insert(ZBNCfg::BALL_ACTUATORS_LIST, ballActuatorsList);



  ImgSrcDef ballGrapDef;
  ballGrapDef.frameAmount = 1;
  ballGrapDef.frameDisplacemet = Vector2D({0.0,0.0});
  ballGrapDef.frameTime = 1000;
  ballGrapDef.intialRegion = Region2D({0.0,0.0},{64.0,64.0});
  ballGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BALL_N_GRAPHICS);

  MultiSpriteSheet* ballSheet = new MultiSpriteSheet(2, ballGrapDef);
  ballGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BALL_B_GRAPHICS);
  ballSheet->setImgSrcDef(BALL_BOOM_STATE,ballGrapDef);

  ImgSrcDef explosionGrapDef;
  explosionGrapDef.frameAmount = 6;
  explosionGrapDef.frameDisplacemet = Vector2D({256.0,0.0});
  explosionGrapDef.frameTime = SECOND/12;
  explosionGrapDef.intialRegion = Region2D({0.0,0.0},{256.0,256.0});
  explosionGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::EXPLODE_GRAPHICS);

  MultiSpriteSheet* explosionSheet = new MultiSpriteSheet(1, explosionGrapDef);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > ballSS(ballSheet);
  rmss.insert(ZBNCfg::BALL_SS, ballSS);
  std::shared_ptr<SpriteSheet<AnimatedSprite> > explosionSS(explosionSheet);
  rmss.insert(ZBNCfg::EXPLSION_SS, explosionSS);

  std::shared_ptr<TicketedFAE<Collisionator<ZombienoidReactor> > > ballCollisionatorsList(new TicketedFAE<Collisionator<ZombienoidReactor> >());
  ctsJoint->add(ballCollisionatorsList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > ballAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  ResourceManager<TicketedFAEC<Bouncer<2>, Resizable> > & rmb2w = ResourceManager<TicketedFAEC<Bouncer<2>, Resizable> >::getInstance();
  std::shared_ptr<TicketedFAEC<Bouncer<2>, Resizable> > ballList(new TicketedFAEC<Bouncer<2>, Resizable>());
  rmb2w.insert(ZBNCfg::BALL_LIST, ballList);

  std::shared_ptr<Daemon> ballBounce(new BehaviorDaemon<Bouncer<2>, TicketedFAEC<Bouncer<2>, Resizable> >(std::make_shared<Bounce<2> >(), ZBNCfg::BALL_LIST));
  std::shared_ptr<Daemon> ballULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Bouncer<2>, Resizable> >(std::make_shared<UniformLinearMotion<2> >(), ZBNCfg::BALL_LIST));

  reactBehaviorMaster->addDaemon(ballBounce);
  commonBehaviorMaster->addDaemon(ballULM);

  std::shared_ptr<CustomBallBuilder> ballBuilder= std::make_shared<CustomBallBuilder>(ZBNCfg::BALL_ACTUATORS_LIST, ZBNCfg::BALL_CBS_JOINT, ZBNCfg::BALL_SS, BALL_SIZE, BALL_SIZE_MIN, BALL_SIZE_MAX, ballCount, MAXBALLS, ZBNCfg::COLLISION_TICKET,
                          ZBNCfg::DRAW_TICKET, ZBNCfg::BEHAVE_TICKET, ballCollisionatorsList,ballAnimatedSpriteList, ballList);

  std::shared_ptr<Daemon> ballCreatorDaemon(new  BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2>> >(ballBuilder, ZBNCfg::BALLSPAWN_LIST ));

  ballCreatorDaemon->run();

  //Game Draw layers front to back
  asJoint->add(itemAnimatedSpriteList);
  asJoint->add(boomAnimatedSpriteList);
  asJoint->add(ballAnimatedSpriteList);
  asJoint->add(brickAnimatedSpriteList);
  asJoint->add(barAnimatedSpriteList);
  asJoint->add(boardAnimatedSpriteList);

  // HUD
  //Life & point counter-----------------------------------------------------------------------------------------------------
  std::shared_ptr<TicketedFAEC<SingleTextSprite> > textSpriteList(new TicketedFAEC<SingleTextSprite>());

  ResourceManager<TicketedFAEC<SingleTextSprite> >& rmTAECSTS = ResourceManager<TicketedFAEC<SingleTextSprite> >::getInstance();
  rmTAECSTS.insert(ZBNCfg::TEXT_TS_LIST, textSpriteList);

  atsJoint->add(textSpriteList);

  SDL_Color aColor;
  aColor.r = 255;
  aColor.g = 128;
  aColor.b = 0;
  aColor.a = 255;

  int TEXT_FONT = textFontStore.loadFont(fontFileName, TEXT_F_SIZE, aColor);
  std::shared_ptr<Value<int64_t> > lifeCountValue(new SimpleValue<int64_t>(INITIAL_LIFES));
  std::shared_ptr<LifeCounter> lifeCountEnt(new LifeCounter(TEXT_BOX_MARGIN, TEXT_BOX_MARGIN, TEXT_CHAR_W * LIFE_BOX_CHARS, TEXT_CHAR_H, LIFE_BOX_CHARS, TEXT_FONT, lifeCountValue));
  std::shared_ptr<LifeCounter> pointsEnt(new LifeCounter(WIDTH - (POINT_BOX_CHARS * TEXT_CHAR_W) - TEXT_BOX_MARGIN, TEXT_BOX_MARGIN, POINT_BOX_CHARS * TEXT_CHAR_W, TEXT_CHAR_H, POINT_BOX_CHARS, TEXT_FONT, pointsValue));

  ItemCatcher<ZombienoidReactor>* catcher = new ItemCatcher<ZombienoidReactor>(pointsValue);

  double* angles = new double[2]{-30.0, 30.0};

  std::shared_ptr<Daemon> lifeItem = std::make_shared<LifeItem>(lifeCountValue,1);
  std::shared_ptr<Daemon> multiplierItem = std::make_shared<BallMultiplierItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ballBuilder, ZBNCfg::BALL_LIST, angles, 2);
  std::shared_ptr<Daemon> accelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, 1.5);
  std::shared_ptr<Daemon> decelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, 0.666666);
  std::shared_ptr<Daemon> ballMagnifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, BALL_SIZE_STEP);
  std::shared_ptr<Daemon> ballMinifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, -BALL_SIZE_STEP);
  std::shared_ptr<Daemon> magnetBarItem = std::make_shared<StickyBarItem>(bar, teg, ITEM_STICKY_TIME, 1);
  std::shared_ptr<Daemon> dummyItem = std::make_shared<DummyItem>();

  catcher->addItem(lifeItem, ITEM_POINTS);
  catcher->addItem(multiplierItem, ITEM_POINTS);
  catcher->addItem(accelItem, ITEM_POINTS);
  catcher->addItem(decelItem, ITEM_POINTS);
  catcher->addItem(ballMagnifierItem, ITEM_POINTS);
  catcher->addItem(ballMinifierItem, ITEM_POINTS);
  catcher->addItem(magnetBarItem, ITEM_POINTS);
  catcher->addItem(dummyItem, ITEM_POINTS_100);
  catcher->addItem(dummyItem, ITEM_POINTS_200);
  catcher->addItem(dummyItem, ITEM_POINTS_500);
  catcher->addItem(dummyItem, ITEM_POINTS_999);
  catcher->addItem(dummyItem, ITEM_POINTS_N5000);

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* itemCatchWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Stated>, WAEC<Avatar, Positionable<2>, Stated> >(catcher);

  barActuatorsList->push_front(itemCatchWrapper);

  wrapAEC(&aecsts, lifeCountEnt);

  textSpriteList->push_front(aecsts);

  wrapAEC(&aecsts, pointsEnt);

  textSpriteList->push_front(aecsts);

  std::shared_ptr<Daemon> lifeDaemon = std::make_shared<ZombienoidLifeSubstractor>(ballCount, lifeCountValue, ballCreatorDaemon);
  reactBehaviorMaster->addDaemon(lifeDaemon);
  reactBehaviorMaster->addDaemon(mouseControllDaemon);
  reactBehaviorMaster->addDaemon(explosionEraser);

  InputToValue mouseX(mouseXPos);
  ieg->addHandler(ZBEK_MOUSE_OFFSET_X, &mouseX);

  //--- Actuators & behaviors ---//
  // Board actuator list with id BOARD_ACTUATOR_LIST
  // Brick actuator list with id BRICK_ACTUATOR_LIST
  // BALL actuator list with id BALL_ACTUATOR_LIST
  // BAR actuator list with id BAR_ACTUATOR_LIST

  Timer *sysTimer = new SDLTimer(true);
  SysTime &sysTime = SysTime::getInstance();
  sysTime.setSystemTimer(sysTimer);

  std::shared_ptr<Daemon> prltd = std::make_shared<BasicPreLoopTimeDaemon>();
  std::shared_ptr<Daemon> prlsdl = std::make_shared<BasicPreLoopSDLDaemon>(&window);
  std::shared_ptr<Daemon> postLoop = std::make_shared<BasicPostLoopSDLDaemon>(&window);
  std::shared_ptr<DaemonMaster> preLoop(new DaemonMaster());
  preLoop->addDaemon(prlsdl);
  preLoop->addDaemon(prltd);

  MainLoop mainLoop(preLoop, postLoop, eventGenerator, commonBehaviorMaster, reactBehaviorMaster, drawMaster);

  std::shared_ptr<Daemon> failDaemon = std::make_shared<ZombienoidDeathTester>(lifeCountValue, &mainLoop);
  std::shared_ptr<Daemon> succesDaemon = std::make_shared<ZombienoidDeathTester>(brickCount, &mainLoop);
  reactBehaviorMaster->addDaemon(failDaemon);
  reactBehaviorMaster->addDaemon(succesDaemon);

  mainLoop.run();

  return 0;
}
} //namespace zombieBall
