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

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/implementations/BaseMovable.h"

#include "ZBE/entities/Element2D.h"

#include "ZBE/events/handlers/actuators/EraserActuator.h"
#include "ZBE/events/handlers/actuators/BouncerActuator.h"
#include "ZBE/events/handlers/actuators/StateChangerActuator.h"

#include "ZBE/behaviors/Bounce.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/StateLTEraser.h"

#include "ZBE/events/handlers/actuators/ConditionalEraserActuator.h"
#include "ZBE/events/handlers/MouseXIH.h"

#include "ZBE/reactobjects/VoidReactObject.h"

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
#include "zombienoid/events/handlers/ExitInputHandler.h"

#include "zombienoid/entities/adaptors/ActiveElement2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/BallCatorAdaptor.h"
#include "zombienoid/entities/adaptors/BlockConerAdaptor.h"
#include "zombienoid/entities/adaptors/BoardConerAdaptor.h"
#include "zombienoid/entities/adaptors/Element2DAnimatedSpriteAdaptor.h"

#include "zombienoid/entities/LifeCounter.h"

#include "zombienoid/daemons/ZombienoidDeathTester.h"
#include "zombienoid/daemons/ZombienoidLifeSubstractor.h"

#include "zombienoid/behaviors/BrickEraser.h"

#include "zombienoid/behaviors/builders/BallBuilder.h"
#include "zombienoid/behaviors/builders/ItemBuilder.h"

#include "zombienoid/ZombienoidReactor.h"

#include "zombienoid/graphics/SimpleSpriteSheet.h"


namespace zombienoid {

using namespace zbe;

template <typename T>
using TicketedFAE = TicketedForwardList<AvatarEntity<T> >;

template <typename ...Avatars>
using TicketedFAEC = TicketedForwardList<AvatarEntityContainer<Avatars...> >;

template <typename T>
using JointAE = ListTicketedJoint<TicketedFAE<T>, std::shared_ptr<AvatarEntity<T> > >;

template <typename T>
using JointAEC = ListTicketedJoint<TicketedFAEC<T>, std::shared_ptr<AvatarEntityContainer<T> > >;

using InteractionGenerator = InteractionEventGenerator<
      ZombienoidReactor, CollisionSelector<ZombienoidReactor>,
      JointAE<Collisioner<ZombienoidReactor> >,
        JointAE<Collisionator<ZombienoidReactor> >
    >;

using CustomBallBuilder = BallBuilder<ZombienoidReactor, TicketedFAE<Collisionator<ZombienoidReactor> >,
              TicketedFAEC<AnimatedSprite>,
              TicketedFAEC<Bouncer<2> > >;

using CustomItemBuilder = ItemBuilder<ZombienoidReactor, TicketedFAE<Collisionator<ZombienoidReactor> >,
              TicketedFAEC<AnimatedSprite>,
              TicketedFAEC<Movable<2> > >;

int zombienoidmain(int, char*[]) {
  enum {
    WIDTH = 1024,
    HEIGHT = 768,
    MARGIN = 32,
    NBALLS = 5,
    ITEM_TYPES = 4,
    ITEM_FALL_SPEED = 100,
    BRICKS_X_MARGIN = 123,
    BRICKS_Y_MARGIN = 128,
    NBRICKS_X = 14,
    NBRICKS_Y = 8,
    BRICK_WIDTH = 51,
    BRICK_HEIGHT = 32,
    ITEM_WIDTH = 27,
    ITEM_HEIGHT = 32,
    BRICK_COLS = 12,
    BRICK_ROWS = 8,
    BALL_SIZE = 32,
    BALL_V_X = -300,
    BALL_V_Y = -300,
    BAR_I_WIDTH = 322,
    BAR_HEIGHT = 32,
    BAR_MARGIN = 32,
    LIFE_COUNTER_F_SIZE = 64
  };
  // Ticket ids.
  const int COLLISION_TICKET = SysIdGenerator::getId();
  const int DRAW_TICKET = SysIdGenerator::getId();
  const int BEHAVE_TICKET = SysIdGenerator::getId();
  // BOARD_GRAPHICS is never read.
  const int BOARD_GRAPHICS = SysIdGenerator::getId();
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
  // Collisionables list joints
  const int BALL_CBS_JOINT = SysIdGenerator::getId();
  const int ITEM_CBS_JOINT = SysIdGenerator::getId();
  // Sprite sheet ids
  const int ITEM_SS = SysIdGenerator::getId();
  const int BRICK_SS = SysIdGenerator::getId();
  const int BALL_SS = SysIdGenerator::getId();
  const int BAR_SS = SysIdGenerator::getId();


  //const char boardImg[] = "escriba su anuncio aqui, por favor";
  const char brickImg[] = "data/images/zombieball/braikn_32.png";
  const char ballImg[]  = "data/images/zombieball/zomball_st_32.png";
  const char barImg[]   = "data/images/zombieball/zombar_color_32.png";
  const char beerImg[]   = "data/images/zombieball/beer_l_32.png";
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

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > >& rmact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* > >& rmaact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* > >::getInstance();

  zombienoid::ExitInputHandler terminator;
  ieg->addHandler(zbe::ZBEK_ESCAPE, &terminator);

  //drawing----------------------------------------------------------------------------------------------------
  std::shared_ptr<Daemon> drawerDaemon(new  BehaviorDaemon<AnimatedSprite, JointAEC<AnimatedSprite> >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(&window, &imgStore), AS_JOINT));
  std::shared_ptr<Daemon> writerDaemon(new  BehaviorDaemon<SingleTextSprite, JointAEC<SingleTextSprite> >(std::make_shared<SingleTextSDLDrawer>(&window, &textFontStore), ATS_JOINT));
  drawMaster->addDaemon(drawerDaemon);
  drawMaster->addDaemon(writerDaemon);

  //wrappers--------------------------------------------------------------------------------------------------

  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Bouncer<2> > > aecb2;
  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2> > > aecm2;
  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Stated, zbe::Avatar> > aecsa;
  std::shared_ptr<zbe::AvatarEntityContainer<zbe::AnimatedSprite> > aecas;
  std::shared_ptr<zbe::AvatarEntityContainer<zbe::SingleTextSprite> > aecsts;
  //?

  //board----------------------------------------------------------------------------------------------------
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > > boardActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* >());

  rmact.insert(BOARD_ACTUATORS_LIST, boardActuatorsList);

  std::shared_ptr<Element2D<ZombienoidReactor> > board(new Element2D<ZombienoidReactor>({MARGIN, MARGIN}, BOARD_ACTUATORS_LIST, WIDTH - (MARGIN * 2), HEIGHT /*- (MARGIN * 2)*/, BOARD_GRAPHICS));

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > boardCollisionerAdaptor(new BoardConerAdaptor<ZombienoidReactor>(board));
  setAdaptor(board, boardCollisionerAdaptor);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > boardCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());

  board->addToList(COLLISION_TICKET, boardCollisionerList->push_front(board));

  ballCBSJoint->add(boardCollisionerList);
  itemCBSJoint->add(boardCollisionerList);

  //Items --------------------
  ResourceManager<TicketedFAEC<Movable<2> > > & rmm2 = ResourceManager<TicketedFAEC<Movable<2> > >::getInstance();
  std::shared_ptr<TicketedFAEC<Movable<2> > > itemList(new TicketedFAEC<Movable<2> >());
  rmm2.insert(ITEM_LIST, itemList);

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* > > itemActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* >());

  ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* itemAgainsBoardEraser = new  ActuatorWrapperCommon<ZombienoidReactor, Avatar, Avatar, Bouncer<2>, Stated>(new EraserActuator<ZombienoidReactor, InteractionTesterRO<ZombienoidReactor> >());
  ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* itemAgainsBarEraser   = new  ActuatorWrapperCommon<ZombienoidReactor, Avatar, Avatar, Bouncer<2>, Stated>(new EraserActuator<ZombienoidReactor, zbe::VoidReactObject<ZombienoidReactor> >());
  itemActuatorsList->push_front(itemAgainsBoardEraser);
  itemActuatorsList->push_front(itemAgainsBarEraser);

  rmaact.insert(ITEM_ACTUATORS_LIST, itemActuatorsList);

  std::shared_ptr<Daemon> itemULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2> > >(std::make_shared<UniformLinearMotion<2> >(), ITEM_LIST));
  commonBehaviorMaster->addDaemon(itemULM);

  uint64_t ITEM_GRAPHICS = imgStore.loadImg(beerImg);
  std::shared_ptr<SpriteSheet<AnimatedSprite> > itemSS(new SimpleSpriteSheet(ITEM_GRAPHICS));
  rmss.insert(ITEM_SS, itemSS);

  std::shared_ptr<TicketedFAE<Collisionator<ZombienoidReactor> > > itemCollisionatorsList(new TicketedFAE<Collisionator<ZombienoidReactor> >());
  ctsJoint->add(itemCollisionatorsList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > itemAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());
  asJoint->add(itemAnimatedSpriteList);

  std::shared_ptr<CustomItemBuilder> itemBuilder= std::make_shared<CustomItemBuilder>(ITEM_ACTUATORS_LIST, ITEM_CBS_JOINT, ITEM_SS, ITEM_HEIGHT, ITEM_TYPES, (double) ITEM_FALL_SPEED , COLLISION_TICKET,
                          DRAW_TICKET, BEHAVE_TICKET, itemCollisionatorsList,itemAnimatedSpriteList, itemList);

  //bricks---------------------------------------------------------------------------------------------------

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > > brickActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* >());

  ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* brickEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, Stated, Avatar, Positionable<2>, Stated >(new StateChangerActuator<ZombienoidReactor, zbe::VoidReactObject<ZombienoidReactor> >(-1));
  brickActuatorsList->push_front(brickEraserWrapper);

  rmact.insert(BRICK_ACTUATORS_LIST, brickActuatorsList);

  int BRICK_GRAHPICS = imgStore.loadImg(brickImg);
  std::shared_ptr<SpriteSheet<AnimatedSprite> > brickSS(new SimpleSpriteSheet(BRICK_GRAHPICS));
  rmss.insert(BRICK_SS, brickSS);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > brickCollisionerList(new TicketedForwardList<AvatarEntity<Collisioner<ZombienoidReactor> > >());
  ballCBSJoint->add(brickCollisionerList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > brickAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());
  asJoint->add(brickAnimatedSpriteList);

  ResourceManager<TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > >& rmsam2 = ResourceManager<TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > >::getInstance();
  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > > brickList(new TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > >());
  rmsam2.insert(BRICK_LIST, brickList);

  std::shared_ptr<Daemon> brickEraserLT(new PunisherDaemon<Behavior<Stated, Avatar, Positionable<2> >, TicketedForwardList<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > >(std::make_shared<BrickEraser>(0, 1, 10, itemBuilder), BRICK_LIST));
  reactBehaviorMaster->addDaemon(brickEraserLT);
  std::shared_ptr<AvatarEntityContainer<Stated, Avatar, Positionable<2> > > aecsap2;
  for(int i = 0; i < NBRICKS_X; i++) {
    for(int j = 0; j < NBRICKS_Y; j++) {
        std::shared_ptr<Element2D<ZombienoidReactor> > brick(new Element2D<ZombienoidReactor>({(double)(BRICK_WIDTH*i)+MARGIN + BRICKS_X_MARGIN, (double)BRICKS_Y_MARGIN+(double)(BRICK_HEIGHT*j)+MARGIN}, BRICK_ACTUATORS_LIST, (double)BRICK_WIDTH, (double)BRICK_HEIGHT, BRICK_SS));
        std::shared_ptr<Adaptor<AnimatedSprite> > brickSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(brick));
        setAdaptor(brick, brickSpriteAdaptor);
        brick->setState(rand() % 2);

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

  //ball counter---------------------------------------------------------------------------------------------
  std::shared_ptr<Value<int64_t> > ballCount(new SimpleValue<int64_t>());

  //ball-----------------------------------------------------------------------------------------------------
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated >* > > ballActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated >* >());

  ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* ballBouncerVoidWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, Bouncer<2>, Avatar, Bouncer<2>, Stated>(new BouncerActuator<ZombienoidReactor, zbe::VoidReactObject<ZombienoidReactor> >());
  ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* ballBouncerITWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, Bouncer<2>, Avatar, Bouncer<2>, Stated>(new BouncerActuator<ZombienoidReactor, InteractionTesterRO<ZombienoidReactor> >());
  ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* ballEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, Avatar, Avatar, Bouncer<2>, Stated>(new ConditionalEraserActuator<ZombienoidReactor>());
  ballActuatorsList->push_front(ballBouncerVoidWrapper);
  ballActuatorsList->push_front(ballBouncerITWrapper);
  ballActuatorsList->push_front(ballEraserWrapper);

  rmaact.insert(BALL_ACTUATORS_LIST, ballActuatorsList);

  uint64_t BALL_GRAPHICS = imgStore.loadImg(ballImg);
  std::shared_ptr<SpriteSheet<AnimatedSprite> > ballSS(new SimpleSpriteSheet(BALL_GRAPHICS));
  rmss.insert(BALL_SS, ballSS);

  std::shared_ptr<TicketedFAE<Collisionator<ZombienoidReactor> > > ballCollisionatorsList(new TicketedFAE<Collisionator<ZombienoidReactor> >());
  ctsJoint->add(ballCollisionatorsList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > ballAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());
  asJoint->add(ballAnimatedSpriteList);

  ResourceManager<TicketedFAEC<Bouncer<2> > > & rmb2 = ResourceManager<TicketedFAEC<Bouncer<2> > >::getInstance();
  std::shared_ptr<TicketedFAEC<Bouncer<2> > > ballList(new TicketedFAEC<Bouncer<2> >());
  rmb2.insert(BALL_LIST, ballList);

  std::shared_ptr<Daemon> ballBounce(new BehaviorDaemon<Bouncer<2>, TicketedFAEC<Bouncer<2> > >(std::make_shared<Bounce<2> >(), BALL_LIST));
  std::shared_ptr<Daemon> ballULM(new BehaviorDaemon<Movable<2>, TicketedFAEC<Bouncer<2> > >(std::make_shared<UniformLinearMotion<2> >(), BALL_LIST));

  commonBehaviorMaster->addDaemon(ballBounce);
  commonBehaviorMaster->addDaemon(ballULM);

  std::shared_ptr<CustomBallBuilder> ballBuilder= std::make_shared<CustomBallBuilder>(BALL_ACTUATORS_LIST, BALL_CBS_JOINT, BALL_SS, BALL_SIZE, ballCount, COLLISION_TICKET,
                          DRAW_TICKET, BEHAVE_TICKET, ballCollisionatorsList,ballAnimatedSpriteList, ballList);

  std::shared_ptr<Daemon> ballCreatorDaemon(new  BehaviorDaemon<Movable<2>, TicketedFAEC<Movable<2>> >(ballBuilder, BALLSPAWN_LIST ));

  ballCreatorDaemon->run();

  //bar------------------------------------------------------------------------------------------------------
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > > barActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* >());
  rmact.insert(BAR_ACTUATORS_LIST, barActuatorsList);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > barCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());
  ballCBSJoint->add(barCollisionerList);
  itemCBSJoint->add(barCollisionerList);

  std::shared_ptr<TicketedFAEC<AnimatedSprite> > barAnimatedSpriteList(new TicketedFAEC<AnimatedSprite>());
  asJoint->add(barAnimatedSpriteList);

  //std::shared_ptr<TicketedForwardList<Element2D<ZombienoidReactor> > > barList(new TicketedForwardList<Element2D<ZombienoidReactor> >());

  uint64_t BAR_GRAPHICS = imgStore.loadImg(barImg);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > barSS(new SimpleSpriteSheet(BAR_GRAPHICS));
  rmss.insert(BAR_SS, barSS);

  std::shared_ptr<Element2D<ZombienoidReactor> > bar(new Element2D<ZombienoidReactor>({(WIDTH-BAR_I_WIDTH)/2, HEIGHT-BAR_MARGIN-BAR_HEIGHT},   BAR_ACTUATORS_LIST, BAR_I_WIDTH, BAR_HEIGHT, BAR_SS));

  std::shared_ptr<Adaptor<AnimatedSprite> > barSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(bar));
  setAdaptor(bar, barSpriteAdaptor);

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > barCollisionerAdaptor(new BlockConerAdaptor<ZombienoidReactor>(bar));
  setAdaptor(bar, barCollisionerAdaptor);

  zbe::wrapAEC(&aecas, bar);

  bar->addToList(COLLISION_TICKET, barCollisionerList->push_front(bar));
  bar->addToList(DRAW_TICKET, barAnimatedSpriteList->push_front(aecas));
  //bar->addToList(BEHAVE_TICKET, barList->push_front(bar));

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
  std::shared_ptr<LifeCounter> lc(new LifeCounter(0, 0, 64, 64, TEXT_FONT, lifeCount));

  ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* itemCatchWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, Stated, Avatar, Positionable<2>, Stated >(new ItemCatcher<ZombienoidReactor>(lifeCount));
  barActuatorsList->push_front(itemCatchWrapper);

  zbe::wrapAEC(&aecsts, lc);

  lifeCountersSingleTextSpriteList->push_front(aecsts);

  std::shared_ptr<Daemon> lifeDaemon = std::make_shared<ZombienoidLifeSubstractor>(ballCount, lifeCount, ballCreatorDaemon);
  reactBehaviorMaster->addDaemon(lifeDaemon);

  MouseXIH mouseX(bar);
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
