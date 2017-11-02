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

#include "zombienoid/events/handlers/ExitInputHandler.h"

#include "zombienoid/entities/adaptors/ActiveElement2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/BallCatorAdaptor.h"
#include "zombienoid/entities/adaptors/BlockConerAdaptor.h"
#include "zombienoid/entities/adaptors/BarConerAdaptor.h"
#include "zombienoid/entities/adaptors/BoardConerAdaptor.h"
#include "zombienoid/entities/adaptors/Element2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/Element2DDisplacedAnimatedSpriteAdaptor.h"

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

#include "zombienoid/graphics/SimpleSpriteSheet.h"
#include "zombienoid/graphics/MultiSpriteSheet.h"


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
    ITEM_TYPES = 7,
    ITEM_FALL_SPEED = 100,
    ITEM_WIDTH = 32,
    ITEM_HEIGHT = 64,
    NBRICKS_X = 16,
    NBRICKS_Y = 10,
    BRICK_WIDTH = 51,
    BRICK_HEIGHT = 32,
    BRICK_COLS = 12,
    BRICK_ROWS = 8,
    BRICKS_X_MARGIN = 72,//123,
    BRICKS_Y_MARGIN = 96,//128,
    BRICK_MAX_LEVEL = 2,
    BRICK_ITEM_SUCCES = 1,
    BRICK_ITEM_TOTAL = 3,
    BALL_SIZE = 32,
    BALL_V_X = -300,
    BALL_V_Y = -300,
    BAR_I_WIDTH = 322,
    BAR_HEIGHT = 32,
    BAR_MARGIN = 32,
    LIFE_COUNTER_F_SIZE = 28
  };
  // Ticket ids.
  const int COLLISION_TICKET = SysIdGenerator::getId();
  const int DRAW_TICKET = SysIdGenerator::getId();
  const int BEHAVE_TICKET = SysIdGenerator::getId();
  const int MAGNET_TICKET = SysIdGenerator::getId();

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
  const int BAR_ACTUATORS_LIST = SysIdGenerator::getId();
  // Behaviors list
  const int BRICK_LIST = SysIdGenerator::getId();
  const int BALLSPAWN_LIST = SysIdGenerator::getId();
  const int BALL_LIST = SysIdGenerator::getId();
  const int ITEM_LIST = SysIdGenerator::getId();
  const int MOUSE_CONTROL_LIST = SysIdGenerator::getId();
  const int DEMAGNETIZE_LIST = SysIdGenerator::getId();
  // Collisionables list joints
  const int BALL_CBS_JOINT = SysIdGenerator::getId();
  const int ITEM_CBS_JOINT = SysIdGenerator::getId();
  // Sprite sheet ids
  const int ITEM_SS = SysIdGenerator::getId();
  const int BRICK_SS = SysIdGenerator::getId();
  const int BALL_SS = SysIdGenerator::getId();
  const int BAR_SS = SysIdGenerator::getId();
  const int BOARD_SS = SysIdGenerator::getId();


  //const char boardImg[] = "escriba su anuncio aqui, por favor";
  const char brickImg[] = "data/images/zombieball/braikn_32.png";
  const char ballImg[]  = "data/images/zombieball/zball_n.png";
  const char barImg[]   = "data/images/zombieball/zombar_color_32.png";
  const char barImgGrey[]   = "data/images/zombieball/zombar_grey_32.png";
  //const char beerImg[]   = "data/images/zombieball/beer_l_32.png";

  //Items
  const char extraLife[]   = "data/images/zombieball/zbeza_life_32.png";
  const char multiplier[]   = "data/images/zombieball/zbeza_tbal_32.png";
  const char accelerator[]   = "data/images/zombieball/zbeza_acel_32.png";
  const char decelerator[]   = "data/images/zombieball/zbeza_dcel_32.png";
  const char bigger[]   = "data/images/zombieball/zbeza_ebal_32.png";
  const char smaller[]   = "data/images/zombieball/zbeza_rbal_32.png";
  const char magnet[]   = "data/images/zombieball/zbeza_sbar_32.png";

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

  ResourceManager<JointAEC<SingleTextSprite> >& rmats = ResourceManager<JointAEC<SingleTextSprite> >::getInstance();
  std::shared_ptr<JointAEC<SingleTextSprite> > atsJoint (new JointAEC<SingleTextSprite>());
  rmats.insert(ATS_JOINT, atsJoint);

  ResourceManager<SpriteSheet<AnimatedSprite> >& rmss = ResourceManager<SpriteSheet<AnimatedSprite> >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* > >& rmact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* > >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* > >& rmaact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* > >::getInstance();

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

  rmaact.insert(ITEM_ACTUATORS_LIST, itemActuatorsList);

  std::shared_ptr<Daemon> itemULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2> > >(std::make_shared<UniformLinearMotion<2> >(), ITEM_LIST));
  commonBehaviorMaster->addDaemon(itemULM);

  uint64_t ITEM_LIFE_GRAPHICS = imgStore.loadImg(extraLife);
  uint64_t ITEM_MULTIPLIER_GRAPHICS = imgStore.loadImg(multiplier);
  uint64_t ITEM_ACCEL_GRAPHICS = imgStore.loadImg(accelerator);
  uint64_t ITEM_DECEL_GRAPHICS = imgStore.loadImg(decelerator);
  uint64_t ITEM_BIGGER_GRAPHICS = imgStore.loadImg(bigger);
  uint64_t ITEM_SMALLER_GRAPHICS = imgStore.loadImg(smaller);
  uint64_t ITEM_MAGNET_GRAPHICS = imgStore.loadImg(magnet);

  ImgSrcDef itemGraphics;
  itemGraphics.frameAmount = 1;
  itemGraphics.frameDisplacemet = Vector2D({0.0,0.0});
  itemGraphics.frameTime = 1000;
  itemGraphics.intialRegion = Region2D({0.0,0.0},{32.0,64.0});
  itemGraphics.imgSrcId = ITEM_LIFE_GRAPHICS;

  MultiSpriteSheet* itemSheet = new MultiSpriteSheet(7, itemGraphics);
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


  std::shared_ptr<SpriteSheet<AnimatedSprite> > itemSS(itemSheet);
  rmss.insert(ITEM_SS, itemSS);

  std::shared_ptr<TicketedFAE<Collisionator<ZombienoidReactor> > > itemCollisionatorsList(new TicketedFAE<Collisionator<ZombienoidReactor> >());
  ctsJoint->add(itemCollisionatorsList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > itemAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());

  std::shared_ptr<CustomItemBuilder> itemBuilder= std::make_shared<CustomItemBuilder>(ITEM_ACTUATORS_LIST, ITEM_CBS_JOINT, ITEM_SS, ITEM_WIDTH, ITEM_HEIGHT, ITEM_TYPES, (double) ITEM_FALL_SPEED , COLLISION_TICKET,
                          DRAW_TICKET, BEHAVE_TICKET, itemCollisionatorsList,itemAnimatedSpriteList, itemList);

  //bricks---------------------------------------------------------------------------------------------------

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* > > brickActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* >());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* brickEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Stated>, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >(new StateChangerActuator<ZombienoidReactor, Solid>(-1));
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
        std::shared_ptr<Element2D<ZombienoidReactor> > brick(new Element2D<ZombienoidReactor>({(double)(BRICK_WIDTH*i)+MARGIN + (BRICK_WIDTH/2) + BRICKS_X_MARGIN, (double)BRICKS_Y_MARGIN+(double)(BRICK_HEIGHT*j)+MARGIN + (BRICK_HEIGHT/2)}, BRICK_ACTUATORS_LIST, (double)BRICK_WIDTH, (double)BRICK_HEIGHT, BRICK_SS));
        std::shared_ptr<Adaptor<AnimatedSprite> > brickSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(brick));
        setAdaptor(brick, brickSpriteAdaptor);
        brick->setState(rand() % BRICK_MAX_LEVEL);

        std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > brickCollisionerAdaptor(new BlockConerAdaptor<ZombienoidReactor>(brick));
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


  //ball counter---------------------------------------------------------------------------------------------
  std::shared_ptr<Value<int64_t> > ballCount(new SimpleValue<int64_t>());

  //ball-----------------------------------------------------------------------------------------------------
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* > > ballActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* >());

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* ballCustomBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Bouncer<2> >, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >(new CustomVectorBouncerActuator<ZombienoidReactor>());
  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* ballMagnetWrapper;
  ballMagnetWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Positionable<2>, Avatar>, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >(new MagnetSticker<ZombienoidReactor, TicketedFAEC<Positionable<2>, Avatar> >(demagnetizeList, BEHAVE_TICKET, MAGNET_TICKET, MARGIN + 64, MARGIN + 64, WIDTH - (2*MARGIN), HEIGHT));
  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* ballBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Bouncer<2> >, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >(new BouncerActuator<ZombienoidReactor, Solid>());
  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* ballBouncerITWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Bouncer<2> >, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >(new BouncerActuator<ZombienoidReactor, InteractionTester>());
  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >* ballEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Avatar>, WeakAvatarEntityContainer<Avatar, Bouncer<2>, Stated> >(new ConditionalEraserActuator<ZombienoidReactor>());
  ballActuatorsList->push_front(ballCustomBouncerVoidWrapper);
  ballActuatorsList->push_front(ballMagnetWrapper);
  ballActuatorsList->push_front(ballBouncerVoidWrapper);
  ballActuatorsList->push_front(ballBouncerITWrapper);
  ballActuatorsList->push_front(ballEraserWrapper);

  rmaact.insert(BALL_ACTUATORS_LIST, ballActuatorsList);

  uint64_t BALL_GRAPHICS = imgStore.loadImg(ballImg);

  ImgSrcDef ballGrapDef;
  ballGrapDef.frameAmount = 1;
  ballGrapDef.frameDisplacemet = Vector2D({0.0,0.0});
  ballGrapDef.frameTime = 1000;
  ballGrapDef.intialRegion = Region2D({0.0,0.0},{64.0,64.0});
  ballGrapDef.imgSrcId = BALL_GRAPHICS;

  MultiSpriteSheet* ballSheet = new MultiSpriteSheet(1, ballGrapDef);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > ballSS(ballSheet);
  rmss.insert(BALL_SS, ballSS);

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

  std::shared_ptr<CustomBallBuilder> ballBuilder= std::make_shared<CustomBallBuilder>(BALL_ACTUATORS_LIST, BALL_CBS_JOINT, BALL_SS, BALL_SIZE, ballCount, MAXBALLS, COLLISION_TICKET,
                          DRAW_TICKET, BEHAVE_TICKET, ballCollisionatorsList,ballAnimatedSpriteList, ballList);

  std::shared_ptr<Daemon> ballCreatorDaemon(new  BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2>> >(ballBuilder, BALLSPAWN_LIST ));

  ballCreatorDaemon->run();

  //Game Draw layers front to back
  asJoint->add(itemAnimatedSpriteList);
  asJoint->add(ballAnimatedSpriteList);
  asJoint->add(brickAnimatedSpriteList);
  asJoint->add(barAnimatedSpriteList);
  asJoint->add(boardAnimatedSpriteList);

  // HUD
  //Life counter-----------------------------------------------------------------------------------------------------
  std::shared_ptr<TicketedFAEC<SingleTextSprite> > lifeCountersSingleTextSpriteList(new TicketedFAEC<SingleTextSprite>());
  atsJoint->add(lifeCountersSingleTextSpriteList);

  SDL_Color aColor;
  aColor.r = 255;
  aColor.g = 128;
  aColor.b = 0;
  aColor.a = 255;

  int TEXT_FONT = textFontStore.loadFont(fontFileName, LIFE_COUNTER_F_SIZE, aColor);
  std::shared_ptr<Value<int64_t> > lifeCount(new SimpleValue<int64_t>(INITIAL_LIFES));
  std::shared_ptr<LifeCounter> lc(new LifeCounter(4, 4, 32, 32, TEXT_FONT, lifeCount));

  ItemCatcher<ZombienoidReactor>* catcher = new ItemCatcher<ZombienoidReactor>();

  double* angles = new double[2]{-30.0, 30.0};

  double BALL_SIZE_MIN = 0.25;
  double BALL_SIZE_MAX = 2;
  double BALL_SIZE_STEP = 0.25;

  std::shared_ptr<Daemon> lifeItem = std::make_shared<LifeItem>(lifeCount,1);
  std::shared_ptr<Daemon> multiplierItem = std::make_shared<BallMultiplierItem<TicketedFAEC<Bouncer<2>, Resizable> > >(ballBuilder, BALL_LIST, angles, 2);
  std::shared_ptr<Daemon> accelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(BALL_LIST, 1.5);
  std::shared_ptr<Daemon> decelItem = std::make_shared<BallAcceleratorItem<TicketedFAEC<Bouncer<2>, Resizable> > >(BALL_LIST, 0.666666);
  std::shared_ptr<Daemon> ballMagnifier = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(BALL_LIST, BALL_SIZE_STEP, BALL_SIZE_MIN, BALL_SIZE_MAX);
  std::shared_ptr<Daemon> ballMinifier = std::make_shared<BallRadiusItem<TicketedFAEC<Bouncer<2>, Resizable> > >(BALL_LIST, -BALL_SIZE_STEP, BALL_SIZE_MIN, BALL_SIZE_MAX);
  std::shared_ptr<Daemon> magnetBar = std::make_shared<StickyBarItem>(bar, teg,SECOND*6,1);

  catcher->addItem(lifeItem);
  catcher->addItem(multiplierItem);
  catcher->addItem(accelItem);
  catcher->addItem(decelItem);
  catcher->addItem(ballMagnifier);
  catcher->addItem(ballMinifier);
  catcher->addItem(magnetBar);

  ActuatorWrapper<ZombienoidReactor, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >* itemCatchWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, WeakAvatarEntityContainer<Stated>, WeakAvatarEntityContainer<Avatar, Positionable<2>, Stated> >(catcher);

  barActuatorsList->push_front(itemCatchWrapper);

  wrapAEC(&aecsts, lc);

  lifeCountersSingleTextSpriteList->push_front(aecsts);

  std::shared_ptr<Daemon> lifeDaemon = std::make_shared<ZombienoidLifeSubstractor>(ballCount, lifeCount, ballCreatorDaemon);
  reactBehaviorMaster->addDaemon(lifeDaemon);
  reactBehaviorMaster->addDaemon(mouseControllDaemon);

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

  std::shared_ptr<Daemon> failDaemon = std::make_shared<ZombienoidDeathTester>(lifeCount, &mainLoop);
  reactBehaviorMaster->addDaemon(failDaemon);

  mainLoop.loop();

  return 0;
}
} //namespace zombieBall
