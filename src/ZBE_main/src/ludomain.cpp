#include "ludomain.h"

#include <cinttypes>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "ZBE/core/daemons/DaemonMaster.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/implementations/VoidCollisioner.h"
#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/events/generators/util/CollisionSelector.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"
#include "ZBE/core/events/generators/util/IntersectionCollisionSelector.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
#include "ZBE/core/events/generators/IntersectionEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/events/handlers/ActuatorWrapper.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/tools/Timer.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/daemons/Punishers.h"
#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/MobileAPO.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/Bounce.h"
#include "ZBE/entities/adaptors/SimpleDrawableSingleSpriteAdaptor.h"
#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"
#include "ZBE/SDL/system/Window.h"
#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"

#include "game/events/handlers/ExitInputHandler.h"

#include "ludo/LudoReactor.h"
#include "ludo/behaviors/LudoBehaviors.h"
#include "ludo/daemons/LudoDaemons.h"
#include "ludo/drawers/LudoDrawers.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/entities/LudoAvatars.h"
#include "ludo/entities/LudoAdaptors.h"
#include "ludo/events/handlers/LudoActuators.h"
#include "ludo/events/handlers/LudoHandlers.h"

#include "ZBE/core/system/MainLoop.h"
#include "ZBE/core/daemons/BasicPreLoopTimeDaemon.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"
#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"

#define PI 3.14159265

namespace ludo {

using namespace zbe;

template<typename T>
using TicketedAE = TicketedForwardList<AvatarEntity<T> >;

int ludomain(int, char** ) {

  printf("--- Ludo main ---\n\n");

  enum {
    WIDTH = 1024,
    HEIGHT = 768
  };

  //int GENERATORLIST = zbe::SysIdGenerator::getId();

  const int INPUTEVENT = SysIdGenerator::getId();
  const int COLLISIONEVENT = SysIdGenerator::getId();
  const int TIMEEVENT = SysIdGenerator::getId();

  const int COLLISIONATORLIST = SysIdGenerator::getId();
  const int MOVABLELIST = SysIdGenerator::getId();
  const int BOUNCERLIST = MOVABLELIST;
  const int LROTATORS = SysIdGenerator::getId();
  const int RROTATORS = SysIdGenerator::getId();
  const int PARTICLES = SysIdGenerator::getId();
  const int ROTATORS = SysIdGenerator::getId();
  const int BALLACTUATORLIST = SysIdGenerator::getId();
  const int COLLISIONABLELIST = SysIdGenerator::getId();
  const int INTERSECTCNRLIST = SysIdGenerator::getId();
  const int INTERSECTCTRLIST = SysIdGenerator::getId();
  const int BOARDACTUATORLIST = SysIdGenerator::getId();
  //int BRICKACTUATORLIST = SysIdGenerator::getId();
  const int SPRITELIST = SysIdGenerator::getId();
  const int RSPRITELIST = SysIdGenerator::getId();
  const int SETABLEGRAPHSLIST = SysIdGenerator::getId();

  const char zomballImg[] = "data/images/zombieball/zomball_st_32.png";
  const char simpleBallImg[] = "data/images/zombieball/simple_ball_32.png";
  const char mouseImg[] = "data/images/zombieball/mouse.png";
  const char arrowImg[] = "data/images/ludo/arrow_r_000_32.png";
//  const char brickfilename[] = "data/images/zombieball/braikn_32.png";
  const char bulletImg[] = "data/images/zombieball/bullet001.png";
  const char orb[] = "data/images/ludo/orb_001_128.png";
  unsigned ballgraphics[6];

  printf("|=================== Building up system ===================|\n");fflush(stdout);

  printf("Building generator master\n");fflush(stdout);
  //DaemonMaster gema;
  std::shared_ptr<zbe::DaemonMaster> gema(new zbe::DaemonMaster());
  printf("|------------------------ Input Event Generator-------------|\n");fflush(stdout);
  printf("Building SDLEventDispatcher\n");fflush(stdout);
  printf("Will extract data from SDL and get it usable for the engine\n");fflush(stdout);
  SDLEventDispatcher & sdlEventDist = SDLEventDispatcher::getInstance();
  printf("Acquiring InputBuffer\n");fflush(stdout);
  printf("SDLEventDispatcher Will store input changes for a frame into it\n");fflush(stdout);
  InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
  printf("Acquiring and configuring InputEventGenerator with that InputReader\n");fflush(stdout);
  printf("Will read events from the InputReader and send them to the store\n");fflush(stdout);
  printf("Input events will use id 0\n");fflush(stdout);
  std::shared_ptr<InputEventGenerator> ieg(new InputEventGenerator(inputBuffer,INPUTEVENT));
  //gema.addDaemon(ieg);
  gema->addDaemon(ieg);
  printf("|-------------------- Input keys config -------------------|\n");fflush(stdout);
  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
  game::ExitInputHandler terminator;
  ieg->addHandler(ZBEK_ESCAPE, &terminator);
  ieg->addHandler(ZBEK_RETURN, &terminator);
  printf("|------------------- Collision Event Generator-------------|\n");fflush(stdout);
  printf("Building lists for collisionator entinties. Currently empty.\n");fflush(stdout);
  printf("It will store entities that will search for a collision.\n");fflush(stdout);
  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > > > ctl(new TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > >());
  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > > > ctl2(new TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > >());
  printf("Acquiring singleton list-manager for those lists .\n");fflush(stdout);
  ListManager< TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > > >& lmct = ListManager< TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > > >::getInstance();
  printf("Storing those in that list-manager.\n");fflush(stdout);
  lmct.insert(COLLISIONATORLIST, ctl);
  lmct.insert(INTERSECTCTRLIST, ctl2);
  printf("Building collision event generator with list id and the event id to use (1).\n");fflush(stdout);
  //std::shared_ptr<CollisionEventGenerator<LudoReactor> > ceg(new CollisionEventGenerator<LudoReactor>(COLLISIONATORLIST, COLLISIONEVENT, new BaseCollisionSelector<LudoReactor>()));
  std::shared_ptr<InteractionEventGenerator<LudoReactor, CollisionSelector<LudoReactor>, TicketedAE<Collisioner<LudoReactor>  >, TicketedAE<Collisionator<LudoReactor> > > > ceg(new InteractionEventGenerator<LudoReactor, CollisionSelector<LudoReactor>, TicketedAE<Collisioner<LudoReactor>  >, TicketedAE<Collisionator<LudoReactor> > >(COLLISIONATORLIST, COLLISIONEVENT, new BaseCollisionSelector<LudoReactor>()));
  gema->addDaemon(ceg);
  printf("|------------------- Time Event Generator -----------------|\n");fflush(stdout);
  printf("Building time event generator with the event id to use (2)\n");fflush(stdout);
  std::shared_ptr<TimeEventGenerator> teg(new TimeEventGenerator(TIMEEVENT));
  //gema.addDaemon(teg);
  gema->addDaemon(teg);
  printf("|------------------------- Time ---------------------------|\n");fflush(stdout);
  printf("Building a SDL implementation of Timer\n");fflush(stdout);
  Timer *sysTimer = new SDLTimer(true);
  printf("Acquiring and configuring SysTime with that Timer\n");fflush(stdout);
  printf("It will be the time reference for all the game context\n");fflush(stdout);
  SysTime &sysTime = SysTime::getInstance();
  sysTime.setSystemTimer(sysTimer);
  printf("|-------------------- Drawing system ----------------------|\n");fflush(stdout);
  printf("Building the window to draw on\n");fflush(stdout);
  Window window(WIDTH,HEIGHT);
  printf("Creating draw master list\n");fflush(stdout);
  //DaemonMaster drawMaster;
  std::shared_ptr<zbe::DaemonMaster> drawMaster(new zbe::DaemonMaster());
  printf("Creating drawables list\n");fflush(stdout);
  std::shared_ptr<TicketedForwardList<AvatarEntity<SingleSprite> > > sprites(new TicketedForwardList<AvatarEntity<SingleSprite> >());
  ListManager<TicketedForwardList<AvatarEntity<SingleSprite > > >& lmAESingleSprite = ListManager<TicketedForwardList<AvatarEntity<SingleSprite> > >::getInstance();
  lmAESingleSprite.insert(SPRITELIST, sprites);
  std::shared_ptr<TicketedForwardList<AvatarEntity<SimpleRotatedSprite> > > rsprites(new TicketedForwardList<AvatarEntity<SimpleRotatedSprite> >());
  ListManager< TicketedForwardList<AvatarEntity<SimpleRotatedSprite > > >& lmAESimpleRotatedSprite = ListManager<TicketedForwardList<AvatarEntity<SimpleRotatedSprite> > >::getInstance();
  lmAESimpleRotatedSprite .insert(RSPRITELIST, rsprites);
  printf("Loading imgs\n");fflush(stdout);
  ballgraphics[0] = window.loadImg(zomballImg);
  ballgraphics[1] = window.loadImg(simpleBallImg);
  ballgraphics[2] = window.loadImg(mouseImg);
  ballgraphics[3] = window.loadImg(arrowImg);
  ballgraphics[4] = window.loadImg(bulletImg);
  ballgraphics[5] = window.loadImg(orb);
  //brickgraphics = window.loadImg(brickfilename);
  printf("Building the drawer to paint SimpleRotatedSprite's \n");fflush(stdout);
  std::shared_ptr<Daemon> drawerDaemon(new  DrawerDaemon<SingleSprite, TicketedForwardList<AvatarEntity<SingleSprite > > >(std::make_shared<SingleSpriteSDLDrawer>(&window), SPRITELIST));
  //drawMaster.addDaemon(drawerDaemon);
  drawMaster->addDaemon(drawerDaemon);
  std::shared_ptr<Daemon> rDrawerDaemon(new  DrawerDaemon<SimpleRotatedSprite, TicketedForwardList<AvatarEntity<SimpleRotatedSprite > > >(std::make_shared<SimpleRotatedSpriteSDLDrawer>(&window), RSPRITELIST));
  //drawMaster.addDaemon(rDrawerDaemon);
  drawMaster->addDaemon(rDrawerDaemon);
  printf("|-------------------- General Daemons ---------------------|\n");fflush(stdout);
  //DaemonMaster commonBehaviorMaster;
  std::shared_ptr<zbe::DaemonMaster> commonBehaviorMaster(new zbe::DaemonMaster());
  //DaemonMaster reactBehaviorMaster;
  std::shared_ptr<zbe::DaemonMaster> reactBehaviorMaster(new zbe::DaemonMaster());
  std::shared_ptr<TicketedForwardList<AvatarEntity<Movable<2> > > > vAEMovable(new TicketedForwardList<AvatarEntity<Movable<2> > >());
  auto& lmAEMovable = ListManager<TicketedForwardList<AvatarEntity<Movable<2> > > >::getInstance();
  lmAEMovable.insert(MOVABLELIST, vAEMovable);
  std::shared_ptr<TicketedForwardList<AvatarEntity<Positionable<2> > > > vAEPositionable(new TicketedForwardList<AvatarEntity<Positionable<2> > >());
  auto& lmAEPositionable = ListManager<TicketedForwardList<AvatarEntity<Positionable<2> > > >::getInstance();
  lmAEPositionable.insert(PARTICLES, vAEPositionable);
  std::shared_ptr<TicketedForwardList<AvatarEntity<Bouncer<2> > > > vAEBouncer(new TicketedForwardList<AvatarEntity<Bouncer<2> > >());
  auto& lmAEBouncer = ListManager<TicketedForwardList<AvatarEntity<Bouncer<2> > > >::getInstance();
  lmAEBouncer.insert(BOUNCERLIST, vAEBouncer);
  std::shared_ptr<Daemon> ballBounce(new  BehaviorDaemon<Bouncer<2>, TicketedForwardList<AvatarEntity<Bouncer<2> > > >(std::make_shared<Bounce<2> >(), BOUNCERLIST));
  std::shared_ptr<Daemon> ballULM(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntity<Movable<2> > > >(std::make_shared<UniformLinearMotion<2> >(), MOVABLELIST));
  commonBehaviorMaster->addDaemon(ballULM);
  reactBehaviorMaster->addDaemon(ballBounce);
  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
  printf("Creating a ball and giving it a position and size\n");fflush(stdout);

  //ball
  std::shared_ptr<std::forward_list<ActuatorWrapper<LudoReactor, Avatar, Bouncer<2> >* > > ballActuatorsList(new std::forward_list<ActuatorWrapper<LudoReactor, Avatar, Bouncer<2> >* >());
  ListManager< std::forward_list<ActuatorWrapper<LudoReactor, Avatar, Bouncer<2> >* > >& lmBallActuatorsList = ListManager< std::forward_list<ActuatorWrapper<LudoReactor, Avatar, Bouncer<2> >* > >::getInstance();
  lmBallActuatorsList.insert(BALLACTUATORLIST, ballActuatorsList);
  ActuatorWrapper<LudoReactor, Avatar, Bouncer<2> >* bouncerWrapper = new  ActuatorWrapperCommon<LudoReactor, Bouncer<2>, Avatar, Bouncer<2> >(new LudoBallBouncer<LudoReactor>());
  ActuatorWrapper<LudoReactor, Avatar, Bouncer<2> >* eraserWrapper = new  ActuatorWrapperCommon<LudoReactor, Avatar, Avatar, Bouncer<2> >(new AvatarEraser<LudoReactor>());
  ballActuatorsList->push_front(bouncerWrapper);
  ballActuatorsList->push_front(eraserWrapper);

  ListManager<TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > > >& lmCollisionablesList = ListManager< TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > > >::getInstance();

  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > > > collisionablesList(new TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > >());
  lmCollisionablesList.insert(COLLISIONABLELIST, collisionablesList);

  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > > > intersectionablesList(new TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > >());
  lmCollisionablesList.insert(INTERSECTCNRLIST, intersectionablesList);

  ListManager<TicketedForwardList<SetableGraphics> >& lmSG = ListManager<TicketedForwardList<SetableGraphics> >::getInstance();
  std::shared_ptr<TicketedForwardList<SetableGraphics> > setableGs(new TicketedForwardList<SetableGraphics>());
  lmSG.insert(SETABLEGRAPHSLIST, setableGs);

  GraphicsSet gSet0(ballgraphics[0],SETABLEGRAPHSLIST);
  GraphicsSet gSet1(ballgraphics[1],SETABLEGRAPHSLIST);
  GraphicsSet gSet2(ballgraphics[2],SETABLEGRAPHSLIST);
  GraphicsSet gSet3(ballgraphics[3],SETABLEGRAPHSLIST);
  ieg->addHandler(ZBEK_z, &gSet0);
  ieg->addHandler(ZBEK_x, &gSet1);
  ieg->addHandler(ZBEK_c, &gSet2);
  ieg->addHandler(ZBEK_v, &gSet3);

  srand(time(0));
  for(int i = 0; i<1000; i++){
    int64_t r = 16 + (rand()% 4);
    int64_t xc =(WIDTH/2 + rand()%100-50);
    int64_t yc = (HEIGHT/2 + rand()%100-50);
    unsigned graphId = ballgraphics[0];

    int64_t vt = 500;
    double vAngleL = rand()%3600;
    vAngleL/=10;
    double vAngleR = rand()%100;
    vAngleR/=1000;
    double vAngle = vAngleL + vAngleR;
    int64_t vx = sin(vAngle*PI/180)*vt;
    int64_t vy = cos(vAngle*PI/180)*vt;
    std::shared_ptr<LudoBall<LudoReactor> > ball = std::make_shared<LudoBall<ludo::LudoReactor> >( xc, yc, r, vx, vy, BALLACTUATORLIST, COLLISIONABLELIST, graphId);
    std::shared_ptr<Adaptor<SimpleRotatedSprite> > spriteAdaptor = std::make_shared<RotatedDrawableSimpleRotatedSpriteAdaptor>(&(*ball));
    setAdaptor(ball, spriteAdaptor);
    std::shared_ptr<Adaptor<Collisionator<LudoReactor> > > lbca = std::make_shared<LudoBallCollisionatorAdaptor<LudoReactor> >(&(*ball));
    setAdaptor(ball, lbca);
    ball->addToList(0, ctl->push_front(ball));
    ball->addToList(1, vAEMovable->push_front(ball));
    ball->addToList(2, vAEBouncer->push_front(ball));
    ball->addToList(3, rsprites->push_front(ball));
    ball->addToList(4, setableGs->push_front(ball));
    ball->addToList(5, intersectionablesList->push_front(ball));
  }

  printf("Creating a rotator\n");fflush(stdout);
  auto& lmTflAEPositionable = ListManager<TicketedForwardList<AvatarEntity<Positionable<2> > > >::getInstance();
  std::shared_ptr<TicketedForwardList<AvatarEntity<Positionable<2> > > > tflAEPositionable(new TicketedForwardList<AvatarEntity<Positionable<2> > >());
  lmTflAEPositionable.insert(ROTATORS, tflAEPositionable);

  auto& lmTflAEMovable = ListManager<TicketedForwardList<AvatarEntity<Movable<2> > > >::getInstance();
  std::shared_ptr<TicketedForwardList<AvatarEntity<Movable<2> > > > tflAEMovable(new TicketedForwardList<AvatarEntity<Movable<2> > >());
  lmTflAEMovable.insert(ROTATORS, tflAEMovable);

  std::shared_ptr<TicketedForwardList<AvatarEntity<Movable<2> > > > tflRAEMovable(new TicketedForwardList<AvatarEntity<Movable<2> > >());
  lmTflAEMovable.insert(LROTATORS, tflRAEMovable);
  std::shared_ptr<TicketedForwardList<AvatarEntity<Movable<2> > > > tflLAEMovable(new TicketedForwardList<AvatarEntity<Movable<2> > >());
  lmTflAEMovable.insert(RROTATORS, tflLAEMovable);

  std::shared_ptr<LudoBall<LudoReactor> > rotator = std::make_shared<LudoBall<ludo::LudoReactor> >( WIDTH/2, HEIGHT/2, 16, 200, 100, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics[3]);
  std::shared_ptr<Adaptor<SimpleRotatedSprite> > spriteAdaptor = std::make_shared<RotatedDrawableSimpleRotatedSpriteAdaptor>(&(*rotator));
  setAdaptor(rotator, spriteAdaptor);
  std::shared_ptr<Adaptor<Collisionator<LudoReactor> > > lbca = std::make_shared<LudoBallCollisionatorAdaptor<LudoReactor> >(&(*rotator));
  setAdaptor(rotator, lbca);
  ctl->push_front(rotator);
  vAEBouncer->push_front(rotator);
  rsprites->push_front(rotator);
  tflAEPositionable->push_front(rotator);
  tflAEMovable->push_front(rotator);

  printf("Giving the rotator the ability of KILL ...press K...\n");fflush(stdout);

  std::shared_ptr<DaemonMaster> killMaster = std::make_shared<DaemonMaster>();
  //Creating areas
  std::shared_ptr<DestroyerCircleAreaCreator<LudoReactor> > dcac(new DestroyerCircleAreaCreator<LudoReactor>(64, INTERSECTCTRLIST, INTERSECTCNRLIST, BOARDACTUATORLIST));
  std::shared_ptr<Daemon> areaCreatorDaemon(new  BehaviorDaemon<Positionable<2>, TicketedForwardList<AvatarEntity<Positionable<2> > > >(dcac, ROTATORS));

  //Calculating intersections
  std::shared_ptr<IntersectionEventGenerator<LudoReactor> > iceg(new IntersectionEventGenerator<LudoReactor>(INTERSECTCTRLIST, COLLISIONEVENT, new IntersectionCollisionSelector<LudoReactor>()));


  //Cleaning areas
  std::shared_ptr<ListEraser<AvatarEntity<Collisionator<LudoReactor> > > > eraser(new ListEraser<AvatarEntity<Collisionator<LudoReactor> > >(INTERSECTCTRLIST));

  //Doing cute stuff
  std::shared_ptr<Daemon> explodParticle(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntity<Movable<2> > > >(std::make_shared<BackBallParticlesLauncher>(64, ballgraphics[5], RSPRITELIST, teg), ROTATORS));


  //Adding daemons
  killMaster->addDaemon(areaCreatorDaemon);
  killMaster->addDaemon(iceg);
  killMaster->addDaemon(eraser);
  killMaster->addDaemon(explodParticle);

  DaemonInputHandler dih(killMaster);

  ieg->addHandler(ZBEK_k, &dih);
  //** kill end

  auto fticket = vAEMovable->push_front(rotator);
  fticket->setINACTIVE();
  TicketToggler ftoggler(fticket);
  ieg->addHandler(ZBEK_UP, &ftoggler);
  auto lticket = tflLAEMovable->push_front(rotator);
  lticket->setINACTIVE();
  TicketToggler ltoggler(lticket);
  ieg->addHandler(ZBEK_LEFT, &ltoggler);
  auto rticket = tflRAEMovable->push_front(rotator);
  rticket->setINACTIVE();
  TicketToggler rtoggler(rticket);
  ieg->addHandler(ZBEK_RIGHT, &rtoggler);

  printf("Pasive enities\n");fflush(stdout);
  ListManager<std::forward_list<ActuatorWrapper<LudoReactor, void >*> >& lmSimpleConerActuatorsList = ListManager<std::forward_list<ActuatorWrapper<LudoReactor, void>*> >::getInstance();
  printf("Creating the bricks\n");fflush(stdout);

  printf("Creating the board and giving it a size\n");fflush(stdout);
  std::shared_ptr<std::forward_list<ActuatorWrapper<LudoReactor, void>*> > boardActuatorsList(new std::forward_list<ActuatorWrapper<LudoReactor, void>*>());
  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, boardActuatorsList);
  std::shared_ptr<LudoBoard<LudoReactor> > board = std::make_shared<LudoBoard<LudoReactor> >(50, 50, WIDTH - 50, HEIGHT - 50, BOARDACTUATORLIST);
  collisionablesList->push_front(board);
  std::shared_ptr<LudoBoard<LudoReactor> > board2 = std::make_shared<LudoBoard<LudoReactor> >(0, 0, WIDTH , HEIGHT , BOARDACTUATORLIST);
  collisionablesList->push_front(board2);

  printf("|=================== Starting up system ===================|\n");fflush(stdout);
  printf("Starting SysTimer\n");fflush(stdout);
  sysTimer->start();
  printf("Acquiring sdl info for the first time\n");fflush(stdout);
  printf("Input data will be stored into the InputReader\n");fflush(stdout);
  sdlEventDist.run();
  printf("Updating system time.\n");fflush(stdout);
  sysTime.update();
  printf("|=================== adding some timers ===================|\n");fflush(stdout);
  std::shared_ptr<Daemon> leftRotator(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntity<Movable<2> > > >(std::make_shared<Rotator>(-0.1f), LROTATORS));
  std::shared_ptr<TimeHandler> rotatorL = std::make_shared<DemonRecurrentTimeHandler>(leftRotator, teg, SECOND/8);
  teg->addTimer(rotatorL, SECOND);

  std::shared_ptr<Daemon> rightRotator(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntity<Movable<2> > > >(std::make_shared<Rotator>(0.1f), RROTATORS));
  std::shared_ptr<TimeHandler> rotatorR = std::make_shared<DemonRecurrentTimeHandler>(rightRotator, teg, SECOND/8);
  teg->addTimer(rotatorR, SECOND);

  std::shared_ptr<Daemon> ballParticles(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntity<Movable<2> > > >(std::make_shared<BackBallParticlesLauncher>(8, ballgraphics[4], RSPRITELIST, teg), MOVABLELIST));
  std::shared_ptr<TimeHandler> expeller = std::make_shared<DemonRecurrentTimeHandler>(ballParticles, teg, SECOND/16);
  teg->addTimer(expeller, SECOND/16);
  printf("|==========================================================|\n");fflush(stdout);

  std::shared_ptr<zbe::Daemon> prltd = std::make_shared<zbe::BasicPreLoopTimeDaemon>();
  std::shared_ptr<zbe::Daemon> prlsdl = std::make_shared<zbe::BasicPreLoopSDLDaemon>(&window);
  std::shared_ptr<zbe::Daemon> postLoop = std::make_shared<zbe::BasicPostLoopSDLDaemon>(&window);
  std::shared_ptr<zbe::DaemonMaster> preLoop(new zbe::DaemonMaster());

  preLoop->addDaemon(prlsdl);
  preLoop->addDaemon(prltd);

  zbe::MainLoop mainLoop(preLoop, postLoop, gema, commonBehaviorMaster, reactBehaviorMaster, drawMaster);
  mainLoop.loop();

  return 0;
}

} //namespace Ludo
