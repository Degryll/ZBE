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

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/MainLoop.h"

#include "ZBE/core/io/InputBuffer.h"

#include "ZBE/entities/Element2D.h"
#include "ZBE/entities/ActiveElement2D.h"

#include "ZBE/events/handlers/actuators/BouncerActuator.h"
#include "ZBE/events/handlers/actuators/EraserActuator.h"

#include "ZBE/behaviors/bounce.h"
#include "ZBE/behaviors/UniformLinearMotion.h"

#include "ZBE/events/handlers/actuators/ConditionalEraserActuator.h"
#include "ZBE/events/handlers/MouseXIH.h"

#include "ZBE/reactobjects/VoidReactObject.h"

#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"

#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"

#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include "ZBE/SDL/system/SDLImageStore.h"

#include "ZBE/SDL/tools/SDLTimer.h"

#include "zombienoid/events/handlers/ExitInputHandler.h"

#include "zombienoid/entities/adaptors/ActiveElement2DAnimatedSpriteAdaptor.h"
#include "zombienoid/entities/adaptors/BallCatorAdaptor.h"
#include "zombienoid/entities/adaptors/BlockConerAdaptor.h"
#include "zombienoid/entities/adaptors/BoardConerAdaptor.h"
#include "zombienoid/entities/adaptors/Element2DAnimatedSpriteAdaptor.h"

#include "zombienoid/ZombienoidReactor.h"

#include "zombienoid/graphics/SimpleSpriteSheet.h"


namespace zombienoid {

using namespace zbe;

template <typename T>
using TicketedFAE = TicketedForwardList<AvatarEntity<T> >;

template <typename T>
using JointAE = ListTicketedJoint<TicketedFAE<T>, std::shared_ptr<AvatarEntity<T> > >;
using InteractionGenerator = InteractionEventGenerator<
      ZombienoidReactor, CollisionSelector<ZombienoidReactor>,
      JointAE<Collisioner<ZombienoidReactor> >,
        JointAE<Collisionator<ZombienoidReactor> >
    >;

int zombienoidmain(int, char*[]) {
  enum {
    WIDTH = 1024,
    HEIGHT = 768,
    MARGIN = 32,
    NBRICKS = 10,
    BRICK_WIDTH = 52,
    BRICK_HEIGHT = 32,
    BRICK_COLS = 12,
    BRICK_ROWS = 8,
    BALL_SIZE = 32,
    BALL_V_X = 100,
    BALL_V_Y = 100,
    BAR_I_WIDTH = 128,
    BAR_HEIGHT = 32,
    BAR_MARGIN = 32
  };
  const int COLLISION_TICKET = SysIdGenerator::getId();
  const int DRAW_TICKET = SysIdGenerator::getId();
  const int BEHAVE_TICKET = SysIdGenerator::getId();

  const int BOARD_GRAPHICS = SysIdGenerator::getId();
  const int BRICK_GRAPHICS = SysIdGenerator::getId();
  const int BALL_GRAPHICS = SysIdGenerator::getId();
  const int BAR_GRAPHICS = SysIdGenerator::getId();

  const int INPUTEVENT = SysIdGenerator::getId();
  const int TIMEEVENT = SysIdGenerator::getId();

  const int COLLISIONEVENT = SysIdGenerator::getId();
  const int CTS_JOINT = SysIdGenerator::getId();
  const int AS_JOINT = SysIdGenerator::getId();

  const int BOARD_ACTUATORS_LIST = SysIdGenerator::getId();
  const int BRICK_ACTUATORS_LIST = SysIdGenerator::getId();
  const int BALL_ACTUATORS_LIST = SysIdGenerator::getId();
  const int BAR_ACTUATORS_LIST = SysIdGenerator::getId();

  const int BOARD_AS_COLLISIONER_LIST = SysIdGenerator::getId();
  //const int BOARD_AS_ANIMATED_SPRITE_LIST = SysIdGenerator::getId();

  const int BRICK_AS_COLLISIONER_LIST = SysIdGenerator::getId();
  const int BRICK_AS_ANIMATED_SPRITE_LIST = SysIdGenerator::getId();
  const int BRICK_LIST = SysIdGenerator::getId();

  const int BALL_CNR_JOINT = SysIdGenerator::getId();
  const int BALL_AS_ANIMATED_SPRITE_LIST = SysIdGenerator::getId();
  const int BALL_LIST = SysIdGenerator::getId();

  const int BAR_AS_COLLISIONER_LIST = SysIdGenerator::getId();
  const int BAR_AS_ANIMATED_SPRITE_LIST = SysIdGenerator::getId();
  const int BAR_LIST = SysIdGenerator::getId();

  const int BRICK_SS = SysIdGenerator::getId();
  const int BALL_SS = SysIdGenerator::getId();
  const int BAR_SS = SysIdGenerator::getId();


  //const char boardImg[] = "escriba su anuncio aqui";
  const char brickImg[] = "data/images/zombieball/braikn_32.png";
  const char ballImg[]  = "data/images/zombieball/zomball_st_32.png";
  const char barImg[]   = "data/images/zombieball/zombar_color_32.png";

  SDLWindow window(WIDTH, HEIGHT);
  SDLImageStore imgStore(window.getRenderer());

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

  ResourceManager<JointAE<AnimatedSprite> >& rmas = ResourceManager<JointAE<AnimatedSprite> >::getInstance();
  std::shared_ptr<JointAE<AnimatedSprite> > asJoint (new JointAE<AnimatedSprite>());
  rmas.insert(AS_JOINT, asJoint);

  ResourceManager<SpriteSheet<AnimatedSprite> >& rmss = ResourceManager<SpriteSheet<AnimatedSprite> >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > >& rmact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > >::getInstance();

  ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* > >& rmaact = ResourceManager<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* > >::getInstance();

  ResourceManager<std::forward_list<ActiveElement2D<ZombienoidReactor> > >& rmAE2d = ResourceManager<std::forward_list<ActiveElement2D<ZombienoidReactor> > >::getInstance();

  zombienoid::ExitInputHandler terminator;
  ieg->addHandler(zbe::ZBEK_ESCAPE, &terminator);



//drawing----------------------------------------------------------------------------------------------------
  std::shared_ptr<Daemon> drawerDaemon(new  DrawerDaemon<AnimatedSprite, TicketedForwardList<AvatarEntity<AnimatedSprite > > >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(&window, &imgStore), AS_JOINT));

  drawMaster->addDaemon(drawerDaemon);

  //board----------------------------------------------------------------------------------------------------
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > > boardActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* >());

  rmact.insert(BOARD_ACTUATORS_LIST, boardActuatorsList);

  std::shared_ptr<Element2D<ZombienoidReactor> > board(new Element2D<ZombienoidReactor>({MARGIN, MARGIN}, BOARD_ACTUATORS_LIST, WIDTH - (MARGIN * 2), HEIGHT - (MARGIN * 2), BOARD_GRAPHICS));

  //std::shared_ptr<Adaptor<AnimatedSprite> > boardSpriteAdaptor(new Element2DAnimatedSpriteAdaptor(&(*board)));
  //setAdaptor(board, boardSpriteAdaptor);

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > boardCollisionerAdaptor(new BoardConerAdaptor<ZombienoidReactor>(&(*board)));
  setAdaptor(board, boardCollisionerAdaptor);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > boardCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());

  //std::shared_ptr<TicketedFAE<AnimatedSprite> > boardAnimatedSpriteList(new TicketedFAE<AnimatedSprite>());

  board->addToList(COLLISION_TICKET, boardCollisionerList->push_front(board));
  //board->storeTicket(DRAW_TICKET, boardAnimatedSpriteList->insert(board));

  //bricks---------------------------------------------------------------------------------------------------

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > > brickActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* >());

  ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* brickEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, Avatar, Avatar, Positionable<2>, Stated >(new EraserActuator<ZombienoidReactor, zbe::VoidReactObject<ZombienoidReactor> >());
  brickActuatorsList->push_front(brickEraserWrapper);

  rmact.insert(BRICK_ACTUATORS_LIST, brickActuatorsList);

  int BRICK_GRAHPICS = imgStore.loadImg(brickImg);
  std::shared_ptr<SpriteSheet<AnimatedSprite> > brickSS(new SimpleSpriteSheet(BRICK_GRAPHICS));
  rmss.insert(BRICK_SS, brickSS);

  for(int i = 0; i < NBRICKS; i++) {

    std::shared_ptr<Element2D<ZombienoidReactor> > brick(new Element2D<ZombienoidReactor>({(BRICK_WIDTH*i)+MARGIN, MARGIN}, BRICK_ACTUATORS_LIST, BRICK_WIDTH, BRICK_HEIGHT, BRICK_SS));
    std::shared_ptr<Adaptor<AnimatedSprite> > brickSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(&(*brick)));
    setAdaptor(brick, brickSpriteAdaptor);

    std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > brickCollisionerAdaptor(new BlockConerAdaptor<ZombienoidReactor>(&(*brick)));
    setAdaptor(brick, brickCollisionerAdaptor);

    std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > brickCollisionerList(new TicketedForwardList<AvatarEntity<Collisioner<ZombienoidReactor> > >());

    std::shared_ptr<TicketedFAE<AnimatedSprite> > brickAnimatedSpriteList(new TicketedFAE<AnimatedSprite>());

    std::shared_ptr<TicketedForwardList<Element2D<ZombienoidReactor> > > brickList(new TicketedForwardList<Element2D<ZombienoidReactor> >());

    brick->addToList(COLLISION_TICKET, brickCollisionerList->push_front(brick));
    brick->addToList(DRAW_TICKET, brickAnimatedSpriteList->push_front(brick));
    brick->addToList(BEHAVE_TICKET, brickList->push_front(brick));
  }

  //ball-----------------------------------------------------------------------------------------------------

  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated >* > > ballActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated >* >());

  ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* ballBouncerWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, Bouncer<2>, Avatar, Bouncer<2>, Stated>(new BouncerActuator<ZombienoidReactor>());
  ActuatorWrapper<ZombienoidReactor, Avatar, Bouncer<2>, Stated>* ballEraserWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, Avatar, Avatar, Bouncer<2>, Stated>(new ConditionalEraserActuator<ZombienoidReactor>());
  ballActuatorsList->push_front(ballBouncerWrapper);
  ballActuatorsList->push_front(ballEraserWrapper);

  rmaact.insert(BALL_ACTUATORS_LIST, ballActuatorsList);

  int BALL_GRAHPICS = imgStore.loadImg(ballImg);
  std::shared_ptr<SpriteSheet<AnimatedSprite> > ballSS(new SimpleSpriteSheet(BALL_GRAPHICS));
  rmss.insert(BALL_SS, ballSS);

  std::shared_ptr<ActiveElement2D<ZombienoidReactor> > ball(new ActiveElement2D<ZombienoidReactor>({WIDTH/2, HEIGHT/2}, {BALL_V_X, BALL_V_Y}, BALL_ACTUATORS_LIST, BALL_CNR_JOINT, BALL_SIZE, BALL_SIZE, BALL_SS));

  std::shared_ptr<Adaptor<AnimatedSprite> > ballSpriteAdaptor(new ActiveElement2DAnimatedSpriteAdaptor<ZombienoidReactor>(&(*ball)));
  setAdaptor(ball, ballSpriteAdaptor);

  std::shared_ptr<Adaptor<Collisionator<ZombienoidReactor> > > ballCollisionatorAdaptor(new BallCatorAdaptor<ZombienoidReactor>(&(*ball)));
  setAdaptor(ball, ballCollisionatorAdaptor);

  std::shared_ptr<TicketedFAE<Collisionator<ZombienoidReactor> > > ballCollisionatorsList(new TicketedFAE<Collisionator<ZombienoidReactor> >());
  std::shared_ptr<TicketedFAE<AnimatedSprite> > ballAnimatedSpriteList(new TicketedFAE<AnimatedSprite>());

  std::shared_ptr<TicketedForwardList<ActiveElement2D<ZombienoidReactor> > > ballList(new TicketedForwardList<ActiveElement2D<ZombienoidReactor> >());

  ball->addToList(COLLISION_TICKET, ballCollisionatorsList->push_front(ball));
  ball->addToList(DRAW_TICKET, ballAnimatedSpriteList->push_front(ball));
  ball->addToList(BEHAVE_TICKET, ballList->push_front(ball));
  ctsJoint->add(ballCollisionatorsList);

  std::shared_ptr<Daemon> ballBounce(new BehaviorDaemon<Bouncer<2>, TicketedForwardList<ActiveElement2D<ZombienoidReactor> > >(std::make_shared<Bounce<2> >(), BALL_LIST));
  std::shared_ptr<Daemon> ballULM(new BehaviorDaemon<Movable<2>, TicketedForwardList<ActiveElement2D<ZombienoidReactor> > >(std::make_shared<UniformLinearMotion<2> >(), BALL_LIST));

  //bar------------------------------------------------------------------------------------------------------
  std::shared_ptr<std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* > > barActuatorsList(new std::forward_list<ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* >());
  //ActuatorWrapper<ZombienoidReactor, Avatar, Positionable<2>, Stated >* itemCatchWrapper = new  ActuatorWrapperCommon<ZombienoidReactor, void, Avatar, Positionable<2>, Stated >(new ItemCatcher<ZombienoidReactor>());
  //barActuatorsList->push_front(itemCatchWrapper);

  rmact.insert(BAR_ACTUATORS_LIST, barActuatorsList);

  int BAR_GRAHPICS = imgStore.loadImg(barImg);

  std::shared_ptr<SpriteSheet<AnimatedSprite> > barSS(new SimpleSpriteSheet(BAR_GRAPHICS));
  rmss.insert(BAR_SS, barSS);

  std::shared_ptr<Element2D<ZombienoidReactor> > bar(new Element2D<ZombienoidReactor>({(WIDTH-BAR_I_WIDTH)/2, HEIGHT-BAR_MARGIN-BAR_HEIGHT},   BAR_ACTUATORS_LIST, BAR_I_WIDTH, BAR_HEIGHT, BAR_SS));

  std::shared_ptr<Adaptor<AnimatedSprite> > barSpriteAdaptor(new Element2DAnimatedSpriteAdaptor<ZombienoidReactor>(&(*bar)));
  setAdaptor(bar, barSpriteAdaptor);

  std::shared_ptr<Adaptor<Collisioner<ZombienoidReactor> > > barCollisionerAdaptor(new BlockConerAdaptor<ZombienoidReactor>(&(*bar)));
  setAdaptor(bar, barCollisionerAdaptor);

  std::shared_ptr<TicketedFAE<Collisioner<ZombienoidReactor> > > barCollisionerList(new TicketedFAE<Collisioner<ZombienoidReactor> >());

  std::shared_ptr<TicketedFAE<AnimatedSprite> > barAnimatedSpriteList(new TicketedFAE<AnimatedSprite>());

  std::shared_ptr<TicketedForwardList<Element2D<ZombienoidReactor> > > barList(new TicketedForwardList<Element2D<ZombienoidReactor> >());

  bar->addToList(COLLISION_TICKET, barCollisionerList->push_front(bar));
  bar->addToList(DRAW_TICKET, barAnimatedSpriteList->push_front(bar));
  bar->addToList(BEHAVE_TICKET, barList->push_front(bar));

  //std::shared_ptr<Daemon> barMouseFollow(new BehaviorDaemon<Positionable<2>, TicketedForwardList<ActiveElement2D<ZombienoidReactor> > >(std::make_shared<MouseXIH>(bar), BAR_LIST));

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
  mainLoop.loop();

  return 0;
}
} //namespace zombieBall
