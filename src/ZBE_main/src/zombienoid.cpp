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

  ZBNCfg::initIds();

  std::shared_ptr<RsrcIDDictionary> rsrcIDDic = std::make_shared<RsrcIDDictionary>(RSRC_ID_DICT_SIZE);
  std::shared_ptr<SDLWindow> window = std::make_shared<SDLWindow>(ZBENOID_WINDOW_TITLE, WIDTH, HEIGHT);
  Timer *sysTimer = new SDLTimer(true);
  SysTime &sysTime = SysTime::getInstance();
  sysTime.setSystemTimer(sysTimer);
  SDLEventDispatcher& sdlEDispatcher = SDLEventDispatcher::getInstance();
  InputBuffer* inputBuffer = sdlEDispatcher.getInputBuffer();

  ZBNoidResourceLoader resourceLoader(rsrcIDDic, window->getImgStore(), window->getFontStore());
  resourceLoader.run();

  std::shared_ptr<DaemonMaster> preLoop(new DaemonMaster());
  std::shared_ptr<Daemon> postLoop = std::make_shared<BasicPostLoopSDLDaemon>(window);
  std::shared_ptr<DaemonMaster> eventGenerator(new DaemonMaster());
  std::shared_ptr<DaemonMaster> commonBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> reactBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> drawMaster(new DaemonMaster());;

  MainLoop mainLoop(preLoop, postLoop, eventGenerator, commonBehaviorMaster, reactBehaviorMaster, drawMaster);

  // Pre & post loop.
  std::shared_ptr<Daemon> prlsdl = std::make_shared<BasicPreLoopSDLDaemon>(window);
  std::shared_ptr<Daemon> prltd = std::make_shared<BasicPreLoopTimeDaemon>();
  preLoop->addDaemon(prlsdl);
  preLoop->addDaemon(prltd);

  // Event generators
  std::shared_ptr<InputEventGenerator> ieg(new InputEventGenerator(inputBuffer, ZBNCfg::INPUTEVENT));
  std::shared_ptr<TimeEventGenerator> teg(new TimeEventGenerator(ZBNCfg::TIMEEVENT));
  std::shared_ptr<InteractionGenerator> iaeg(new InteractionGenerator(ZBNCfg::CTS_JOINT, ZBNCfg::COLLISIONEVENT, new BaseCollisionSelector<ZombienoidReactor>()));
  eventGenerator->addDaemon(ieg);
  eventGenerator->addDaemon(teg);
  eventGenerator->addDaemon(iaeg);

  // Common behaviors
  std::shared_ptr<Daemon> itemULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2> > >(std::make_shared<UniformLinearMotion<2> >(), ZBNCfg::ITEM_LIST));
  std::shared_ptr<Daemon> ballULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Bouncer<2>, Resizable> >(std::make_shared<UniformLinearMotion<2> >(), ZBNCfg::BALL_LIST));
  commonBehaviorMaster->addDaemon(itemULM);
  commonBehaviorMaster->addDaemon(ballULM);

  // React behaviors
  std::shared_ptr<Daemon> failDaemon = std::make_shared<ZombienoidDeathTester>( ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES), &mainLoop);
  std::shared_ptr<Daemon> succesDaemon = std::make_shared<ZombienoidDeathTester>( ZBNCfg::rmVInt64.get(ZBNCfg::NBRICKS), &mainLoop);
  std::shared_ptr<Daemon> ballBounce = std::make_shared<BehaviorDaemon<Bouncer<2>, TicketedFAEC<Bouncer<2>, Resizable> > >(std::make_shared<Bounce<2> >(), ZBNCfg::BALL_LIST);
  std::shared_ptr<Daemon> brickEraserLT = std::make_shared<PunisherDaemon<Behavior<Stated, Avatar, Positionable<2> >, TicketedFAEC<Stated, Avatar, Positionable<2> > > >(std::make_shared<BrickEraser>(BRK_HIT_LOWLIMIT, BRICK_ITEM_SUCCES, BRICK_ITEM_TOTAL, ZBNCfg::rmBPos2D.get(ZBNCfg::ITEM_BUILDER)), ZBNCfg::BRICK_LIST);
  std::shared_ptr<Daemon> lifeDaemon = std::make_shared<ZombienoidLifeSubstractor>( ZBNCfg::rmVInt64.get(ZBNCfg::NBALLS),  ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES), ZBNCfg::rmD.get(ZBNCfg::BALL_BUILDER_DAEMON));
  std::shared_ptr<Daemon> mouseControllDaemon = std::make_shared<BehaviorDaemon<Positionable<2>, JointAEC<Positionable<2>, Avatar > > >(std::make_shared<XSetter>( ZBNCfg::rmVDouble.get(ZBNCfg::MOUSE_X_POS)), ZBNCfg::MOUSE_CONTROL_LIST );
  std::shared_ptr<Daemon> demagnetizeDaemon = std::make_shared<BehaviorDaemon<Avatar, TicketedFAEC<Positionable<2>, Avatar> > >(std::make_shared<Demagnetizer>(ZBNCfg::BEHAVE_TICKET, ZBNCfg::MAGNET_TICKET), ZBNCfg::DEMAGNETIZE_LIST);
  std::shared_ptr<Daemon> explosionEraser = std::make_shared<BehaviorDaemon<Avatar, TicketedFAEC<Avatar, Scorer> > >(std::make_shared<Erase>(), ZBNCfg::EXPLSION_ERASE_LIST);
  reactBehaviorMaster->addDaemon(failDaemon);
  reactBehaviorMaster->addDaemon(succesDaemon);
  reactBehaviorMaster->addDaemon(ballBounce);
  reactBehaviorMaster->addDaemon(brickEraserLT);
  reactBehaviorMaster->addDaemon(lifeDaemon);
  reactBehaviorMaster->addDaemon(mouseControllDaemon);
  reactBehaviorMaster->addDaemon(explosionEraser);

  // Drawers
  std::shared_ptr<Daemon> drawerDaemon(new  BehaviorDaemon<AnimatedSprite, JointAEC<AnimatedSprite> >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(window), ZBNCfg::AS_JOINT));
  std::shared_ptr<Daemon> writerDaemon(new  BehaviorDaemon<SingleTextSprite, JointAEC<SingleTextSprite> >(std::make_shared<SingleTextSDLDrawer>(window), ZBNCfg::ATS_JOINT));
  drawMaster->addDaemon(drawerDaemon);
  drawMaster->addDaemon(writerDaemon);

  zombienoid::ExitInputHandler terminator;
  ieg->addHandler(ZBEK_ESCAPE, &terminator);

  DaemonInputHandler demagnetizeDaemonInputHandler(demagnetizeDaemon);
  ieg->addHandler(ZBEK_MOUSE_LEFT, &demagnetizeDaemonInputHandler);

  //wrappers--------------------------------------------------------------------------------------------------

  std::shared_ptr<AEC<Positionable<2>, Avatar> > aecp2a;
  std::shared_ptr<AEC<AnimatedSprite> > aecas;
  std::shared_ptr<AEC<SingleTextSprite> > aecsts;
  std::shared_ptr<AEC<Stated> > aecs;

  // ActuatorWrapper's
  // Items --------------------
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* itemAgainsBoardEraser = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated> >(new EraserActuator<ZombienoidReactor, InteractionTester >());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* itemAgainsBarEraser   = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated> >(new EraserActuator<ZombienoidReactor, CustomVector>());
  ZBNCfg::rmFLAWItem.get(ZBNCfg::ITEM_ACTUATORS_LIST)->push_front(itemAgainsBoardEraser);
  ZBNCfg::rmFLAWItem.get(ZBNCfg::ITEM_ACTUATORS_LIST)->push_front(itemAgainsBarEraser);

  // Bricks --------------------
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* brickEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Stated>, WAEC<Avatar, Positionable<2>, Stated> >(new BrickHitStateActuator<ZombienoidReactor, Solid>(BRK_HIT_INCREMENT, BRK_HIT_HIGHLIMIT, BRK_HIT_DEADVALUE));
  ZBNCfg::rmFLAWBlock.get(ZBNCfg::BRICK_ACTUATORS_LIST)->push_front(brickEraserWrapper);

  // Balls --------------------

  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballCustomBouncerVoidWrapper;
  ballCustomBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Bouncer<2> >, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new CustomVectorBouncerActuator<ZombienoidReactor>());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballMagnetWrapper;
  ballMagnetWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Positionable<2>, Avatar>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new MagnetSticker<ZombienoidReactor, TicketedFAEC<Positionable<2>, Avatar> >(ZBNCfg::rmTFAECPos2DAvt.get(ZBNCfg::DEMAGNETIZE_LIST), ZBNCfg::BEHAVE_TICKET, ZBNCfg::MAGNET_TICKET, MARGIN + 64, MARGIN + 64, WIDTH - (2*MARGIN), HEIGHT));
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBouncerVoidWrapper;
  ballBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Bouncer<2> >, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BouncerActuator<ZombienoidReactor, Solid>());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBouncerITWrapper;
  ballBouncerITWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Bouncer<2> >, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BouncerActuator<ZombienoidReactor, InteractionTester>());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballEraserWrapper;
  ballEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new ConditionalEraserActuator<ZombienoidReactor>());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballScorerWrapper;
  ballScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Scorer>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BallScorer<ZombienoidReactor>( ZBNCfg::rmVInt64.get(ZBNCfg::NPOINTS), P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));
  ActuatorWrapper<ZombienoidReactor, WAEC<Scorer> >* explosionScorerWrapper;
  explosionScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Scorer>, WAEC<Scorer> >(new BallScorer<ZombienoidReactor>( ZBNCfg::rmVInt64.get(ZBNCfg::NPOINTS), P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));
  ZBNCfg::rmFLAWExplosion.get(ZBNCfg::EXPLOSION_ACTUATORS_LIST)->push_front(explosionScorerWrapper);
  auto ballBombizer = new BallBoombizer<ZombienoidReactor,
                                        TicketedFAEC<Avatar, Scorer>,
                                        TicketedFAE<Collisionator<ZombienoidReactor> >,
                                        TicketedFAE<Collisioner<ZombienoidReactor> >, TicketedFAEC<SingleTextSprite>,
                                        TicketedFAEC<AnimatedSprite> >
                                        (teg, ZBNCfg::COLLISIONEVENT, ZBNCfg::BOOM_TEXTSPRITE_TICKET, ZBNCfg::EXPLOSION_ACTUATORS_LIST,
                                         ZBNCfg::COLLISION_TICKET, ZBNCfg::BEHAVE_TICKET, ZBNCfg::EXPLSION_ERASE_LIST, ZBNCfg::BOOM_COLLISIONATOR_LIST,
                                         ZBNCfg::BRICK_COLLISIONER_LIST, ZBNCfg::BOOM_AS_LIST, ZBNCfg::TEXT_TS_LIST, ZBNCfg::EXPLSION_SS, BOOM_TIME,
                                         rsrcIDDic->getId(ZBNCfg::BOOM_TEXT_FONT), TEXT_B_SIZE, TEXT_B_SIZE, BALL_BOOM_STATE, BALL_XPLODE_RATIO, BALL_SIZE_STEP);
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBoombizerWrapper;
  ballBoombizerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated, Resizable>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(ballBombizer);

  ZBNCfg::rmFLAWBall.get(ZBNCfg::BALL_ACTUATORS_LIST)->push_front(ballCustomBouncerVoidWrapper);
  ZBNCfg::rmFLAWBall.get(ZBNCfg::BALL_ACTUATORS_LIST)->push_front(ballMagnetWrapper);
  ZBNCfg::rmFLAWBall.get(ZBNCfg::BALL_ACTUATORS_LIST)->push_front(ballBouncerVoidWrapper);
  ZBNCfg::rmFLAWBall.get(ZBNCfg::BALL_ACTUATORS_LIST)->push_front(ballBouncerITWrapper);
  ZBNCfg::rmFLAWBall.get(ZBNCfg::BALL_ACTUATORS_LIST)->push_front(ballEraserWrapper);
  ZBNCfg::rmFLAWBall.get(ZBNCfg::BALL_ACTUATORS_LIST)->push_front(ballScorerWrapper);
  ZBNCfg::rmFLAWBall.get(ZBNCfg::BALL_ACTUATORS_LIST)->push_front(ballBoombizerWrapper);

  // Bar --------------------

  ItemCatcher<ZombienoidReactor>* catcher = new ItemCatcher<ZombienoidReactor>( ZBNCfg::rmVInt64.get(ZBNCfg::NPOINTS));

  std::shared_ptr<Daemon> lifeItem = std::make_shared<LifeItem>( ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES), LIFE_ITEM_AMOUNT);
  std::shared_ptr<Daemon> multiplierItem = std::make_shared<BallMultiplierItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::rmBMov2D.get(ZBNCfg::BALL_BUILDER), ZBNCfg::BALL_LIST, BALL_MULTIPLIER_ANGLES, BALL_MULTIPLIER_AMOUNT);
  std::shared_ptr<Daemon> accelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, BALL_ACCELERATION_RATIO);
  std::shared_ptr<Daemon> decelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, BALL_DECELERATION_RATIO);
  std::shared_ptr<Daemon> ballMagnifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, BALL_SIZE_STEP);
  std::shared_ptr<Daemon> ballMinifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, -BALL_SIZE_STEP);
  std::shared_ptr<zbe::Daemon> initDaemon = std::make_shared<BehaviorDaemon<Stated, TicketedFAEC<Stated> > >(std::make_shared<StateSetter>(BAR_STICKY_STATE), ZBNCfg::STICKY_STATE_LIST);
  std::shared_ptr<zbe::Daemon> endDaemon = std::make_shared<BehaviorDaemon<Stated, TicketedFAEC<Stated> > >(std::make_shared<StateSetter>(BAR_NORMAL_STATE), ZBNCfg::STICKY_STATE_LIST);
  std::shared_ptr<Daemon> magnetBarItem = std::make_shared<StickyBarItem>(initDaemon,  endDaemon, teg, ITEM_STICKY_TIME, BAR_STICKY_STATE, BAR_NORMAL_STATE,  ZBNCfg::rmVInt64.get(ZBNCfg::STICKY_ITEM_STATE));
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
  ZBNCfg::rmFLAWBlock.get(ZBNCfg::BAR_ACTUATORS_LIST)->push_front(itemCatchWrapper);

  // entities
  //board----------------------------------------------------------------------------------------------------

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

  //bricks---------------------------------------------------------------------------------------------------
  //bricks counter---------------------------------------------------------------------------------------------
  std::shared_ptr<SpriteSheet<AnimatedSprite> > brickSS(new SimpleSpriteSheet(rsrcIDDic->getId(ZBNCfg::BRICK_GRAHPICS)));
  ZBNCfg::rmSSheetAnimSprt.insert(ZBNCfg::BRICK_SS, brickSS);

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

  //ball spawner---------------------------------------------------------------------------------------------

  for(unsigned i = 0; i < INITBALLS; i++) {
    int64_t vel = 600;
    double vAngleL = (rand()%1800)+900;
    vAngleL/=10;
    double vAngleR = rand()%100;
    vAngleR/=1000;
    double vAngle = vAngleL + vAngleR;
    int64_t vx = sin(vAngle*PI/180)*vel;
    int64_t vy = cos(vAngle*PI/180)*vel;

    Mobile<2>* spawnData = new SimpleMobile<2>();
    spawnData->setPosition({WIDTH/2.0, HEIGHT*5.0/6.0});
    spawnData->setVelocity({(double)vx, (double)vy});
    Movable<2>* spawnAvatar = new BaseMovable<2>(spawnData);
    std::shared_ptr<AEFixed<Movable<2> > > spawner = std::make_shared<AEFixed<Movable<2> > >(spawnAvatar);
    std::shared_ptr<AEC<Movable<2> > > aecm2;
    wrapAEC(&aecm2, spawner);
    ZBNCfg::rmTFAECMov2D.get(ZBNCfg::BALLSPAWN_LIST)->push_front(aecm2);
  }
  //bar------------------------------------------------------------------------------------------------------

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

  //ball-----------------------------------------------------------------------------------------------------

  ZBNCfg::rmD.get(ZBNCfg::BALL_BUILDER_DAEMON)->run();

  // HUD
  //Life & point counter-----------------------------------------------------------------------------------------------------

  std::shared_ptr<LifeCounter> lifeCountEnt(new LifeCounter(TEXT_BOX_MARGIN, TEXT_BOX_MARGIN, TEXT_CHAR_W * LIFE_BOX_CHARS, TEXT_CHAR_H, LIFE_BOX_CHARS, rsrcIDDic->getId(ZBNCfg::TEXT_FONT),  ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES)));
  std::shared_ptr<LifeCounter> pointsEnt(new LifeCounter(WIDTH - (POINT_BOX_CHARS * TEXT_CHAR_W) - TEXT_BOX_MARGIN, TEXT_BOX_MARGIN, POINT_BOX_CHARS * TEXT_CHAR_W, TEXT_CHAR_H, POINT_BOX_CHARS, rsrcIDDic->getId(ZBNCfg::TEXT_FONT),  ZBNCfg::rmVInt64.get(ZBNCfg::NPOINTS)));

  wrapAEC(&aecsts, lifeCountEnt);

  ZBNCfg::rmTFAECSTextSprt.get(ZBNCfg::TEXT_TS_LIST)->push_front(aecsts);

  wrapAEC(&aecsts, pointsEnt);

  ZBNCfg::rmTFAECSTextSprt.get(ZBNCfg::TEXT_TS_LIST)->push_front(aecsts);

  InputToValue mouseX( ZBNCfg::rmVDouble.get(ZBNCfg::MOUSE_X_POS));
  ieg->addHandler(ZBEK_MOUSE_OFFSET_X, &mouseX);

  mainLoop.run();

  return 0;
}
} //namespace zombieBall
