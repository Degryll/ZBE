#include "zombienoid.h"

#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"
#include "ZBE/core/daemons/Punishers.h"
#include "ZBE/core/daemons/BasicPreLoopTimeDaemon.h"

#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

#include "ZBE/core/tools/containers/ListJoint.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

#include "ZBE/core/tools/graphics/SpriteSheet.h"

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/MainLoop.h"

#include "ZBE/core/io/InputBuffer.h"

#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/archetypes/Mobile.h"

#include "ZBE/entities/avatars/InteractionTester.h"
#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/Resizable.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"

#include "ZBE/entities/Element2D.h"

#include "ZBE/events/handlers/actuators/EraserActuator.h"
#include "ZBE/events/handlers/actuators/BouncerActuator.h"
#include "ZBE/events/handlers/actuators/StateChangerActuator.h"

#include "ZBE/behaviors/Bounce.h"
#include "ZBE/behaviors/Erase.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/StateLTEraser.h"

#include "ZBE/events/handlers/actuators/ConditionalEraserActuator.h"
#include "ZBE/events/handlers/input/DaemonInputHandler.h"
#include "ZBE/events/handlers/MouseXIH.h"

#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"
#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"

#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include "ZBE/SDL/system/SDLImageStore.h"
#include "ZBE/SDL/system/SDLTextFontStore.h"

#include "ZBE/SDL/tools/SDLTimer.h"

#include "zombienoid/events/handlers/actuators/ItemCatcher.h"
#include "zombienoid/events/handlers/actuators/CustomVectorBouncerActuator.h"
#include "zombienoid/events/handlers/actuators/MagnetSticker.h"
#include "zombienoid/events/handlers/actuators/BallScorer.h"
#include "zombienoid/events/handlers/actuators/BallBoombizer.h"
#include "zombienoid/events/handlers/actuators/BrickHitStateActuator.h"

#include "zombienoid/events/handlers/ExitInputHandler.h"

#include "zombienoid/entities/adaptors/ActiveElement2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/BallCatorAdaptor.h"
#include "zombienoid/entities/adaptors/BlockConerAdaptor.h"
#include "zombienoid/entities/adaptors/BarConerAdaptor.h"
#include "zombienoid/entities/adaptors/BoardConerAdaptor.h"
#include "zombienoid/entities/adaptors/Element2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/Element2DDisplacedAnimatedSpriteAdaptor.h"

#include "zombienoid/entities/avatars/Scorer.h"

#include "zombienoid/entities/LifeCounter.h"

#include "zombienoid/daemons/items/LifeItem.h"
#include "zombienoid/daemons/items/BallMultiplierItem.h"
#include "zombienoid/daemons/items/BallAcceleratorItem.h"
#include "zombienoid/daemons/items/BallRadiusItem.h"
#include "zombienoid/daemons/items/StickyBarItem.h"

#include "zombienoid/daemons/ZombienoidDeathTester.h"
#include "zombienoid/daemons/ZombienoidLifeSubstractor.h"

#include "zombienoid/behaviors/Demagnetizer.h"
#include "zombienoid/behaviors/BrickEraser.h"
#include "zombienoid/behaviors/XSetter.h"

#include "zombienoid/behaviors/builders/BallBuilder.h"
#include "zombienoid/behaviors/builders/ItemBuilder.h"

#include "zombienoid/ZombienoidReactor.h"

#include "zombienoid/graphics/MultiSpriteSheet.h"
#include "zombienoid/graphics/SimpleSpriteSheet.h"


namespace zombienoid {

using namespace zbe;

template <typename T>
using TicketedFAE = TicketedForwardList<AvatarEntity<T> >;

template <typename ...Avatars>
using TicketedFAEC = TicketedForwardList<AvatarEntityContainer<Avatars...> >;

template <typename T>
using JointAE = ListTicketedJoint<TicketedFAE<T>, std::shared_ptr<AvatarEntity<T> > >;

template <typename ...Avatars>
using JointAEC = ListTicketedJoint<TicketedFAEC<Avatars...>, std::shared_ptr<AvatarEntityContainer<Avatars...> > >;

using InteractionGenerator = InteractionEventGenerator<
      ZombienoidReactor, CollisionSelector<ZombienoidReactor>,
      JointAE<Collisioner<ZombienoidReactor> >,
        JointAE<Collisionator<ZombienoidReactor> >
    >;

using CustomBallBuilder = BallBuilder<ZombienoidReactor, TicketedFAE<Collisionator<ZombienoidReactor> >,
              TicketedFAEC<AnimatedSprite>,
              TicketedFAEC<Bouncer<2>, Resizable> >;

using CustomItemBuilder = ItemBuilder<ZombienoidReactor, TicketedFAE<Collisionator<ZombienoidReactor> >,
              TicketedFAEC<AnimatedSprite>,
              TicketedFAEC<Movable<2> > >;

int zombienoidmain(int, char*[]) {
  enum {
    WIDTH = 1024,
    HEIGHT = 768,
    MARGIN = 32,
    NBALLS = 1,
    MAXBALLS = 1000,

    P_ACCUM_TIME = SECOND,
    P_EXTRA_ACCUM_TIME = SECOND / 4,
    POINTS_MULTIPLIER = 10,

    ITEM_TYPES = 12,
    ITEM_FALL_SPEED = 100,
    ITEM_WIDTH = 32,
    ITEM_HEIGHT = 64,

    ITEM_POINTS = 50,
    ITEM_POINTS_100 = 100,
    ITEM_POINTS_200 = 200,
    ITEM_POINTS_500 = 500,
    ITEM_POINTS_999 = 999,
    ITEM_POINTS_N5000 = -5000,

    ITEM_STICKY_TIME = SECOND*4,

    NBRICKS_X = 13,
    NBRICKS_Y = 10,
    BRICK_WIDTH = 64,
    BRICK_HEIGHT = 32,
    BRICKS_X_MARGIN = 64,
    BRICKS_Y_MARGIN = 64,
    BRICK_MAX_LEVEL = 3,
    BRICK_ITEM_SUCCES = 1,
    BRICK_ITEM_TOTAL = 10,
    SPECIAL_STATES = 2,

    BRICK_BOOMBIZER_STATE = 16,
    BALL_BOOM_STATE = 1,
    BOOM_TIME = SECOND*4,

    BALL_SIZE = 32,
    BALL_V_X = -300,
    BALL_V_Y = -300,

    BAR_I_WIDTH = 322,
    BAR_HEIGHT = 32,
    BAR_MARGIN = 32,

    TEXT_F_SIZE = 32,
    TEXT_B_SIZE = 18,
    TEXT_CHAR_W = 16,
    TEXT_CHAR_H = 30,

    LIFE_BOX_CHARS = 2,
    POINT_BOX_CHARS = 10,
    TEXT_BOX_MARGIN = 6
  };

  // Ticket ids.
  const int COLLISION_TICKET = SysIdGenerator::getId();
  const int DRAW_TICKET = SysIdGenerator::getId();
  const int BEHAVE_TICKET = SysIdGenerator::getId();
  const int MAGNET_TICKET = SysIdGenerator::getId();
  const int BOOM_TEXTSPRITE_TICKET = SysIdGenerator::getId();
  // Event ids.
  const int INPUTEVENT = SysIdGenerator::getId();
  const int TIMEEVENT = SysIdGenerator::getId();
  const int COLLISIONEVENT = SysIdGenerator::getId();
  // List joints for collisiontors, sprites and text sprites.
  const int CTS_JOINT = SysIdGenerator::getId();
  const int AS_JOINT = SysIdGenerator::getId();
  const int ATS_JOINT = SysIdGenerator::getId();
  // Actuators list.
  const int BOARD_ACTUATORS_LIST = SysIdGenerator::getId();
  const int ITEM_ACTUATORS_LIST = SysIdGenerator::getId();
  const int BRICK_ACTUATORS_LIST = SysIdGenerator::getId();
  const int BALL_ACTUATORS_LIST = SysIdGenerator::getId();
  const int EXPLOSION_ACTUATORS_LIST = SysIdGenerator::getId();
  const int BAR_ACTUATORS_LIST = SysIdGenerator::getId();
  // Behaviors list
  const int BRICK_LIST = SysIdGenerator::getId();
  const int BALLSPAWN_LIST = SysIdGenerator::getId();
  const int BALL_LIST = SysIdGenerator::getId();
  const int ITEM_LIST = SysIdGenerator::getId();
  const int MOUSE_CONTROL_LIST = SysIdGenerator::getId();
  const int DEMAGNETIZE_LIST = SysIdGenerator::getId();
  const int EXPLSION_ERASE_LIST = SysIdGenerator::getId();
  // Collisionables list
  const int BRICK_COLLISIONER_LIST = SysIdGenerator::getId();
  // Collisionables list
  const int BOOM_COLLISIONATOR_LIST = SysIdGenerator::getId();
  // Collisionables list joints
  const int BALL_CBS_JOINT = SysIdGenerator::getId();
  const int ITEM_CBS_JOINT = SysIdGenerator::getId();
  // AnimatedSprite list
  const int BOOM_AS_LIST = SysIdGenerator::getId();
  // TextSprite list
  const int TEXT_TS_LIST = SysIdGenerator::getId();
  // Sprite sheet ids
  const int ITEM_SS = SysIdGenerator::getId();
  const int BRICK_SS = SysIdGenerator::getId();
  const int BALL_SS = SysIdGenerator::getId();
  const int EXPLSION_SS = SysIdGenerator::getId();
  const int BAR_SS = SysIdGenerator::getId();
  const int BOARD_SS = SysIdGenerator::getId();


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
  const char explosion[] = "data/images/zombieball/orb_001_512.png";
  //Back
  const char backImg[]   = "data/images/zombieball/bck.png";
  //Fonts
  const char fontFileName[] = "data/fonts/PublicEnemyNF.ttf";

  const int64_t INITIAL_LIFES = 3;

  srand(time(0));

  SDLWindow window(WIDTH, HEIGHT);
  SDLImageStore imgStore(window.getRenderer());
  SDLTextFontStore textFontStore(&imgStore, window.getRenderer());

  std::shared_ptr<DaemonMaster> eventGenerator(new DaemonMaster());
  std::shared_ptr<DaemonMaster> commonBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> reactBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> drawMaster(new DaemonMaster());

  SDLEventDispatcher& sdlEDispatcher = SDLEventDispatcher::getInstance();
  InputBuffer* inputBuffer = sdlEDispatcher.getInputBuffer();
  std::shared_ptr<InputEventGenerator> ieg(new InputEventGenerator(inputBuffer, INPUTEVENT));

  std::shared_ptr<TimeEventGenerator> teg(new TimeEventGenerator(TIMEEVENT));

  std::shared_ptr<InteractionGenerator> iaeg(new InteractionGenerator(CTS_JOINT, COLLISIONEVENT, new BaseCollisionSelector<ZombienoidReactor>()));

  eventGenerator->addDaemon(ieg);
  eventGenerator->addDaemon(teg);
  eventGenerator->addDaemon(iaeg);

  ResourceManager<JointAE<Collisionator<ZombienoidReactor> > >& rmct = ResourceManager<JointAE<Collisionator<ZombienoidReactor> > >::getInstance();
  std::shared_ptr<JointAE<Collisionator<ZombienoidReactor> > > ctsJoint(new JointAE<Collisionator<ZombienoidReactor> >());
  rmct.insert(CTS_JOINT, ctsJoint);

  ResourceManager<JointAE<Collisioner<ZombienoidReactor> > >& rmcn = ResourceManager<JointAE<Collisioner<ZombienoidReactor> > >::getInstance();
  std::shared_ptr<JointAE<Collisioner<ZombienoidReactor> > > ballCBSJoint(new JointAE<Collisioner<ZombienoidReactor> >());
  rmcn.insert(BALL_CBS_JOINT, ballCBSJoint);
  std::shared_ptr<JointAE<Collisioner<ZombienoidReactor> > > itemCBSJoint(new JointAE<Collisioner<ZombienoidReactor> >());
  rmcn.insert(ITEM_CBS_JOINT, itemCBSJoint);

  ResourceManager<JointAEC<AnimatedSprite> >& rmas = ResourceManager<JointAEC<AnimatedSprite> >::getInstance();
  std::shared_ptr<JointAEC<AnimatedSprite> > asJoint (new JointAEC<AnimatedSprite>());
  rmas.insert(AS_JOINT, asJoint);

  ResourceManager<JointAEC<SingleTextSprite> >& rmJAECSTS = ResourceManager<JointAEC<SingleTextSprite> >::getInstance();
  std::shared_ptr<JointAEC<SingleTextSprite> > atsJoint (new JointAEC<SingleTextSprite>());
  rmJAECSTS.insert(ATS_JOINT, atsJoint);

  ResourceManager<SpriteSheet<AnimatedSprite> >& rmss = ResourceManager<SpriteSheet<AnimatedSprite> >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* > >& rmact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* > >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* > >& rmawlabs = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* > >::getInstance();
  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > >& rmawlabss = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > >::getInstance();

  zombienoid::ExitInputHandler terminator;
  ieg->addHandler(ZBEK_ESCAPE, &terminator);

  //drawing----------------------------------------------------------------------------------------------------
  std::shared_ptr<Daemon> drawerDaemon(new  BehaviorDaemon<AnimatedSprite, JointAEC<AnimatedSprite> >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(&window, &imgStore), AS_JOINT));
  std::shared_ptr<Daemon> writerDaemon(new  BehaviorDaemon<SingleTextSprite, JointAEC<SingleTextSprite> >(std::make_shared<SingleTextSDLDrawer>(&window, &textFontStore), ATS_JOINT));
  drawMaster->addDaemon(drawerDaemon);
  drawMaster->addDaemon(writerDaemon);

  //wrappers--------------------------------------------------------------------------------------------------

  std::shared_ptr<AvatarEntityContainer<Bouncer<2> > > aecb2;
  std::shared_ptr<AvatarEntityContainer<Movable<2> > > aecm2;
  std::shared_ptr<AvatarEntityContainer<Positionable<2>, Avatar> > aecp2a;
  std::shared_ptr<AvatarEntityContainer<Stated, Avatar> > aecsa;
  std::shared_ptr<AvatarEntityContainer<AnimatedSprite> > aecas;
  std::shared_ptr<AvatarEntityContainer<SingleTextSprite> > aecsts;

  //board----------------------------------------------------------------------------------------------------

  uint64_t BOARD_GRAPHICS = imgStore.loadImg(backImg);

  ImgSrcDef boardGraphics;
  boardGraphics.frameAmount = 8;
  boardGraphics.frameDisplacemet = Vector2D({800.0,0.0});
  boardGraphics.frameTime = 16000;
  boardGraphics.intialRegion = Region2D({0.0,0.0},{800.0,600.0});
  boardGraphics.imgSrcId = BOARD_GRAPHICS;

  MultiSpriteSheet* boardSheet = new MultiSpriteSheet(2, boardGraphics);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > boardSS(boardSheet);
  rmss.insert(BOARD_SS, boardSS);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > boardAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* > > boardActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* >());

  rmact.insert(BOARD_ACTUATORS_LIST, boardActuatorsList);

  std::shared_ptr<Element2D<ZombienoidReactor> > board(new Element2D<ZombienoidReactor>({MARGIN, MARGIN}, BOARD_ACTUATORS_LIST, WIDTH - (MARGIN * 2), HEIGHT /*- (MARGIN * 2)*/, BOARD_SS));

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > boardCollisionerAdaptor(new BoardConerAdaptor<ZombienoidReactor>(board));
  setAdaptor(board, boardCollisionerAdaptor);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > boardCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());
//Vector2D({-(WIDTH - (MARGIN * 2))/2, -(HEIGHT/2) + MARGIN })
//Vector2D({(WIDTH - (MARGIN * 2))/2, (HEIGHT/2) + MARGIN })
  std::shared_ptr<Adaptor<AnimatedSprite> > boardSpriteAdaptor(new Element2DDisplacedAnimatedSpriteAdaptor<ZombienoidReactor>(board, Vector2D({0, 0})));
  setAdaptor(board, boardSpriteAdaptor);

  wrapAEC(&aecas, board);

  board->addToList(COLLISION_TICKET, boardCollisionerList->push_front(board));
  board->addToList(DRAW_TICKET, boardAnimatedSpriteList->push_front(aecas));

  ballCBSJoint->add(boardCollisionerList);
  itemCBSJoint->add(boardCollisionerList);

  //Items --------------------
  ResourceManager<TicketedFAEC<Movable<2> > > & rmm2 = ResourceManager<TicketedFAEC<Movable<2> > >::getInstance();
  std::shared_ptr<TicketedFAEC<Movable<2> > > itemList(new TicketedFAEC<Movable<2> >());
  rmm2.insert(ITEM_LIST, itemList);

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* > > itemActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* >());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* itemAgainsBoardEraser = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Avatar>, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >(new EraserActuator<ZombienoidReactor, InteractionTester >());
  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* itemAgainsBarEraser   = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Avatar>, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >(new EraserActuator<ZombienoidReactor, CustomVector>());
  itemActuatorsList->push_front(itemAgainsBoardEraser);
  itemActuatorsList->push_front(itemAgainsBarEraser);

  rmawlabs.insert(ITEM_ACTUATORS_LIST, itemActuatorsList);

  std::shared_ptr<Daemon> itemULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2> > >(std::make_shared<UniformLinearMotion<2> >(), ITEM_LIST));
  commonBehaviorMaster->addDaemon(itemULM);

  uint64_t ITEM_LIFE_GRAPHICS = imgStore.loadImg(extraLife);
  uint64_t ITEM_MULTIPLIER_GRAPHICS = imgStore.loadImg(multiplier);
  uint64_t ITEM_ACCEL_GRAPHICS = imgStore.loadImg(accelerator);
  uint64_t ITEM_DECEL_GRAPHICS = imgStore.loadImg(decelerator);
  uint64_t ITEM_BIGGER_GRAPHICS = imgStore.loadImg(bigger);
  uint64_t ITEM_SMALLER_GRAPHICS = imgStore.loadImg(smaller);
  uint64_t ITEM_MAGNET_GRAPHICS = imgStore.loadImg(magnet);
  uint64_t ITEM_P100_GRAPHICS = imgStore.loadImg(points100);
  uint64_t ITEM_P200_GRAPHICS = imgStore.loadImg(points200);
  uint64_t ITEM_P500_GRAPHICS = imgStore.loadImg(points500);
  uint64_t ITEM_P999_GRAPHICS = imgStore.loadImg(points999);
  uint64_t ITEM_PN5000_GRAPHICS = imgStore.loadImg(pointsn5000);

  ImgSrcDef itemGraphics;
  itemGraphics.frameAmount = 1;
  itemGraphics.frameDisplacemet = Vector2D({0.0,0.0});
  itemGraphics.frameTime = 1000;
  itemGraphics.intialRegion = Region2D({0.0,0.0},{32.0,64.0});
  itemGraphics.imgSrcId = ITEM_LIFE_GRAPHICS;

  MultiSpriteSheet* itemSheet = new MultiSpriteSheet(ITEM_TYPES, itemGraphics);
  itemGraphics.imgSrcId = ITEM_MULTIPLIER_GRAPHICS;
  itemSheet->setImgSrcDef(1,itemGraphics);
  itemGraphics.imgSrcId = ITEM_ACCEL_GRAPHICS;
  itemSheet->setImgSrcDef(2,itemGraphics);
  itemGraphics.imgSrcId = ITEM_DECEL_GRAPHICS;
  itemSheet->setImgSrcDef(3,itemGraphics);
  itemGraphics.imgSrcId = ITEM_BIGGER_GRAPHICS;
  itemSheet->setImgSrcDef(4,itemGraphics);
  itemGraphics.imgSrcId = ITEM_SMALLER_GRAPHICS;
  itemSheet->setImgSrcDef(5,itemGraphics);
  itemGraphics.imgSrcId = ITEM_MAGNET_GRAPHICS;
  itemSheet->setImgSrcDef(6,itemGraphics);
  itemGraphics.imgSrcId = ITEM_P100_GRAPHICS;
  itemSheet->setImgSrcDef(7,itemGraphics);
  itemGraphics.imgSrcId = ITEM_P200_GRAPHICS;
  itemSheet->setImgSrcDef(8,itemGraphics);
  itemGraphics.imgSrcId = ITEM_P500_GRAPHICS;
  itemSheet->setImgSrcDef(9,itemGraphics);
  itemGraphics.imgSrcId = ITEM_P999_GRAPHICS;
  itemSheet->setImgSrcDef(10,itemGraphics);
  itemGraphics.imgSrcId = ITEM_PN5000_GRAPHICS;
  itemSheet->setImgSrcDef(11,itemGraphics);


  std::shared_ptr<SpriteSheet<AnimatedSprite> > itemSS(itemSheet);
  rmss.insert(ITEM_SS, itemSS);

  std::shared_ptr<TicketedFAE<Collisionator<ZombienoidReactor> > > itemCollisionatorsList(new TicketedFAE<Collisionator<ZombienoidReactor> >());
  ctsJoint->add(itemCollisionatorsList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > itemAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  std::shared_ptr<CustomItemBuilder> itemBuilder= std::make_shared<CustomItemBuilder>(ITEM_ACTUATORS_LIST, ITEM_CBS_JOINT, ITEM_SS, ITEM_WIDTH, ITEM_HEIGHT, ITEM_TYPES, (double) ITEM_FALL_SPEED , COLLISION_TICKET,
                          DRAW_TICKET, BEHAVE_TICKET, itemCollisionatorsList,itemAnimatedSpriteList, itemList);

  //bricks---------------------------------------------------------------------------------------------------

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* > > brickActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* >());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* brickEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Stated>, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >(new BrickHitStateActuator<ZombienoidReactor, Solid>(-1,10,-1));
  brickActuatorsList->push_front(brickEraserWrapper);

  rmact.insert(BRICK_ACTUATORS_LIST, brickActuatorsList);

  int BRICK_GRAHPICS = imgStore.loadImg(brickImg);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > brickSS(new SimpleSpriteSheet(BRICK_GRAHPICS));

  rmss.insert(BRICK_SS, brickSS);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > brickCollisionerList(new TicketedForwardList<AvatarEntity<Collisioner<ZombienoidReactor> > >());
  ballCBSJoint->add(brickCollisionerList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > brickAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  ResourceManager<TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > >& rmsam2 = ResourceManager<TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > >::getInstance();
  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > > brickList(new TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > >());
  rmsam2.insert(BRICK_LIST, brickList);

  std::shared_ptr<Daemon> brickEraserLT(new PunisherDaemon<Behavior<Stated, Avatar, Positionable<2> >, TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > >(std::make_shared<BrickEraser>(0, BRICK_ITEM_SUCCES, BRICK_ITEM_TOTAL, itemBuilder), BRICK_LIST));
  reactBehaviorMaster->addDaemon(brickEraserLT);
  std::shared_ptr<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > aecsap2;
  for(int i = 0; i < NBRICKS_X; i++) {
    for(int j = 0; j < NBRICKS_Y; j++) {
        int state = (rand() % (BRICK_MAX_LEVEL + 1)-SPECIAL_STATES);
        if(state == -1){
            continue;
        }
        if(state == -2){
            state = BRICK_BOOMBIZER_STATE;
        }

        std::shared_ptr<Element2D<ZombienoidReactor> > brick(new Element2D<ZombienoidReactor>({(double)(BRICK_WIDTH*i)+MARGIN + (BRICK_WIDTH/2) + BRICKS_X_MARGIN, (double)BRICKS_Y_MARGIN+(double)(BRICK_HEIGHT*j)+MARGIN + (BRICK_HEIGHT/2)}, BRICK_ACTUATORS_LIST, (double)BRICK_WIDTH, (double)BRICK_HEIGHT, BRICK_SS));
        std::shared_ptr<Adaptor<AnimatedSprite> > brickSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(brick));
        setAdaptor(brick, brickSpriteAdaptor);
        brick->setState( state );

        std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > brickCollisionerAdaptor(new BlockConerAdaptor<ZombienoidReactor>(brick, BRICK_BOOMBIZER_STATE));
        setAdaptor(brick, brickCollisionerAdaptor);

        wrapAEC(&aecas, brick);
        wrapAEC(&aecsap2, brick);

        brick->addToList(COLLISION_TICKET, brickCollisionerList->push_front(brick));
        brick->addToList(DRAW_TICKET, brickAnimatedSpriteList->push_front(aecas));
        brick->addToList(BEHAVE_TICKET, brickList->push_front(aecsap2));
    }
  }

  //ball spawner---------------------------------------------------------------------------------------------
  ResourceManager<TicketedFAEC<Movable<2> > > & rmaecM2d = ResourceManager<TicketedFAEC<Movable<2> > >::getInstance();
  std::shared_ptr<TicketedFAEC<Movable<2> > > spawnList(new TicketedFAEC<Movable<2> >());
  rmaecM2d.insert(BALLSPAWN_LIST, spawnList);

  for(int i = 0; i < NBALLS; i++) {
    int64_t vt = 400;
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
    std::shared_ptr<AvatarEntityFixed<Movable<2> > > spawner = std::make_shared<AvatarEntityFixed<Movable<2> > >(spawnAvatar);
    wrapAEC(&aecm2, spawner);
    spawnList->push_front(aecm2);
  }
  //bar------------------------------------------------------------------------------------------------------
  std::shared_ptr<Value<double> > mouseXPos(new SimpleValue<double>());

  ResourceManager<JointAEC<Positionable<2>, Avatar> >& rmjp2a = ResourceManager<JointAEC<Positionable<2>, Avatar > >::getInstance();
  std::shared_ptr<JointAEC<Positionable<2>, Avatar> > p2aJoint(new JointAEC<Positionable<2>, Avatar>());
  rmjp2a.insert(MOUSE_CONTROL_LIST, p2aJoint);
  std::shared_ptr<TicketedFAEC<Positionable<2>, Avatar> > mouseControlList(new TicketedFAEC<Positionable<2> , Avatar>());
  p2aJoint->add(mouseControlList);

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* > > barActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* >());
  rmact.insert(BAR_ACTUATORS_LIST, barActuatorsList);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > barCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());
  ballCBSJoint->add(barCollisionerList);
  itemCBSJoint->add(barCollisionerList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > barAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  uint64_t BAR_GRAPHICS = imgStore.loadImg(barImg);
  uint64_t BAR_GRAPHICS_GREY = imgStore.loadImg(barImgGrey);

  ImgSrcDef barGrapDef;
  barGrapDef.frameAmount = 1;
  barGrapDef.frameDisplacemet = Vector2D({0.0,0.0});
  barGrapDef.frameTime = 1000;
  barGrapDef.intialRegion = Region2D({0.0,0.0},{161.0,32.0});
  barGrapDef.imgSrcId = BAR_GRAPHICS;

  MultiSpriteSheet* barSheet = new MultiSpriteSheet(2, barGrapDef);
  barGrapDef.imgSrcId = BAR_GRAPHICS_GREY;
  barSheet->setImgSrcDef(1,barGrapDef);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > barSS(barSheet);
  rmss.insert(BAR_SS, barSS);

  std::shared_ptr<Element2D<ZombienoidReactor> > bar(new Element2D<ZombienoidReactor>({(WIDTH-BAR_I_WIDTH)/2, HEIGHT-BAR_MARGIN-(BAR_HEIGHT/2)},   BAR_ACTUATORS_LIST, BAR_I_WIDTH, BAR_HEIGHT, BAR_SS));

  std::shared_ptr<Adaptor<AnimatedSprite> > barSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(bar));
  setAdaptor(bar, barSpriteAdaptor);

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > barCollisionerAdaptor(new BarConerAdaptor<ZombienoidReactor>(bar));
  setAdaptor(bar, barCollisionerAdaptor);

  wrapAEC(&aecas, bar);
  wrapAEC(&aecp2a, bar);

  bar->addToList(COLLISION_TICKET, barCollisionerList->push_front(bar));
  bar->addToList(DRAW_TICKET, barAnimatedSpriteList->push_front(aecas));
  bar->addToList(BEHAVE_TICKET, mouseControlList->push_front(aecp2a));

  std::shared_ptr<Daemon> mouseControllDaemon(new  BehaviorDaemon<Positionable<2>, JointAEC<Positionable<2>, Avatar > >(std::make_shared<XSetter>(mouseXPos), MOUSE_CONTROL_LIST ));

  //things that stick to the bar
  ResourceManager<TicketedFAEC<Positionable<2>, Avatar> >& rmp2a = ResourceManager<TicketedFAEC<Positionable<2>, Avatar > >::getInstance();
  std::shared_ptr<TicketedFAEC<Positionable<2>, Avatar> > demagnetizeList(new TicketedFAEC<Positionable<2> , Avatar>());
  p2aJoint->add(demagnetizeList);
  rmp2a.insert(DEMAGNETIZE_LIST, demagnetizeList);
  std::shared_ptr<Daemon> demagnetizeDaemon(new  BehaviorDaemon<Avatar, TicketedFAEC<Positionable<2>, Avatar> >(std::make_shared<Demagnetizer>(BEHAVE_TICKET, MAGNET_TICKET), DEMAGNETIZE_LIST));

  DaemonInputHandler demagnetizeDaemonInputHandler(demagnetizeDaemon);
  ieg->addHandler(ZBEK_MOUSE_LEFT, &demagnetizeDaemonInputHandler);

  //Points counter-------------------------------------------------------------------------------------------
  std::shared_ptr<Value<int64_t> > pointsValue(new SimpleValue<int64_t>(0));

  //ball counter---------------------------------------------------------------------------------------------
  std::shared_ptr<Value<int64_t> > ballCount(new SimpleValue<int64_t>());

  //ball-----------------------------------------------------------------------------------------------------
  double BALL_SIZE_MIN = 0.25;
  double BALL_SIZE_MAX = 2;
  double BALL_SIZE_STEP = 0.25;
  double BALL_XPLODE_RATIO = 64.0;

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* > > ballActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* >());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballCustomBouncerVoidWrapper;
  ballCustomBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Bouncer<2> >, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new CustomVectorBouncerActuator<ZombienoidReactor>());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballMagnetWrapper;
  ballMagnetWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Positionable<2>, Avatar>, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new MagnetSticker<ZombienoidReactor, TicketedFAEC<Positionable<2>, Avatar> >(demagnetizeList, BEHAVE_TICKET, MAGNET_TICKET, MARGIN + 64, MARGIN + 64, WIDTH - (2*MARGIN), HEIGHT));

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBouncerVoidWrapper;
  ballBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Bouncer<2> >, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BouncerActuator<ZombienoidReactor, Solid>());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBouncerITWrapper;
  ballBouncerITWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Bouncer<2> >, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BouncerActuator<ZombienoidReactor, InteractionTester>());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballEraserWrapper;
  ballEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Avatar>, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new ConditionalEraserActuator<ZombienoidReactor>());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballScorerWrapper;
  ballScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Scorer>, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(new BallScorer<ZombienoidReactor>(pointsValue, P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));

  // TODO
  // multiss de ladrillos
  // multiss de bola

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > boomAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());
  ResourceManager<TicketedFAEC<AnimatedSprite> >& rmTFAECAS = ResourceManager<TicketedFAEC<AnimatedSprite> >::getInstance();
  rmTFAECAS.insert(BOOM_AS_LIST, boomAnimatedSpriteList);
  ResourceManager<TicketedFAE<Collisioner<ZombienoidReactor> > > & rmTFAECN = ResourceManager<TicketedFAE<Collisioner<ZombienoidReactor> > >::getInstance();
  rmTFAECN.insert(BRICK_COLLISIONER_LIST, brickCollisionerList);
  ResourceManager<TicketedFAE<Collisionator<ZombienoidReactor> > > & rmTFAECT = ResourceManager<TicketedFAE<Collisionator<ZombienoidReactor> > >::getInstance();
  rmTFAECT.insert(BOOM_COLLISIONATOR_LIST, std::make_shared<TicketedFAE<Collisionator<ZombienoidReactor> > >());

  auto explosionAvatarList = std::make_shared<TicketedFAEC<Avatar, Scorer> >();
  ResourceManager<TicketedFAEC<Avatar, Scorer> >& rmTFAECA = ResourceManager<TicketedFAEC<Avatar, Scorer> >::getInstance();
  rmTFAECA.insert(EXPLSION_ERASE_LIST, explosionAvatarList);
  std::shared_ptr<Daemon> explosionEraser(new BehaviorDaemon<Avatar, TicketedFAEC<Avatar, Scorer> >(std::make_shared<Erase>(), EXPLSION_ERASE_LIST));

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Scorer> >*> >& rsmng = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, zbe::WeakAvatarEntityContainer<Scorer> >*> >::getInstance();
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Scorer> >*> > explosionActuatorsList(new std::forward_list<zbe::ActuatorWrapper<ZombienoidReactor, zbe::WeakAvatarEntityContainer<Scorer> >*>());
  rsmng.insert(EXPLOSION_ACTUATORS_LIST, explosionActuatorsList);
  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Scorer> >* explosionScorerWrapper;
  explosionScorerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Scorer>, WeakAvatarEntityContainer<Scorer> >(new BallScorer<ZombienoidReactor>(pointsValue, P_ACCUM_TIME, P_EXTRA_ACCUM_TIME, POINTS_MULTIPLIER));
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
  (teg, COLLISIONEVENT, BOOM_TEXTSPRITE_TICKET, EXPLOSION_ACTUATORS_LIST, COLLISION_TICKET, BEHAVE_TICKET, EXPLSION_ERASE_LIST, BOOM_COLLISIONATOR_LIST, BRICK_COLLISIONER_LIST, BOOM_AS_LIST, TEXT_TS_LIST, EXPLSION_SS, BOOM_TIME, BOOM_TEXT_FONT, TEXT_B_SIZE, TEXT_B_SIZE, BALL_BOOM_STATE, BALL_XPLODE_RATIO, BALL_SIZE_STEP);
  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >* ballBoombizerWrapper;
  ballBoombizerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated, Resizable>, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated, Scorer, Resizable> >(ballBombizer);

  ballActuatorsList->push_front(ballCustomBouncerVoidWrapper);
  ballActuatorsList->push_front(ballMagnetWrapper);
  ballActuatorsList->push_front(ballBouncerVoidWrapper);
  ballActuatorsList->push_front(ballBouncerITWrapper);
  ballActuatorsList->push_front(ballEraserWrapper);
  ballActuatorsList->push_front(ballScorerWrapper);
  ballActuatorsList->push_front(ballBoombizerWrapper);

  rmawlabss.insert(BALL_ACTUATORS_LIST, ballActuatorsList);

  uint64_t BALL_N_GRAPHICS = imgStore.loadImg(ballImgNormal);
  uint64_t BALL_B_GRAPHICS = imgStore.loadImg(ballImgBoomb);
  uint64_t EXPLODE_GRAPHICS = imgStore.loadImg(explosion);

  ImgSrcDef ballGrapDef;
  ballGrapDef.frameAmount = 1;
  ballGrapDef.frameDisplacemet = Vector2D({0.0,0.0});
  ballGrapDef.frameTime = 1000;
  ballGrapDef.intialRegion = Region2D({0.0,0.0},{64.0,64.0});
  ballGrapDef.imgSrcId = BALL_N_GRAPHICS;

  MultiSpriteSheet* ballSheet = new MultiSpriteSheet(2, ballGrapDef);
  ballGrapDef.imgSrcId = BALL_B_GRAPHICS;
  ballSheet->setImgSrcDef(BALL_BOOM_STATE,ballGrapDef);

  ImgSrcDef explosionGrapDef;
  explosionGrapDef.frameAmount = 1;
  explosionGrapDef.frameDisplacemet = Vector2D({0.0,0.0});
  explosionGrapDef.frameTime = 1000;
  explosionGrapDef.intialRegion = Region2D({0.0,0.0},{512.0,512.0});
  explosionGrapDef.imgSrcId = EXPLODE_GRAPHICS;

  MultiSpriteSheet* explosionSheet = new MultiSpriteSheet(1, explosionGrapDef);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > ballSS(ballSheet);
  rmss.insert(BALL_SS, ballSS);
  std::shared_ptr<SpriteSheet<AnimatedSprite> > explosionSS(explosionSheet);
  rmss.insert(EXPLSION_SS, explosionSS);

  std::shared_ptr<TicketedFAE<Collisionator<ZombienoidReactor> > > ballCollisionatorsList(new TicketedFAE<Collisionator<ZombienoidReactor> >());
  ctsJoint->add(ballCollisionatorsList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > ballAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  ResourceManager<TicketedFAEC<Bouncer<2>, Resizable> > & rmb2w = ResourceManager<TicketedFAEC<Bouncer<2>, Resizable> >::getInstance();
  std::shared_ptr<TicketedFAEC<Bouncer<2>, Resizable> > ballList(new TicketedFAEC<Bouncer<2>, Resizable>());
  rmb2w.insert(BALL_LIST, ballList);

  std::shared_ptr<Daemon> ballBounce(new BehaviorDaemon<Bouncer<2>, TicketedFAEC<Bouncer<2>, Resizable> >(std::make_shared<Bounce<2> >(), BALL_LIST));
  std::shared_ptr<Daemon> ballULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Bouncer<2>, Resizable> >(std::make_shared<UniformLinearMotion<2> >(), BALL_LIST));

  commonBehaviorMaster->addDaemon(ballBounce);
  commonBehaviorMaster->addDaemon(ballULM);

  std::shared_ptr<CustomBallBuilder> ballBuilder= std::make_shared<CustomBallBuilder>(BALL_ACTUATORS_LIST, BALL_CBS_JOINT, BALL_SS, BALL_SIZE, BALL_SIZE_MIN, BALL_SIZE_MAX, ballCount, MAXBALLS, COLLISION_TICKET,
                          DRAW_TICKET, BEHAVE_TICKET, ballCollisionatorsList,ballAnimatedSpriteList, ballList);

  std::shared_ptr<Daemon> ballCreatorDaemon(new  BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2>> >(ballBuilder, BALLSPAWN_LIST ));

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
  rmTAECSTS.insert(TEXT_TS_LIST, textSpriteList);

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
  std::shared_ptr<Daemon> multiplierItem = std::make_shared<BallMultiplierItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ballBuilder, BALL_LIST, angles, 2);
  std::shared_ptr<Daemon> accelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(BALL_LIST, 1.5);
  std::shared_ptr<Daemon> decelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(BALL_LIST, 0.666666);
  std::shared_ptr<Daemon> ballMagnifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(BALL_LIST, BALL_SIZE_STEP);
  std::shared_ptr<Daemon> ballMinifierItem = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(BALL_LIST, -BALL_SIZE_STEP);
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

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* itemCatchWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Stated>, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >(catcher);

  barActuatorsList->push_front(itemCatchWrapper);

  wrapAEC(&aecsts, lifeCountEnt);

  textSpriteList->push_front(aecsts);

  wrapAEC(&aecsts, pointsEnt);

  textSpriteList->push_front(aecsts);

  std::shared_ptr<Daemon> lifeDaemon = std::make_shared<ZombienoidLifeSubstractor>(ballCount, lifeCountValue, ballCreatorDaemon);
  reactBehaviorMaster->addDaemon(lifeDaemon);
  reactBehaviorMaster->addDaemon(mouseControllDaemon);
  reactBehaviorMaster->addDaemon(explosionEraser);

  MouseXIH mouseX(mouseXPos);
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
  reactBehaviorMaster->addDaemon(failDaemon);

  mainLoop.loop();

  return 0;
}
} //namespace zombieBall
