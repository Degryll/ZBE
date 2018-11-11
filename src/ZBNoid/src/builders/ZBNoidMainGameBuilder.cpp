/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidMainGameBuilder.cpp
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid builder of the main game (the actual game, no tittle screens).
 */

#include "builders/ZBNoidMainGameBuilder.h"

namespace zombienoid {

std::shared_ptr<zbe::Daemon> ZBNoidMainGameBuilder::build() {

  using namespace zbe;

  std::shared_ptr<DaemonMaster> preLoop(new DaemonMaster());
  std::shared_ptr<Daemon> postLoop = std::make_shared<BasicPostLoopSDLDaemon>(window);
  std::shared_ptr<DaemonMaster> eventGenerator(new DaemonMaster());
  std::shared_ptr<DaemonMaster> commonBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> reactBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> drawMaster(new DaemonMaster());;

  std::shared_ptr<MainLoop> mainLoop = std::make_shared<MainLoop>(preLoop, postLoop, eventGenerator, commonBehaviorMaster, reactBehaviorMaster, drawMaster);

  // Pre & post loop.
  std::shared_ptr<Daemon> prlsdl = std::make_shared<BasicPreLoopSDLDaemon>(window);
  preLoop->addDaemon(prlsdl);

  // Event generators
  std::shared_ptr<InputEventGenerator> ieg = std::make_shared<InputEventGenerator>(inputBuffer);
  std::shared_ptr<MappedInputStatusManager> ism = std::make_shared<MappedInputStatusManager>(ZBNCfg::INPUTEVENT);
  ieg->addManager(ism);
  std::shared_ptr<TimeEventGenerator> teg = std::make_shared<TimeEventGenerator>(ZBNCfg::TIMEEVENT);
  std::shared_ptr<InteractionGenerator> iaeg = std::make_shared<InteractionGenerator>(ZBNCfg::CTS_JOINT, ZBNCfg::COLLISIONEVENT, new BaseCollisionSelector());
  eventGenerator->addDaemon(ieg);
  eventGenerator->addDaemon(teg);
  eventGenerator->addDaemon(iaeg);

  // Common behaviors
  std::shared_ptr<Daemon> itemULM(new BehaviorDaemon<TicketedFAEC<Bouncer<2>, Avatar>, Movable<2> >(std::make_shared<UniformLinearMotion<2> >(), RsrcStore<TicketedFAEC<Bouncer<2>, Avatar> >::getInstance().get(ZBNCfg::ITEM_LIST)));
  std::shared_ptr<Daemon> ballULM(new BehaviorDaemon<TicketedFAEC<Bouncer<2>, Resizable, Avatar>, Movable<2> >(std::make_shared<UniformLinearMotion<2> >(), RsrcStore<TicketedFAEC<Bouncer<2>, Resizable, Avatar> >::getInstance().get(ZBNCfg::BALL_LIST)));
  commonBehaviorMaster->addDaemon(itemULM);
  commonBehaviorMaster->addDaemon(ballULM);

  // React behaviors
  std::shared_ptr<Daemon> failDaemon = std::make_shared<ZombienoidDeathTester>( ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES), mainLoop, ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE), MAINGAMEOVER);
  std::shared_ptr<Daemon> succesDaemon = std::make_shared<ZombienoidDeathTester>( ZBNCfg::rmVInt64.get(ZBNCfg::NBRICKS), mainLoop, ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE), MAINGAMEWIN);
  std::shared_ptr<Daemon> ballBounce = std::make_shared<BehaviorDaemon<TicketedFAEC<Bouncer<2>, Resizable, Avatar>, Bouncer<2> > >(std::make_shared<Bounce<2> >(), RsrcStore<TicketedFAEC<Bouncer<2>, Resizable, Avatar> >::getInstance().get(ZBNCfg::BALL_LIST));
  std::shared_ptr<Daemon> brickEraserLT = std::make_shared<BehaviorDaemon<TicketedFAEC<Stated, Avatar, Positionable<2> >, Stated, Avatar, Positionable<2> > >(std::make_shared<BrickEraser>(BRK_HIT_LOWLIMIT, BRICK_ITEM_SUCCES, BRICK_ITEM_TOTAL, ZBNCfg::rmBPos2D.get(ZBNCfg::ITEM_BUILDER)), RsrcStore<TicketedFAEC<Stated, Avatar, Positionable<2> > >::getInstance().get(ZBNCfg::BRICK_LIST));
  std::shared_ptr<DaemonMaster> ballInitializerDmn(new DaemonMaster());
  ballInitializerDmn->addDaemon(ZBNCfg::rmD.get(ZBNCfg::BALL_BUILDER_DAEMON));
  ballInitializerDmn->addDaemon(ZBNCfg::rmD.get(ZBNCfg::BALL_MAGNETIZER_DAEMON));
  std::shared_ptr<Daemon> lifeDaemon = std::make_shared<ZombienoidLifeSubstractor>( ZBNCfg::rmVInt64.get(ZBNCfg::NBALLS),  ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES), ballInitializerDmn);
  std::shared_ptr<Daemon> mouseControllDaemon = std::make_shared<BehaviorDaemon<JointAEC<Positionable<2>, Avatar >, Positionable<2> > >(std::make_shared<XSetter>( ZBNCfg::rmVDouble.get(ZBNCfg::MOUSE_X_POS)), RsrcStore<JointAEC<Positionable<2>, Avatar > >::getInstance().get(ZBNCfg::MOUSE_CONTROL_LIST));
  std::shared_ptr<Daemon> demagnetizeDaemon = std::make_shared<BehaviorDaemon<TicketedFAEC<Positionable<2>, Avatar>, Avatar > >(std::make_shared<Demagnetizer>(ZBNCfg::BEHAVE_TICKET, ZBNCfg::MAGNET_TICKET), RsrcStore<TicketedFAEC<Positionable<2>, Avatar> >::getInstance().get(ZBNCfg::DEMAGNETIZE_LIST));
  std::shared_ptr<Daemon> explosionEraser = std::make_shared<BehaviorDaemon<TicketedFAEC<Avatar, Scorer>, Avatar > >(std::make_shared<Erase>(), RsrcStore<TicketedFAEC<Avatar, Scorer> >::getInstance().get(ZBNCfg::EXPLSION_ERASE_LIST));
  reactBehaviorMaster->addDaemon(failDaemon);
  reactBehaviorMaster->addDaemon(succesDaemon);
  reactBehaviorMaster->addDaemon(ballBounce);
  reactBehaviorMaster->addDaemon(brickEraserLT);
  reactBehaviorMaster->addDaemon(lifeDaemon);
  reactBehaviorMaster->addDaemon(mouseControllDaemon);
  reactBehaviorMaster->addDaemon(explosionEraser);

  // Drawers
  std::shared_ptr<Daemon> drawerDaemon(new  BehaviorDaemon<JointAEC<AnimatedSprite>, AnimatedSprite >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(window), RsrcStore<JointAEC<AnimatedSprite> >::getInstance().get(ZBNCfg::AS_JOINT)));
  std::shared_ptr<Daemon> writerDaemon(new  BehaviorDaemon<JointAEC<SingleTextSprite>, SingleTextSprite >(std::make_shared<SingleTextSDLDrawer>(window), RsrcStore<JointAEC<SingleTextSprite> >::getInstance().get(ZBNCfg::ATS_JOINT)));
  drawMaster->addDaemon(drawerDaemon);
  drawMaster->addDaemon(writerDaemon);

  // input handlers
  ExitInputHandler* terminator = new ExitInputHandler();
  ism->addHandler(ZBEK_ESCAPE, terminator);

  DaemonInputHandler* demagnetizeDaemonInputHandler = new DaemonInputHandler(demagnetizeDaemon);
  ism->addHandler(ZBEK_MOUSE_LEFT, demagnetizeDaemonInputHandler);

  InputToValue* mouseX = new InputToValue( ZBNCfg::rmVDouble.get(ZBNCfg::MOUSE_X_POS));
  ism->addHandler(ZBEK_MOUSE_OFFSET_X, mouseX);

  // ActuatorWrapper's
  // Items --------------------
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* itemAgainsBoardEraser = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated> >(new EraserAtor<ZombienoidReactor, InteractionTester >());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* itemAgainsBarEraser   = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated> >(new EraserAtor<ZombienoidReactor, CustomVector>());
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
  ballBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Bouncer<2> >, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BouncerSelfAtor<ZombienoidReactor, Solid>());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBouncerITWrapper;
  ballBouncerITWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Bouncer<2> >, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BouncerSelfAtor<ZombienoidReactor, InteractionTester>());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballEraserWrapper;
  ballEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Avatar>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new ConditionalEraserAtor<ZombienoidReactor>());
  ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballScorerWrapper;
  ballScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Scorer>, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BallScorer<ZombienoidReactor>( ZBNCfg::rmVInt64.get(ZBNCfg::NPOINTS), P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));
  ActuatorWrapper<ZombienoidReactor, WAEC<Scorer> >* explosionScorerWrapper;
  explosionScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WAEC<Scorer>, WAEC<Scorer> >(new BallScorer<ZombienoidReactor>( ZBNCfg::rmVInt64.get(ZBNCfg::NPOINTS), P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));
  ZBNCfg::rmFLAWExplosion.get(ZBNCfg::EXPLOSION_ACTUATORS_LIST)->push_front(explosionScorerWrapper);
  auto ballBombizer = new BallBoombizer<ZombienoidReactor,
                                        TicketedFAEC<Avatar, Scorer>,
                                        TicketedFAE<Interactionator<ZombienoidReactor> >,
                                        TicketedFAE<Interactioner<ZombienoidReactor> >, TicketedFAEC<SingleTextSprite>,
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
  std::shared_ptr<Daemon> multiplierItem = std::make_shared<BallMultiplierItem<TicketedFAEC<Bouncer<2>, Resizable, Avatar> > >(ZBNCfg::rmBMov2D.get(ZBNCfg::BALL_BUILDER), ZBNCfg::BALL_LIST, BALL_MULTIPLIER_ANGLES, BALL_MULTIPLIER_AMOUNT);
  std::shared_ptr<Daemon> accelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable, Avatar> > >(ZBNCfg::BALL_LIST, BALL_ACCELERATION_RATIO);
  std::shared_ptr<Daemon> decelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable, Avatar> > >(ZBNCfg::BALL_LIST, BALL_DECELERATION_RATIO);
  std::shared_ptr<Daemon> ballMagnifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable, Avatar> > >(ZBNCfg::BALL_LIST, BALL_SIZE_STEP);
  std::shared_ptr<Daemon> ballMinifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable, Avatar> > >(ZBNCfg::BALL_LIST, -BALL_SIZE_STEP);
  std::shared_ptr<zbe::Daemon> initDaemon = std::make_shared<BehaviorDaemon<TicketedFAEC<Stated>, Stated > >(std::make_shared<StateSetter>(BAR_STICKY_STATE), RsrcStore<TicketedFAEC<Stated> >::getInstance().get(ZBNCfg::STICKY_STATE_LIST));
  std::shared_ptr<zbe::Daemon> endDaemon = std::make_shared<BehaviorDaemon<TicketedFAEC<Stated>, Stated > >(std::make_shared<StateSetter>(BAR_NORMAL_STATE), RsrcStore<TicketedFAEC<Stated> >::getInstance().get(ZBNCfg::STICKY_STATE_LIST));
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

  return mainLoop;
}

}  // namespace zombienoid
