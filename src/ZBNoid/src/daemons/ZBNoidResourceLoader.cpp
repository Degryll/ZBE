#include "daemons/ZBNoidResourceLoader.h"

namespace zombienoid {
// Tittle screen
const char menuButton[] = "data/images/zombieball/button_001_512_128.png";
const char selcetedMenuButton[] = "data/images/zombieball/button_001_selected_512_128.png";
//Bricks
const char brickImg[] = "data/images/zombieball/braikn_64.png";
// Balls
const char ballImgNormal[] = "data/images/zombieball/zball_n.png";
const char ballImgBoomb[] = "data/images/zombieball/zball_b.png";
//bars
const char barImg[] = "data/images/zombieball/zombar_color_32.png";
const char barImgGrey[] = "data/images/zombieball/zombar_grey_32.png";
//Items
const char extraLife[] = "data/images/zombieball/zbeza_life_32.png";
const char multiplier[] = "data/images/zombieball/zbeza_tbal_32.png";
const char accelerator[] = "data/images/zombieball/zbeza_acel_32.png";
const char decelerator[] = "data/images/zombieball/zbeza_dcel_32.png";
const char bigger[] = "data/images/zombieball/zbeza_ebal_32.png";
const char smaller[] = "data/images/zombieball/zbeza_rbal_32.png";
const char magnet[] = "data/images/zombieball/zbeza_sbar_32.png";
const char points100[] = "data/images/zombieball/zbeza_pnts_100_32.png";
const char points200[] = "data/images/zombieball/zbeza_pnts_200_32.png";
const char points500[] = "data/images/zombieball/zbeza_pnts_500_32.png";
const char points999[] = "data/images/zombieball/zbeza_pnts_999_32.png";
const char pointsn5000[] = "data/images/zombieball/zbeza_pntn_32.png";
//Explosion
const char explosion[] = "data/images/zombieball/boom_002_256.png";
//Back
const char backImg[]   = "data/images/zombieball/bck.png";
//Fonts
const char fontFileName[] = "data/fonts/PublicEnemyNF.ttf";
//Font colors
const SDL_Color boomTextColor {
  255, 255, 0, 192
};
const SDL_Color textColor{255, 128, 0, 255};

void ZBNoidResourceLoader::run () {
  using namespace zbe;

  srand(time(0));

  // Joints
  auto jaeCator = std::make_shared<JointAE<Interactionator<ZombienoidReactor> > >();
  auto jaeBallConer = std::make_shared<JointAE<Interactioner<ZombienoidReactor> > >();
  auto jaeItemConer = std::make_shared<JointAE<Interactioner<ZombienoidReactor> > >();
  auto jaecAnimSprt = std::make_shared<JointAEC<AnimatedSprite> >();
  auto jaecSTextSprt = std::make_shared<JointAEC<SingleTextSprite> >();
  auto jaecMouse = std::make_shared<JointAEC<Positionable<2>, Avatar> >();

  ZBNCfg::rmJAECator.insert(ZBNCfg::CTS_JOINT, jaeCator);
  ZBNCfg::rmJAEConer.insert(ZBNCfg::BALL_CBS_JOINT, jaeBallConer);
  ZBNCfg::rmJAEConer.insert(ZBNCfg::ITEM_CBS_JOINT, jaeItemConer);
  ZBNCfg::rmJAECAnimSprt.insert(ZBNCfg::AS_JOINT, jaecAnimSprt);
  ZBNCfg::rmJAECSTextSprt.insert(ZBNCfg::ATS_JOINT, jaecSTextSprt);
  ZBNCfg::rmJAECPos2DAvt.insert(ZBNCfg::MOUSE_CONTROL_LIST, jaecMouse);

  // Lists
  auto boardActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >();
  auto itemActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated> >* > >();
  auto barActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >();
  auto ballActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > >();
  auto brickActuatorsList = std::make_shared<std::forward_list<ActuatorWrapper<ZombienoidReactor, WAEC<Avatar, Positionable<2>, Stated> >* > >();
  auto explosionActuatorsList = std::make_shared<std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WAEC<Scorer> >*> >();
  auto boardCollisionerList = std::make_shared<TicketedFAE<Interactioner<ZombienoidReactor> > >();
  auto itemList = std::make_shared<TicketedFAEC<Bouncer<2>, Avatar> >();
  auto stickerList = std::make_shared<TicketedFAEC<Stated> >();
  auto itemCollisionatorsList = std::make_shared<TicketedFAE<Interactionator<ZombienoidReactor> > >();
  auto textSpriteList = std::make_shared<TicketedFAEC<SingleTextSprite> >();
  auto titleButontextSpriteList = std::make_shared<TicketedFAEC<SingleTextSprite> >();
  auto winButontextSpriteList = std::make_shared<TicketedFAEC<SingleTextSprite> >();
  auto lostButontextSpriteList = std::make_shared<TicketedFAEC<SingleTextSprite> >();
  auto brickList = std::make_shared<TicketedFAEC<Stated, Avatar, Positionable<2> > >();
  auto brickCollisionerList = std::make_shared<TicketedFAE<Interactioner<ZombienoidReactor> > >();
  auto spawnList = std::make_shared<TicketedFAEC<Movable<2> > >();
  auto mouseControlList = std::make_shared<TicketedFAEC<Positionable<2>, Avatar> >();
  auto demagnetizeList = std::make_shared<TicketedFAEC<Positionable<2>, Avatar> >();
  auto explosionAvatarList = std::make_shared<TicketedFAEC<Avatar, Scorer> >();
  auto ballCollisionatorsList = std::make_shared<TicketedFAE<Interactionator<ZombienoidReactor> > >();
  auto ballList = std::make_shared<TicketedFAEC<Bouncer<2>, Resizable, zbe::Avatar> >();
  auto barCollisionerList = std::make_shared<TicketedFAE<Interactioner<ZombienoidReactor> > >();

  // Drawing layers
  auto itemAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto boomAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto ballAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto brickAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto barAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto boardAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto titleButonsAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto winButonsAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto lostButonsAnimatedSpriteList = std::make_shared<TicketedFAEC<AnimatedSprite> >();

  ZBNCfg::rmFLAWExplosion.insert(ZBNCfg::EXPLOSION_ACTUATORS_LIST, explosionActuatorsList);
  ZBNCfg::rmFLAWBlock.insert(ZBNCfg::BOARD_ACTUATORS_LIST, boardActuatorsList);
  ZBNCfg::rmFLAWBlock.insert(ZBNCfg::BAR_ACTUATORS_LIST, barActuatorsList);
  ZBNCfg::rmFLAWBlock.insert(ZBNCfg::BRICK_ACTUATORS_LIST, brickActuatorsList);
  ZBNCfg::rmFLAWItem.insert(ZBNCfg::ITEM_ACTUATORS_LIST, itemActuatorsList);
  ZBNCfg::rmFLAWBall.insert(ZBNCfg::BALL_ACTUATORS_LIST, ballActuatorsList);
  ZBNCfg::rmTFAECPos2DAvt.insert(ZBNCfg::DEMAGNETIZE_LIST, demagnetizeList);
  ZBNCfg::rmTFAECPos2DAvt.insert(ZBNCfg::BALL_MOUSE_CONTROL_LIST, mouseControlList);
  ZBNCfg::rmTFAECMov2D.insert(ZBNCfg::BALLSPAWN_LIST, spawnList);
  ZBNCfg::rmTFAECBncr2DAvt.insert(ZBNCfg::ITEM_LIST, itemList);
  ZBNCfg::rmTFAECStat.insert(ZBNCfg::STICKY_STATE_LIST, stickerList);
  ZBNCfg::rmTFAECStatAvtPos2D.insert(ZBNCfg::BRICK_LIST, brickList);
  ZBNCfg::rmTFAECBncr2DRszAvt.insert(ZBNCfg::BALL_LIST, ballList);
  ZBNCfg::rmTFAECSTextSprt.insert(ZBNCfg::TEXT_TS_LIST, textSpriteList);
  ZBNCfg::rmTFAECSTextSprt.insert(ZBNCfg::TITLE_BUTTONS_TS_LIST, titleButontextSpriteList);
  ZBNCfg::rmTFAECSTextSprt.insert(ZBNCfg::WIN_BUTTONS_TS_LIST, winButontextSpriteList);
  ZBNCfg::rmTFAECSTextSprt.insert(ZBNCfg::LOST_BUTTONS_TS_LIST, lostButontextSpriteList);
  ZBNCfg::rmTFAECAnimSprt.insert(ZBNCfg::BOOM_AS_LIST, boomAnimatedSpriteList);
  ZBNCfg::rmTFAECAnimSprt.insert(ZBNCfg::BOARD_AS_LIST, boardAnimatedSpriteList);
  ZBNCfg::rmTFAECAnimSprt.insert(ZBNCfg::BRICK_AS_LIST, brickAnimatedSpriteList);
  ZBNCfg::rmTFAECAnimSprt.insert(ZBNCfg::BAR_AS_LIST, barAnimatedSpriteList);
  ZBNCfg::rmTFAECAnimSprt.insert(ZBNCfg::BALL_AS_LIST, ballAnimatedSpriteList);
  ZBNCfg::rmTFAECAnimSprt.insert(ZBNCfg::TITLE_BUTTONS_AS_LIST, titleButonsAnimatedSpriteList);
  ZBNCfg::rmTFAECAnimSprt.insert(ZBNCfg::WIN_BUTTONS_AS_LIST, winButonsAnimatedSpriteList);
  ZBNCfg::rmTFAECAnimSprt.insert(ZBNCfg::LOST_BUTTONS_AS_LIST, lostButonsAnimatedSpriteList);
  ZBNCfg::rmTFAECAvtScor.insert(ZBNCfg::EXPLSION_ERASE_LIST, explosionAvatarList);
  ZBNCfg::rmTFAEConer.insert(ZBNCfg::BRICK_COLLISIONER_LIST, brickCollisionerList);
  ZBNCfg::rmTFAEConer.insert(ZBNCfg::BOARD_COLLISIONER_LIST, boardCollisionerList);
  ZBNCfg::rmTFAEConer.insert(ZBNCfg::BAR_COLLISIONER_LIST, barCollisionerList);
  ZBNCfg::rmTFAECator.insert(ZBNCfg::BOOM_COLLISIONATOR_LIST, std::make_shared<TicketedFAE<Interactionator<ZombienoidReactor> > >());
  ZBNCfg::rmTFAECator.insert(ZBNCfg::BALL_COLLISIONATOR_LIST, ballCollisionatorsList);

  // Populating joints
  // Game Draw layers front to back
  jaecAnimSprt->add(itemAnimatedSpriteList);
  jaecAnimSprt->add(boomAnimatedSpriteList);
  jaecAnimSprt->add(ballAnimatedSpriteList);
  jaecAnimSprt->add(brickAnimatedSpriteList);
  jaecAnimSprt->add(barAnimatedSpriteList);
  jaecAnimSprt->add(boardAnimatedSpriteList);

  jaecMouse->add(mouseControlList);
  jaecMouse->add(demagnetizeList);
  jaeBallConer->add(brickCollisionerList);
  jaeBallConer->add(boardCollisionerList);
  jaeBallConer->add(barCollisionerList);
  jaeItemConer->add(boardCollisionerList);
  jaeItemConer->add(barCollisionerList);
  jaeCator->add(itemCollisionatorsList);
  jaeCator->add(ballCollisionatorsList);
  jaecSTextSprt->add(textSpriteList);

  std::shared_ptr<Value<int64_t> > gameState(new SimpleValue<int64_t>(LOADGAME));
  std::shared_ptr<Value<int64_t> > lifeCountValue(new SimpleValue<int64_t>());
  std::shared_ptr<Value<int64_t> > brickCount(new SimpleValue<int64_t>(0));
  std::shared_ptr<Value<int64_t> > pointsValue(new SimpleValue<int64_t>(0));
  std::shared_ptr<Value<int64_t> > ballCount(new SimpleValue<int64_t>());
  std::shared_ptr<Value<int64_t> > stickyItemState(new SimpleValue<int64_t>(BAR_NORMAL_STATE));
  std::shared_ptr<Value<double> > mouseXPos(new SimpleValue<double>());

  ZBNCfg::rmVInt64.insert(ZBNCfg::GAMESTATE, gameState);
  ZBNCfg::rmVInt64.insert(ZBNCfg::NLIFES, lifeCountValue);
  ZBNCfg::rmVInt64.insert(ZBNCfg::NBRICKS, brickCount);
  ZBNCfg::rmVInt64.insert(ZBNCfg::NPOINTS, pointsValue);
  ZBNCfg::rmVInt64.insert(ZBNCfg::NBALLS, ballCount);
  ZBNCfg::rmVInt64.insert(ZBNCfg::STICKY_ITEM_STATE, stickyItemState);
  ZBNCfg::rmVDouble.insert(ZBNCfg::MOUSE_X_POS, mouseXPos);

  std::shared_ptr<CustomItemBuilder> itemBuilder= std::make_shared<CustomItemBuilder>(ZBNCfg::ITEM_ACTUATORS_LIST, ZBNCfg::ITEM_CBS_JOINT, ZBNCfg::ITEM_SS,
      ITEM_WIDTH, ITEM_HEIGHT, ITEM_TYPES,
      (double) ITEM_FALL_SPEED, ZBNCfg::COLLISION_TICKET,
      ZBNCfg::DRAW_TICKET, ZBNCfg::BEHAVE_TICKET, itemCollisionatorsList,
      itemAnimatedSpriteList, itemList);

  std::shared_ptr<CustomBallBuilder> ballBuilder = std::make_shared<CustomBallBuilder>(ZBNCfg::BALL_ACTUATORS_LIST, ZBNCfg::BALL_CBS_JOINT, ZBNCfg::BALL_SS, BALL_SIZE,
      BALL_SIZE_MIN, BALL_SIZE_MAX, ballCount, MAXBALLS, ZBNCfg::COLLISION_TICKET, ZBNCfg::DRAW_TICKET,
      ZBNCfg::BEHAVE_TICKET, ballCollisionatorsList,ballAnimatedSpriteList, ballList);

  std::shared_ptr<zbe::Behavior<zbe::Bouncer<2>, zbe::Resizable, zbe::Avatar> > ballMagnetizerBhv = std::make_shared<InitialBallMagnetizer<ZombienoidReactor, TicketedFAEC<Positionable<2>, Avatar>, zbe::Bouncer<2>, zbe::Resizable, zbe::Avatar> >(
     ZBNCfg::rmTFAECPos2DAvt.get(ZBNCfg::DEMAGNETIZE_LIST),
     ZBNCfg::BEHAVE_TICKET, ZBNCfg::MAGNET_TICKET, MARGIN + 64, MARGIN + 64, WIDTH - (2*MARGIN), HEIGHT,Vector2D({BAR_HEIGHT/2.0-(BALL_SIZE/2),0.0})
  );

  std::shared_ptr<Daemon> ballCreatorDaemon = std::make_shared<BehaviorDaemon<TicketedFAEC<Movable<2> >, Movable<2> > >(ballBuilder, RsrcStore<TicketedFAEC<Movable<2> > >::getInstance().get(ZBNCfg::BALLSPAWN_LIST));
  std::shared_ptr<Daemon> ballMagentizerDaemon = std::make_shared<BehaviorDaemon<TicketedFAEC<zbe::Bouncer<2>, zbe::Resizable, zbe::Avatar>, zbe::Bouncer<2>, zbe::Resizable, zbe::Avatar > >( ballMagnetizerBhv, RsrcStore<TicketedFAEC<zbe::Bouncer<2>, zbe::Resizable, zbe::Avatar> >::getInstance().get(ZBNCfg::BALL_LIST));

  ZBNCfg::rmBMov2D.insert(ZBNCfg::BALL_BUILDER, ballBuilder);
  ZBNCfg::rmBPos2D.insert(ZBNCfg::ITEM_BUILDER, itemBuilder);
  ZBNCfg::rmD.insert(ZBNCfg::BALL_BUILDER_DAEMON, ballCreatorDaemon);
  ZBNCfg::rmD.insert(ZBNCfg::BALL_MAGNETIZER_DAEMON, ballMagentizerDaemon);

  rsrcIDDic->setId(ZBNCfg::BUTTON_GRAPHICS, imgStore->loadImg(menuButton));
  rsrcIDDic->setId(ZBNCfg::SELECTED_BUTTON_GRAPHICS, imgStore->loadImg(selcetedMenuButton));

  rsrcIDDic->setId(ZBNCfg::BOARD_GRAPHICS, imgStore->loadImg(backImg));
  rsrcIDDic->setId(ZBNCfg::ITEM_LIFE_GRAPHICS, imgStore->loadImg(extraLife));
  rsrcIDDic->setId(ZBNCfg::ITEM_MULTIPLIER_GRAPHICS, imgStore->loadImg(multiplier));
  rsrcIDDic->setId(ZBNCfg::ITEM_ACCEL_GRAPHICS, imgStore->loadImg(accelerator));
  rsrcIDDic->setId(ZBNCfg::ITEM_DECEL_GRAPHICS, imgStore->loadImg(decelerator));
  rsrcIDDic->setId(ZBNCfg::ITEM_BIGGER_GRAPHICS, imgStore->loadImg(bigger));
  rsrcIDDic->setId(ZBNCfg::ITEM_SMALLER_GRAPHICS, imgStore->loadImg(smaller));
  rsrcIDDic->setId(ZBNCfg::ITEM_MAGNET_GRAPHICS, imgStore->loadImg(magnet));
  rsrcIDDic->setId(ZBNCfg::ITEM_P100_GRAPHICS, imgStore->loadImg(points100));
  rsrcIDDic->setId(ZBNCfg::ITEM_P200_GRAPHICS, imgStore->loadImg(points200));
  rsrcIDDic->setId(ZBNCfg::ITEM_P500_GRAPHICS, imgStore->loadImg(points500));
  rsrcIDDic->setId(ZBNCfg::ITEM_P999_GRAPHICS, imgStore->loadImg(points999));
  rsrcIDDic->setId(ZBNCfg::ITEM_PN5000_GRAPHICS, imgStore->loadImg(pointsn5000));

  rsrcIDDic->setId(ZBNCfg::BRICK_GRAHPICS, imgStore->loadImg(brickImg));

  rsrcIDDic->setId(ZBNCfg::BAR_GRAPHICS, imgStore->loadImg(barImg));
  rsrcIDDic->setId(ZBNCfg::BAR_GRAPHICS_GREY, imgStore->loadImg(barImgGrey));

  rsrcIDDic->setId(ZBNCfg::BALL_N_GRAPHICS, imgStore->loadImg(ballImgNormal));
  rsrcIDDic->setId(ZBNCfg::BALL_B_GRAPHICS, imgStore->loadImg(ballImgBoomb));
  rsrcIDDic->setId(ZBNCfg::EXPLODE_GRAPHICS, imgStore->loadImg(explosion));

  rsrcIDDic->setId(ZBNCfg::BOOM_TEXT_FONT, textFontStore->loadFont(fontFileName, TEXT_B_SIZE, boomTextColor));
  rsrcIDDic->setId(ZBNCfg::TEXT_FONT, textFontStore->loadFont(fontFileName, TEXT_F_SIZE, textColor));

  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > brickSS(new SimpleSpriteSheet(rsrcIDDic->getId(ZBNCfg::BRICK_GRAHPICS)));
  ZBNCfg::rmSSheetAnimSprt.insert(ZBNCfg::BRICK_SS, brickSS);

  ImgDef buttonGraphics;
  buttonGraphics.frameAmount = BUTTON_FRAMES;
  buttonGraphics.regionOffset = BUTTON_DISPLACEMENT;
  buttonGraphics.frameTime = BUTTON_FRAMETIME;
  buttonGraphics.region = BUTTON_REGION;
  buttonGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::BUTTON_GRAPHICS);

  MultiSpriteSheet* buttonSheet = new MultiSpriteSheet(BUTTON_STATES, buttonGraphics);
  buttonGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::SELECTED_BUTTON_GRAPHICS);
  buttonSheet->setSprite(1, buttonGraphics);

  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > buttonSS(buttonSheet);
  ZBNCfg::rmSSheetAnimSprt.insert(ZBNCfg::BUTTON_SS, buttonSS);

  ImgDef boardGraphics;
  boardGraphics.frameAmount = BOARD_FRAMES;
  boardGraphics.regionOffset = BOARD_DISPLACEMENT;
  boardGraphics.frameTime = BOARD_FRAMETIME;
  boardGraphics.region = BOARD_REGION;
  boardGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::BOARD_GRAPHICS);

  MultiSpriteSheet* boardSheet = new MultiSpriteSheet(BOARD_STATES, boardGraphics);

  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > boardSS(boardSheet);
  ZBNCfg::rmSSheetAnimSprt.insert(ZBNCfg::BOARD_SS, boardSS);

  ImgDef itemGraphics;
  itemGraphics.frameAmount = ITEM_FRAMES;
  itemGraphics.regionOffset = ITEM_DISPLACEMENT;
  itemGraphics.frameTime = ITEM_FRAMETIME;
  itemGraphics.region = ITEM_REGION;
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_LIFE_GRAPHICS);

  MultiSpriteSheet* itemSheet = new MultiSpriteSheet(ITEM_TYPES, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_MULTIPLIER_GRAPHICS);
  itemSheet->setSprite(1, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_ACCEL_GRAPHICS);
  itemSheet->setSprite(2, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_DECEL_GRAPHICS);
  itemSheet->setSprite(3, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_BIGGER_GRAPHICS);
  itemSheet->setSprite(4, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_SMALLER_GRAPHICS);
  itemSheet->setSprite(5, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_MAGNET_GRAPHICS);
  itemSheet->setSprite(6, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P100_GRAPHICS);
  itemSheet->setSprite(7, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P200_GRAPHICS);
  itemSheet->setSprite(8, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P500_GRAPHICS);
  itemSheet->setSprite(9, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P999_GRAPHICS);
  itemSheet->setSprite(10, itemGraphics);
  itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_PN5000_GRAPHICS);
  itemSheet->setSprite(11, itemGraphics);

  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > itemSS(itemSheet);
  ZBNCfg::rmSSheetAnimSprt.insert(ZBNCfg::ITEM_SS, itemSS);

  ImgDef barGrapDef;
  barGrapDef.frameAmount = BAR_FRAMES;
  barGrapDef.regionOffset = BAR_DISPLACEMENT;
  barGrapDef.frameTime = BAR_FRAMETIME;
  barGrapDef.region = BAR_REGION;
  barGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BAR_GRAPHICS);

  MultiSpriteSheet* barSheet = new MultiSpriteSheet(2, barGrapDef);
  barGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BAR_GRAPHICS_GREY);
  barSheet->setSprite(1,barGrapDef);

  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > barSS(barSheet);
  ZBNCfg::rmSSheetAnimSprt.insert(ZBNCfg::BAR_SS, barSS);

  ImgDef ballGrapDef;
  ballGrapDef.frameAmount = BALL_FRAMES;
  ballGrapDef.regionOffset = BALL_DISPLACEMENT;
  ballGrapDef.frameTime = BALL_FRAMETIME;
  ballGrapDef.region = BALL_REGION;
  ballGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BALL_N_GRAPHICS);

  MultiSpriteSheet* ballSheet = new MultiSpriteSheet(2, ballGrapDef);
  ballGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BALL_B_GRAPHICS);
  ballSheet->setSprite(BALL_BOOM_STATE,ballGrapDef);

  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > ballSS(ballSheet);
  ZBNCfg::rmSSheetAnimSprt.insert(ZBNCfg::BALL_SS, ballSS);

  ImgDef explosionGrapDef;
  explosionGrapDef.frameAmount = EXPLOSION_FRAMES;
  explosionGrapDef.regionOffset = EXPLOSION_DISPLACEMENT;
  explosionGrapDef.frameTime = EXPLOSION_FRAMETIME;
  explosionGrapDef.region = EXPLOSION_REGION;
  explosionGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::EXPLODE_GRAPHICS);

  MultiSpriteSheet* explosionSheet = new MultiSpriteSheet(1, explosionGrapDef);

  std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > explosionSS(explosionSheet);
  ZBNCfg::rmSSheetAnimSprt.insert(ZBNCfg::EXPLSION_SS, explosionSS);

}

}
