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

  // Basic ResourceManager: List of collisionators and collisioners for collision. List of AnimatedSprite and SingleTextSprite for drawing
  auto& rmTFAECN = ResourceManager<TicketedFAE<Collisioner<ZombienoidReactor> > >::getInstance();
  auto& rmTFAECT = ResourceManager<TicketedFAE<Collisionator<ZombienoidReactor> > >::getInstance();
  auto& rmct = ResourceManager<JointAE<Collisionator<ZombienoidReactor> > >::getInstance();
  auto& rmcn = ResourceManager<JointAE<Collisioner<ZombienoidReactor> > >::getInstance();
  auto& rmTFAECAS = ResourceManager<TicketedFAEC<AnimatedSprite> >::getInstance();
  auto& rmTAECSTS = ResourceManager<TicketedFAEC<SingleTextSprite> >::getInstance();
  auto& rmas = ResourceManager<JointAEC<AnimatedSprite> >::getInstance();
  auto& rmJAECSTS = ResourceManager<JointAEC<SingleTextSprite> >::getInstance();
  // Basic ResourceManager for SpriteSheet Drawer
  auto& rmss = ResourceManager<SpriteSheet<AnimatedSprite> >::getInstance();
  // Specific ResourceManager for interactions: Actuators
  auto& rmact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >::getInstance();
  auto& rmawlabs = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* > >::getInstance();
  auto& rmawlabss = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > >::getInstance();
  auto& rsmng = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, zbe::WAEC<Scorer> >*> >::getInstance();
  // Specific ResourceManager for Behaviors
  auto& rms = ResourceManager<TicketedFAEC<Stated> >::getInstance();
  auto& rmm2 = ResourceManager<TicketedFAEC<Movable<2> > >::getInstance();
  auto& rmsam2 = ResourceManager<TicketedFAEC<Stated, Avatar, Positionable<2> > >::getInstance();
  auto& rmp2a = ResourceManager<TicketedFAEC<Positionable<2>, Avatar > >::getInstance();
  auto& rmjp2a = ResourceManager<JointAEC<Positionable<2>, Avatar > >::getInstance();
  auto& rmTFAECA = ResourceManager<TicketedFAEC<Avatar, Scorer> >::getInstance();
  auto& rmb2w = ResourceManager<TicketedFAEC<Bouncer<2>, Resizable> >::getInstance();

  // Joints
  auto ctsJoint = std::make_shared<JointAE<Collisionator<ZombienoidReactor> > >();
  auto ballCBSJoint = std::make_shared<JointAE<Collisioner<ZombienoidReactor> > >();
  auto itemCBSJoint = std::make_shared<JointAE<Collisioner<ZombienoidReactor> > >();
  auto asJoint = std::make_shared<JointAEC<AnimatedSprite> >();
  auto atsJoint = std::make_shared<JointAEC<SingleTextSprite> >();
  auto p2aJoint = std::make_shared<JointAEC<Positionable<2>, Avatar> >();

  rmct.insert(ZBNCfg::CTS_JOINT, ctsJoint);
  rmcn.insert(ZBNCfg::BALL_CBS_JOINT, ballCBSJoint);
  rmcn.insert(ZBNCfg::ITEM_CBS_JOINT, itemCBSJoint);
  rmas.insert(ZBNCfg::AS_JOINT, asJoint);
  rmJAECSTS.insert(ZBNCfg::ATS_JOINT, atsJoint);
  rmjp2a.insert(ZBNCfg::MOUSE_CONTROL_LIST, p2aJoint);

  // Lists
  auto boardActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >();
  auto itemActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* > >();
  auto barActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >();
  auto ballActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > >();
  auto brickActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >();
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Scorer> >*> > explosionActuatorsList(new std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<Scorer> >*>());
  auto boardCollisionerList = std::make_shared<TicketedFAE<Collisioner<ZombienoidReactor> > >();
  auto itemList = std::make_shared<TicketedFAEC<Movable<2> > >();
  auto stickerList = std::make_shared<TicketedFAEC<Stated> >();
  auto itemCollisionatorsList = std::make_shared<TicketedFAE<Collisionator<ZombienoidReactor> > >();
  auto textSpriteList = std::make_shared<TicketedFAEC<SingleTextSprite> >();
  auto brickList = std::make_shared<TicketedFAEC<Stated, Avatar, Positionable<2> > >();
  auto brickCollisionerList = std::make_shared<TicketedFAE<Collisioner<ZombienoidReactor> > >();
  auto spawnList = std::make_shared<TicketedFAEC<Movable<2> > >();
  auto mouseControlList = std::make_shared<TicketedFAEC<Positionable<2> , Avatar> >();
  auto demagnetizeList = std::make_shared<TicketedFAEC<Positionable<2> , Avatar> >();
  auto explosionAvatarList = std::make_shared<TicketedFAEC<Avatar, Scorer> >();
  auto ballCollisionatorsList = std::make_shared<TicketedFAE<Collisionator<ZombienoidReactor> > >();
  auto ballList = std::make_shared<TicketedFAEC<Bouncer<2>, Resizable> >();
  auto barCollisionerList = std::make_shared<TicketedFAE<Collisioner<ZombienoidReactor> > >();

  // Drawing layers
  auto itemAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto boomAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto ballAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto brickAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto barAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto boardAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();

  rsmng.insert(ZBNCfg::EXPLOSION_ACTUATORS_LIST, explosionActuatorsList);
  rmact.insert(ZBNCfg::BOARD_ACTUATORS_LIST, boardActuatorsList);
  rmact.insert(ZBNCfg::BAR_ACTUATORS_LIST, barActuatorsList);
  rmact.insert(ZBNCfg::BRICK_ACTUATORS_LIST, brickActuatorsList);
  rmawlabs.insert(ZBNCfg::ITEM_ACTUATORS_LIST, itemActuatorsList);
  rmawlabss.insert(ZBNCfg::BALL_ACTUATORS_LIST, ballActuatorsList);
  rmp2a.insert(ZBNCfg::DEMAGNETIZE_LIST, demagnetizeList);
  rmm2.insert(ZBNCfg::ITEM_LIST, itemList);
  rmm2.insert(ZBNCfg::BALLSPAWN_LIST, spawnList);
  rms.insert(ZBNCfg::STICKY_STATE_LIST, stickerList);
  rmsam2.insert(ZBNCfg::BRICK_LIST, brickList);
  rmb2w.insert(ZBNCfg::BALL_LIST, ballList);
  rmTAECSTS.insert(ZBNCfg::TEXT_TS_LIST, textSpriteList);
  rmTFAECAS.insert(ZBNCfg::BOOM_AS_LIST, boomAnimatedSpriteList);
  rmTFAECA.insert(ZBNCfg::EXPLSION_ERASE_LIST, explosionAvatarList);
  rmTFAECN.insert(ZBNCfg::BRICK_COLLISIONER_LIST, brickCollisionerList);
  rmTFAECT.insert(ZBNCfg::BOOM_COLLISIONATOR_LIST, std::make_shared<TicketedFAE<Collisionator<ZombienoidReactor> > >());

  // Populating joints

  // Game Draw layers front to back
  asJoint->add(itemAnimatedSpriteList);
  asJoint->add(boomAnimatedSpriteList);
  asJoint->add(ballAnimatedSpriteList);
  asJoint->add(brickAnimatedSpriteList);
  asJoint->add(barAnimatedSpriteList);
  asJoint->add(boardAnimatedSpriteList);

  p2aJoint->add(mouseControlList);
  p2aJoint->add(demagnetizeList);
  ballCBSJoint->add(brickCollisionerList);
  ballCBSJoint->add(boardCollisionerList);
  ballCBSJoint->add(barCollisionerList);
  itemCBSJoint->add(boardCollisionerList);
  itemCBSJoint->add(barCollisionerList);
  ctsJoint->add(itemCollisionatorsList);
  ctsJoint->add(ballCollisionatorsList);
  atsJoint->add(textSpriteList);

  std::shared_ptr<Value<int64_t> > lifeCountValue(new SimpleValue<int64_t>(INITIAL_LIFES));
  std::shared_ptr<Value<int64_t> > brickCount(new SimpleValue<int64_t>(0));
  std::shared_ptr<Value<int64_t> > pointsValue(new SimpleValue<int64_t>(0));
  std::shared_ptr<Value<int64_t> > ballCount(new SimpleValue<int64_t>());
  std::shared_ptr<Value<int64_t> > stickyItemState(new SimpleValue<int64_t>(BAR_NORMAL_STATE));
  std::shared_ptr<Value<double> > mouseXPos(new SimpleValue<double>());

  std::shared_ptr<CustomItemBuilder> itemBuilder= std::make_shared<CustomItemBuilder>(ZBNCfg::ITEM_ACTUATORS_LIST, ZBNCfg::ITEM_CBS_JOINT, ZBNCfg::ITEM_SS,
                                                                                      ITEM_WIDTH, ITEM_HEIGHT, ITEM_TYPES,
                                                                                      (double) ITEM_FALL_SPEED , ZBNCfg::COLLISION_TICKET,
                                                                                      ZBNCfg::DRAW_TICKET, ZBNCfg::BEHAVE_TICKET, itemCollisionatorsList,
                                                                                      itemAnimatedSpriteList, itemList);

  std::shared_ptr<CustomBallBuilder> ballBuilder = std::make_shared<CustomBallBuilder>(ZBNCfg::BALL_ACTUATORS_LIST, ZBNCfg::BALL_CBS_JOINT, ZBNCfg::BALL_SS, BALL_SIZE,
                                                                                      BALL_SIZE_MIN, BALL_SIZE_MAX, ballCount, MAXBALLS, ZBNCfg::COLLISION_TICKET, ZBNCfg::DRAW_TICKET,
                                                                                      ZBNCfg::BEHAVE_TICKET, ballCollisionatorsList,ballAnimatedSpriteList, ballList);

  std::shared_ptr<Daemon> ballCreatorDaemon = std::make_shared<BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2> > > >(ballBuilder, ZBNCfg::BALLSPAWN_LIST );

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
  std::shared_ptr<Daemon> failDaemon = std::make_shared<ZombienoidDeathTester>(lifeCountValue, &mainLoop);
  std::shared_ptr<Daemon> succesDaemon = std::make_shared<ZombienoidDeathTester>(brickCount, &mainLoop);
  std::shared_ptr<Daemon> ballBounce = std::make_shared<BehaviorDaemon<Bouncer<2>, TicketedFAEC<Bouncer<2>, Resizable> > >(std::make_shared<Bounce<2> >(), ZBNCfg::BALL_LIST);
  std::shared_ptr<Daemon> brickEraserLT = std::make_shared<PunisherDaemon<Behavior<Stated, Avatar, Positionable<2> >, TicketedFAEC<Stated, Avatar, Positionable<2> > > >(std::make_shared<BrickEraser>(BRK_HIT_LOWLIMIT, BRICK_ITEM_SUCCES, BRICK_ITEM_TOTAL, itemBuilder), ZBNCfg::BRICK_LIST);
  std::shared_ptr<Daemon> lifeDaemon = std::make_shared<ZombienoidLifeSubstractor>(ballCount, lifeCountValue, ballCreatorDaemon);
  std::shared_ptr<Daemon> mouseControllDaemon = std::make_shared<BehaviorDaemon<Positionable<2>, JointAEC<Positionable<2>, Avatar > > >(std::make_shared<XSetter>(mouseXPos), ZBNCfg::MOUSE_CONTROL_LIST );
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
  itemActuatorsList->push_front(itemAgainsBoardEraser);
  itemActuatorsList->push_front(itemAgainsBarEraser);

  // Bricks --------------------
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* brickEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Stated>, WAEC<Avatar, Positionable<2>, Stated> >(new BrickHitStateActuator<ZombienoidReactor, Solid>(BRK_HIT_INCREMENT, BRK_HIT_HIGHLIMIT, BRK_HIT_DEADVALUE));
  brickActuatorsList->push_front(brickEraserWrapper);

  // Balls --------------------

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
  ActuatorWrapper<ZombienoidReactor, WAEC<Scorer> >* explosionScorerWrapper;
  explosionScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Scorer>, WAEC<Scorer> >(new BallScorer<ZombienoidReactor>(pointsValue, P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));
  explosionActuatorsList->push_front(explosionScorerWrapper);
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

  ballActuatorsList->push_front(ballCustomBouncerVoidWrapper);
  ballActuatorsList->push_front(ballMagnetWrapper);
  ballActuatorsList->push_front(ballBouncerVoidWrapper);
  ballActuatorsList->push_front(ballBouncerITWrapper);
  ballActuatorsList->push_front(ballEraserWrapper);
  ballActuatorsList->push_front(ballScorerWrapper);
  ballActuatorsList->push_front(ballBoombizerWrapper);

  // Bar --------------------

  ItemCatcher<ZombienoidReactor>* catcher = new ItemCatcher<ZombienoidReactor>(pointsValue);

  std::shared_ptr<Daemon> lifeItem = std::make_shared<LifeItem>(lifeCountValue, LIFE_ITEM_AMOUNT);
  std::shared_ptr<Daemon> multiplierItem = std::make_shared<BallMultiplierItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ballBuilder, ZBNCfg::BALL_LIST, BALL_MULTIPLIER_ANGLES, BALL_MULTIPLIER_AMOUNT);
  std::shared_ptr<Daemon> accelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, BALL_ACCELERATION_RATIO);
  std::shared_ptr<Daemon> decelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, BALL_DECELERATION_RATIO);
  std::shared_ptr<Daemon> ballMagnifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, BALL_SIZE_STEP);
  std::shared_ptr<Daemon> ballMinifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ZBNCfg::BALL_LIST, -BALL_SIZE_STEP);
  std::shared_ptr<zbe::Daemon> initDaemon = std::make_shared<BehaviorDaemon<Stated, TicketedFAEC<Stated> > >(std::make_shared<StateSetter>(BAR_STICKY_STATE), ZBNCfg::STICKY_STATE_LIST);
  std::shared_ptr<zbe::Daemon> endDaemon = std::make_shared<BehaviorDaemon<Stated, TicketedFAEC<Stated> > >(std::make_shared<StateSetter>(BAR_NORMAL_STATE), ZBNCfg::STICKY_STATE_LIST);
  std::shared_ptr<Daemon> magnetBarItem = std::make_shared<StickyBarItem>(initDaemon,  endDaemon, teg, ITEM_STICKY_TIME, BAR_STICKY_STATE, BAR_NORMAL_STATE, stickyItemState);
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

  board->addToList(ZBNCfg::COLLISION_TICKET, boardCollisionerList->push_front(board));
  board->addToList(ZBNCfg::DRAW_TICKET, boardAnimatedSpriteList->push_front(aecas));

  securityBoard->addToList(ZBNCfg::COLLISION_TICKET, boardCollisionerList->push_front(securityBoard));

  //bricks---------------------------------------------------------------------------------------------------
  //bricks counter---------------------------------------------------------------------------------------------
  std::shared_ptr<SpriteSheet<AnimatedSprite> > brickSS(new SimpleSpriteSheet(rsrcIDDic->getId(ZBNCfg::BRICK_GRAHPICS)));
  rmss.insert(ZBNCfg::BRICK_SS, brickSS);

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

  for(int i = 0; i < NBALLS; i++) {
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
    spawnList->push_front(aecm2);
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

  bar->addToList(ZBNCfg::COLLISION_TICKET, barCollisionerList->push_front(bar));
  bar->addToList(ZBNCfg::DRAW_TICKET, barAnimatedSpriteList->push_front(aecas));
  bar->addToList(ZBNCfg::BEHAVE_TICKET, mouseControlList->push_front(aecp2a));
  bar->addToList(ZBNCfg::STICKY_LIST_TICKET, stickerList->push_front(aecs));

  //ball-----------------------------------------------------------------------------------------------------

  ballCreatorDaemon->run();

  // HUD
  //Life & point counter-----------------------------------------------------------------------------------------------------

  std::shared_ptr<LifeCounter> lifeCountEnt(new LifeCounter(TEXT_BOX_MARGIN, TEXT_BOX_MARGIN, TEXT_CHAR_W * LIFE_BOX_CHARS, TEXT_CHAR_H, LIFE_BOX_CHARS, rsrcIDDic->getId(ZBNCfg::TEXT_FONT), lifeCountValue));
  std::shared_ptr<LifeCounter> pointsEnt(new LifeCounter(WIDTH - (POINT_BOX_CHARS * TEXT_CHAR_W) - TEXT_BOX_MARGIN, TEXT_BOX_MARGIN, POINT_BOX_CHARS * TEXT_CHAR_W, TEXT_CHAR_H, POINT_BOX_CHARS, rsrcIDDic->getId(ZBNCfg::TEXT_FONT), pointsValue));

  wrapAEC(&aecsts, lifeCountEnt);

  textSpriteList->push_front(aecsts);

  wrapAEC(&aecsts, pointsEnt);

  textSpriteList->push_front(aecsts);

  InputToValue mouseX(mouseXPos);
  ieg->addHandler(ZBEK_MOUSE_OFFSET_X, &mouseX);

  mainLoop.run();

  return 0;
}
} //namespace zombieBall
