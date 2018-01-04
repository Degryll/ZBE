#include "ludomain.h"

#include <cinttypes>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <math.h>

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
#include "ZBE/core/tools/graphics/SpriteSheet.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/MainLoop.h"

#include "ZBE/core/daemons/BasicPreLoopTimeDaemon.h"
#include "ZBE/core/daemons/Punishers.h"

#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/MobileAPO.h"

#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/Bounce.h"
#include "ZBE/entities/adaptors/SimpleDrawableSingleSpriteAdaptor.h"

#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"
#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"
#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"
#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"

#include "zombienoid/graphics/MultiSpriteSheet.h"

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

#define PI 3.14159265

namespace ludo {

using namespace zbe;

template<typename T>
using TicketedAE = TicketedForwardList<AvatarEntity<T> >;

template <typename ...Avatars>
using TicketedAEC = TicketedForwardList<AvatarEntityContainer<Avatars...> >;

int ludomain(int, char** ) {

//  printf("--- Ludo main ---\n\n");
//
//  enum {
//    WIDTH = 1024,
//    HEIGHT = 768,
//    MARGIN = 50,
//    LEFT_PANEL = 300,
//    BOARD_WIDTH = WIDTH - MARGIN - LEFT_PANEL,
//    BOARD_HEIGHT = HEIGHT - MARGIN
//  };
//
//  //int GENERATORLIST = SysIdGenerator::getId();
//
//  const int INPUTEVENT = SysIdGenerator::getId();
//  const int COLLISIONEVENT = SysIdGenerator::getId();
//  const int TIMEEVENT = SysIdGenerator::getId();
//
//  const int COLLISIONATORLIST = SysIdGenerator::getId();
//  const int MOVABLELIST = SysIdGenerator::getId();
//  const int BOUNCERLIST = MOVABLELIST;
//  const int LROTATORS = SysIdGenerator::getId();
//  const int RROTATORS = SysIdGenerator::getId();
//  const int PARTICLES = SysIdGenerator::getId();
//  const int ROTATORS = SysIdGenerator::getId();
//  const int BALLACTUATORLIST = SysIdGenerator::getId();
//  const int COLLISIONABLELIST = SysIdGenerator::getId();
//  const int INTERSECTCNRLIST = SysIdGenerator::getId();
//  const int INTERSECTCTRLIST = SysIdGenerator::getId();
//  const int BOARDACTUATORLIST = SysIdGenerator::getId();
//  //int BRICKACTUATORLIST = SysIdGenerator::getId();
//  const int SPRITELIST = SysIdGenerator::getId();
//  const int RSPRITELIST = SysIdGenerator::getId();
//  const int SETABLEGRAPHSLIST = SysIdGenerator::getId();
//
//  const char zomballImg[] = "data/images/zombieball/zomball_st_32.png";
//  const char simpleBallImg[] = "data/images/zombieball/simple_ball_32.png";
//  const char mouseImg[] = "data/images/zombieball/mouse.png";
//  const char arrowImg[] = "data/images/ludo/arrow_r_000_32.png";
////  const char brickfilename[] = "data/images/zombieball/braikn_32.png";
//  const char bulletImg[] = "data/images/zombieball/bullet001.png";
//  const char orb[] = "data/images/ludo/orb_001_128.png";
//  unsigned ballgraphics[6];
//
//  printf("|=================== Building up system ===================|\n");fflush(stdout);
//
//  printf("Building generator master\n");fflush(stdout);
//  //DaemonMaster gema;
//  std::shared_ptr<DaemonMaster> gema(new DaemonMaster());
//  printf("|------------------------ Input Event Generator-------------|\n");fflush(stdout);
//  printf("Building SDLEventDispatcher\n");fflush(stdout);
//  printf("Will extract data from SDL and get it usable for the engine\n");fflush(stdout);
//  SDLEventDispatcher & sdlEventDist = SDLEventDispatcher::getInstance();
//  printf("Acquiring InputBuffer\n");fflush(stdout);
//  printf("SDLEventDispatcher Will store input changes for a frame into it\n");fflush(stdout);
//  InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
//  printf("Acquiring and configuring InputEventGenerator with that InputReader\n");fflush(stdout);
//  printf("Will read events from the InputReader and send them to the store\n");fflush(stdout);
//  printf("Input events will use id 0\n");fflush(stdout);
//  std::shared_ptr<InputEventGenerator> ieg(new InputEventGenerator(inputBuffer,INPUTEVENT));
//  //gema.addDaemon(ieg);
//  gema->addDaemon(ieg);
//  printf("|-------------------- Input keys config -------------------|\n");fflush(stdout);
//  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
//  game::ExitInputHandler terminator;
//  ieg->addHandler(ZBEK_ESCAPE, &terminator);
//  ieg->addHandler(ZBEK_RETURN, &terminator);
//  printf("|------------------- Collision Event Generator-------------|\n");fflush(stdout);
//  printf("Building lists for collisionator entinties. Currently empty.\n");fflush(stdout);
//  printf("It will store entities that will search for a collision.\n");fflush(stdout);
//  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > > > ctl(new TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > >());
//  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > > > ctl2(new TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > >());
//  printf("Acquiring singleton list-manager for those lists .\n");fflush(stdout);
//  ResourceManager< TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > > >& lmct = ResourceManager< TicketedForwardList<AvatarEntity<Collisionator<LudoReactor> > > >::getInstance();
//  printf("Storing those in that list-manager.\n");fflush(stdout);
//  lmct.insert(COLLISIONATORLIST, ctl);
//  lmct.insert(INTERSECTCTRLIST, ctl2);
//  printf("Building collision event generator with list id and the event id to use (1).\n");fflush(stdout);
//  //std::shared_ptr<CollisionEventGenerator<LudoReactor> > ceg(new CollisionEventGenerator<LudoReactor>(COLLISIONATORLIST, COLLISIONEVENT, new BaseCollisionSelector<LudoReactor>()));
//  std::shared_ptr<InteractionEventGenerator<LudoReactor, CollisionSelector<LudoReactor>, TicketedAE<Collisioner<LudoReactor>  >, TicketedAE<Collisionator<LudoReactor> > > > ceg(new InteractionEventGenerator<LudoReactor, CollisionSelector<LudoReactor>, TicketedAE<Collisioner<LudoReactor>  >, TicketedAE<Collisionator<LudoReactor> > >(COLLISIONATORLIST, COLLISIONEVENT, new BaseCollisionSelector<LudoReactor>()));
//  gema->addDaemon(ceg);
//  printf("|------------------- Time Event Generator -----------------|\n");fflush(stdout);
//  printf("Building time event generator with the event id to use (2)\n");fflush(stdout);
//  std::shared_ptr<TimeEventGenerator> teg(new TimeEventGenerator(TIMEEVENT));
//  //gema.addDaemon(teg);
//  gema->addDaemon(teg);
//  printf("|------------------------- Time ---------------------------|\n");fflush(stdout);
//  printf("Building a SDL implementation of Timer\n");fflush(stdout);
//  Timer *sysTimer = new SDLTimer(true);
//  printf("Acquiring and configuring SysTime with that Timer\n");fflush(stdout);
//  printf("It will be the time reference for all the game context\n");fflush(stdout);
//  SysTime &sysTime = SysTime::getInstance();
//  sysTime.setSystemTimer(sysTimer);
//  printf("|-------------------- Drawing system ----------------------|\n");fflush(stdout);
//  printf("Building the window to draw on\n");fflush(stdout);
//  SDLWindow window(WIDTH,HEIGHT);
//  SDLImageStore imgStore(window.getRenderer());
//  printf("Creating draw master list\n");fflush(stdout);
//  //DaemonMaster drawMaster;
//  std::shared_ptr<DaemonMaster> drawMaster(new DaemonMaster());
//  printf("Creating drawables list\n");fflush(stdout);
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<SingleSprite> > > sprites(new TicketedForwardList<AvatarEntityContainer<SingleSprite> >());
//  ResourceManager<TicketedForwardList<AvatarEntityContainer<SingleSprite > > >& lmAESingleSprite = ResourceManager<TicketedForwardList<AvatarEntityContainer<SingleSprite> > >::getInstance();
//  lmAESingleSprite.insert(SPRITELIST, sprites);
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<RotatedSprite> > > rsprites(new TicketedForwardList<AvatarEntityContainer<RotatedSprite> >());
//  ResourceManager< TicketedForwardList<AvatarEntityContainer<RotatedSprite > > >& lmAESimpleRotatedSprite = ResourceManager<TicketedForwardList<AvatarEntityContainer<RotatedSprite> > >::getInstance();
//  lmAESimpleRotatedSprite .insert(RSPRITELIST, rsprites);
//  printf("Loading imgs\n");fflush(stdout);
//  ballgraphics[0] = imgStore.loadImg(zomballImg);
//  ballgraphics[1] = imgStore.loadImg(simpleBallImg);
//  ballgraphics[2] = imgStore.loadImg(mouseImg);
//  ballgraphics[3] = imgStore.loadImg(arrowImg);
//  ballgraphics[4] = imgStore.loadImg(bulletImg);
//  ballgraphics[5] = imgStore.loadImg(orb);
//  //brickgraphics = window.loadImg(brickfilename);
//  printf("Building the drawer to paint RotatedSprite's \n");fflush(stdout);
//  std::shared_ptr<Daemon> drawerDaemon(new  BehaviorDaemon<SingleSprite, TicketedForwardList<AvatarEntityContainer<SingleSprite > > >(std::make_shared<SingleSpriteSDLDrawer>(&window, &imgStore), SPRITELIST));
//  //drawMaster.addDaemon(drawerDaemon);
//  drawMaster->addDaemon(drawerDaemon);
//  std::shared_ptr<Daemon> rDrawerDaemon(new  BehaviorDaemon<RotatedSprite, TicketedForwardList<AvatarEntityContainer<RotatedSprite > > >(std::make_shared<SimpleRotatedSpriteSDLDrawer>(&window, &imgStore), RSPRITELIST));
//  //drawMaster.addDaemon(rDrawerDaemon);
//  drawMaster->addDaemon(rDrawerDaemon);
//  printf("|-------------------- General Daemons ---------------------|\n");fflush(stdout);
//  //DaemonMaster commonBehaviorMaster;
//  std::shared_ptr<DaemonMaster> commonBehaviorMaster(new DaemonMaster());
//  //DaemonMaster reactBehaviorMaster;
//  std::shared_ptr<DaemonMaster> reactBehaviorMaster(new DaemonMaster());
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Movable<2> > > > vAEMovable(new TicketedForwardList<AvatarEntityContainer<Movable<2> > >());
//  auto& lmAEMovable = ResourceManager<TicketedForwardList<AvatarEntityContainer<Movable<2> > > >::getInstance();
//  lmAEMovable.insert(MOVABLELIST, vAEMovable);
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Positionable<2> > > > vAEPositionable(new TicketedForwardList<AvatarEntityContainer<Positionable<2> > >());
//  auto& lmAEPositionable = ResourceManager<TicketedForwardList<AvatarEntityContainer<Positionable<2> > > >::getInstance();
//  lmAEPositionable.insert(PARTICLES, vAEPositionable);
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Bouncer<2> > > > vAEBouncer(new TicketedForwardList<AvatarEntityContainer<Bouncer<2> > >());
//  auto& lmAEBouncer = ResourceManager<TicketedForwardList<AvatarEntityContainer<Bouncer<2> > > >::getInstance();
//  lmAEBouncer.insert(BOUNCERLIST, vAEBouncer);
//  std::shared_ptr<Daemon> ballBounce(new  BehaviorDaemon<Bouncer<2>, TicketedForwardList<AvatarEntityContainer<Bouncer<2> > > >(std::make_shared<Bounce<2> >(), BOUNCERLIST));
//  std::shared_ptr<Daemon> ballULM(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntityContainer<Movable<2> > > >(std::make_shared<UniformLinearMotion<2> >(), MOVABLELIST));
//  commonBehaviorMaster->addDaemon(ballULM);
//  reactBehaviorMaster->addDaemon(ballBounce);
//  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
//  printf("Creating a ball and giving it a position and size\n");fflush(stdout);
//
//  //ball
//  std::shared_ptr<std::forward_list<ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<Avatar, Bouncer<2> > >* > > ballActuatorsList(new std::forward_list<ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<Avatar, Bouncer<2> > >* >());
//  ResourceManager< std::forward_list<ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<Avatar, Bouncer<2> > >* > >& lmBallActuatorsList = ResourceManager< std::forward_list<ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<Avatar, Bouncer<2> > >* > >::getInstance();
//  lmBallActuatorsList.insert(BALLACTUATORLIST, ballActuatorsList);
//  ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<Avatar, Bouncer<2> > >* bouncerWrapper = new  ActuatorWrapperCommon<LudoReactor, zbe::WeakAvatarEntityContainer<Bouncer<2> >, zbe::WeakAvatarEntityContainer<Avatar, Bouncer<2> > >(new LudoBallBouncer<LudoReactor>());
//  ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<Avatar, Bouncer<2> > >* eraserWrapper = new  ActuatorWrapperCommon<LudoReactor, zbe::WeakAvatarEntityContainer<Avatar>, zbe::WeakAvatarEntityContainer<Avatar, Bouncer<2> > >(new AvatarEraser<LudoReactor>());
//  ballActuatorsList->push_front(bouncerWrapper);
//  ballActuatorsList->push_front(eraserWrapper);
//
//  ResourceManager<TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > > >& lmCollisionablesList = ResourceManager< TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > > >::getInstance();
//
//  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > > > collisionablesList(new TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > >());
//  lmCollisionablesList.insert(COLLISIONABLELIST, collisionablesList);
//
//  std::shared_ptr<TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > > > intersectionablesList(new TicketedForwardList<AvatarEntity<Collisioner<LudoReactor> > >());
//  lmCollisionablesList.insert(INTERSECTCNRLIST, intersectionablesList);
//
//  ResourceManager<TicketedForwardList<SetableGraphics> >& lmSG = ResourceManager<TicketedForwardList<SetableGraphics> >::getInstance();
//  std::shared_ptr<TicketedForwardList<SetableGraphics> > setableGs(new TicketedForwardList<SetableGraphics>());
//  lmSG.insert(SETABLEGRAPHSLIST, setableGs);
//
//  GraphicsSet gSet0(ballgraphics[0],SETABLEGRAPHSLIST);
//  GraphicsSet gSet1(ballgraphics[1],SETABLEGRAPHSLIST);
//  GraphicsSet gSet2(ballgraphics[2],SETABLEGRAPHSLIST);
//  GraphicsSet gSet3(ballgraphics[3],SETABLEGRAPHSLIST);
//  ieg->addHandler(ZBEK_z, &gSet0);
//  ieg->addHandler(ZBEK_x, &gSet1);
//  ieg->addHandler(ZBEK_c, &gSet2);
//  ieg->addHandler(ZBEK_v, &gSet3);
//
//  srand(time(0));
//
//  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2> > > aecm2;
//  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Bouncer<2> > > aecb2;
//  std::shared_ptr<zbe::AvatarEntityContainer<zbe::RotatedSprite> > aecrs;
//  std::shared_ptr<zbe::AvatarEntityContainer<zbe::Positionable<2> > > aecp2;
//
//  for(int i = 0; i<1000; i++){
//    int64_t r = 16 + (rand()% 4);
//    int64_t xc =(MARGIN + (BOARD_WIDTH/2) + rand()%100-50);
//    int64_t yc = (MARGIN + (BOARD_HEIGHT/2) + rand()%100-50);
//    unsigned graphId = ballgraphics[0];
//
//    int64_t vt = 500;
//    double vAngleL = rand()%3600;
//    vAngleL/=10;
//    double vAngleR = rand()%100;
//    vAngleR/=1000;
//    double vAngle = vAngleL + vAngleR;
//    int64_t vx = sin(vAngle*PI/180)*vt;
//    int64_t vy = cos(vAngle*PI/180)*vt;
//    std::shared_ptr<LudoBall<LudoReactor> > ball = std::make_shared<LudoBall<ludo::LudoReactor> >( xc, yc, r, vx, vy, BALLACTUATORLIST, COLLISIONABLELIST, graphId);
//    std::shared_ptr<Adaptor<RotatedSprite> > spriteAdaptor = std::make_shared<RotatedDrawableSimpleRotatedSpriteAdaptor>(ball);
//    setAdaptor(ball, spriteAdaptor);
//    std::shared_ptr<Adaptor<Collisionator<LudoReactor> > > lbca = std::make_shared<LudoBallCollisionatorAdaptor<LudoReactor> >(ball);
//    setAdaptor(ball, lbca);
//
//    zbe::wrapAEC(&aecm2, ball);
//    zbe::wrapAEC(&aecb2, ball);
//    zbe::wrapAEC(&aecrs, ball);
//
//    ball->addToList(0, ctl->push_front(ball));
//    ball->addToList(1, vAEMovable->push_front(aecm2));
//    ball->addToList(2, vAEBouncer->push_front(aecb2));
//    ball->addToList(3, rsprites->push_front(aecrs));
//    ball->addToList(4, setableGs->push_front(ball));
//    ball->addToList(5, intersectionablesList->push_front(ball));
//  }
//
//  printf("Creating a rotator\n");fflush(stdout);
//  auto& lmTflAEPositionable = ResourceManager<TicketedForwardList<AvatarEntityContainer<Positionable<2> > > >::getInstance();
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Positionable<2> > > > tflAEPositionable(new TicketedForwardList<AvatarEntityContainer<Positionable<2> > >());
//  lmTflAEPositionable.insert(ROTATORS, tflAEPositionable);
//
//  auto& lmTflAEMovable = ResourceManager<TicketedForwardList<AvatarEntityContainer<Movable<2> > > >::getInstance();
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Movable<2> > > > tflAEMovable(new TicketedForwardList<AvatarEntityContainer<Movable<2> > >());
//  lmTflAEMovable.insert(ROTATORS, tflAEMovable);
//
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Movable<2> > > > tflRAEMovable(new TicketedForwardList<AvatarEntityContainer<Movable<2> > >());
//  lmTflAEMovable.insert(LROTATORS, tflRAEMovable);
//  std::shared_ptr<TicketedForwardList<AvatarEntityContainer<Movable<2> > > > tflLAEMovable(new TicketedForwardList<AvatarEntityContainer<Movable<2> > >());
//  lmTflAEMovable.insert(RROTATORS, tflLAEMovable);
//
//  std::shared_ptr<LudoBall<LudoReactor> > rotator = std::make_shared<LudoBall<ludo::LudoReactor> >( MARGIN + (BOARD_WIDTH/2), MARGIN + (BOARD_HEIGHT/2), 16, 200, 100, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics[3]);
//  std::shared_ptr<Adaptor<RotatedSprite> > spriteAdaptor = std::make_shared<RotatedDrawableSimpleRotatedSpriteAdaptor>(rotator);
//  setAdaptor(rotator, spriteAdaptor);
//  std::shared_ptr<Adaptor<Collisionator<LudoReactor> > > lbca = std::make_shared<LudoBallCollisionatorAdaptor<LudoReactor> >(rotator);
//  setAdaptor(rotator, lbca);
//
//  zbe::wrapAEC(&aecb2, rotator);
//  zbe::wrapAEC(&aecm2, rotator);
//  zbe::wrapAEC(&aecp2, rotator);
//  zbe::wrapAEC(&aecrs, rotator);
//
//  ctl->push_front(rotator);
//  vAEBouncer->push_front(aecb2);
//  rsprites->push_front(aecrs);
//  tflAEPositionable->push_front(aecp2);
//  tflAEMovable->push_front(aecm2);
//
//  printf("Giving the rotator the ability of KILL ...press K...\n");fflush(stdout);
//
//  std::shared_ptr<DaemonMaster> killMaster = std::make_shared<DaemonMaster>();
//  //Creating areas
//  std::shared_ptr<DestroyerCircleAreaCreator<LudoReactor> > dcac(new DestroyerCircleAreaCreator<LudoReactor>(64, INTERSECTCTRLIST, INTERSECTCNRLIST, BOARDACTUATORLIST));
//  std::shared_ptr<Daemon> areaCreatorDaemon(new  BehaviorDaemon<Positionable<2>, TicketedForwardList<AvatarEntityContainer<Positionable<2> > > >(dcac, ROTATORS));
//
//  //Calculating intersections
//  std::shared_ptr<IntersectionEventGenerator<LudoReactor> > iceg(new IntersectionEventGenerator<LudoReactor>(INTERSECTCTRLIST, COLLISIONEVENT, new IntersectionCollisionSelector<LudoReactor>()));
//
//
//  //Cleaning areas
//  std::shared_ptr<ListEraser<AvatarEntity<Collisionator<LudoReactor> > > > eraser(new ListEraser<AvatarEntity<Collisionator<LudoReactor> > >(INTERSECTCTRLIST));
//
//  //Doing cute stuff
//  std::shared_ptr<Daemon> explodParticle(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntityContainer<Movable<2> > > >(std::make_shared<BackBallParticlesLauncher>(64, ballgraphics[5], RSPRITELIST, teg), ROTATORS));
//
//
//  //Adding daemons
//  killMaster->addDaemon(areaCreatorDaemon);
//  killMaster->addDaemon(iceg);
//  //killMaster->addDaemon(eraser);
//  killMaster->addDaemon(explodParticle);
//  //This is erased on reactBehaviorMaster cause areas must be still present when events are managed.
//  reactBehaviorMaster->addDaemon(eraser);
//
//  DaemonInputHandler dih(killMaster);
//
//  ieg->addHandler(ZBEK_k, &dih);
//
//  auto fticket = vAEMovable->push_front(aecm2);
//  fticket->setINACTIVE();
//  TicketToggler ftoggler(fticket);
//  ieg->addHandler(ZBEK_UP, &ftoggler);
//  auto lticket = tflLAEMovable->push_front(aecm2);
//  lticket->setINACTIVE();
//  TicketToggler ltoggler(lticket);
//  ieg->addHandler(ZBEK_LEFT, &ltoggler);
//  auto rticket = tflRAEMovable->push_front(aecm2);
//  rticket->setINACTIVE();
//  TicketToggler rtoggler(rticket);
//  ieg->addHandler(ZBEK_RIGHT, &rtoggler);
//
//  printf("Pasive enities\n");fflush(stdout);
//  ResourceManager<std::forward_list<ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<void> >*> >& lmSimpleConerActuatorsList = ResourceManager<std::forward_list<ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<void> >*> >::getInstance();
//  printf("Creating the bricks\n");fflush(stdout);
//
//  printf("Creating the board and giving it a size\n");fflush(stdout);
//  std::shared_ptr<std::forward_list<ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<void> >*> > boardActuatorsList(new std::forward_list<ActuatorWrapper<LudoReactor, zbe::WeakAvatarEntityContainer<void> >*>());
//  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, boardActuatorsList);
//  std::shared_ptr<LudoBoard<LudoReactor> > board = std::make_shared<LudoBoard<LudoReactor> >(MARGIN, MARGIN, BOARD_WIDTH, BOARD_HEIGHT, BOARDACTUATORLIST);
//  collisionablesList->push_front(board);
//  std::shared_ptr<LudoBoard<LudoReactor> > board2 = std::make_shared<LudoBoard<LudoReactor> >(0, 0, WIDTH , HEIGHT , BOARDACTUATORLIST);
//  collisionablesList->push_front(board2);
//
//  //Right panel
//  const char dmg_walk[] = "data/images/ludo/platformer/Char_aaa_damaged_walk.png";
//  const char in_air[] = "data/images/ludo/platformer/Char_aaa_in_air.png";
//  const char jump_end[] = "data/images/ludo/platformer/Char_aaa_jump_end.png";
//  const char jump_start[] = "data/images/ludo/platformer/Char_aaa_jump_start.png";
//  const char walk[] = "data/images/ludo/platformer/Char_aaa_walk.png";
//  const char stand[] = "data/images/ludo/platformer/Char_aaa_stand.png";
//
//  uint64_t WALK_GRAPHICS = imgStore.loadImg(walk);
//  uint64_t DMG_WALK_GRAPHICS = imgStore.loadImg(dmg_walk);
//  uint64_t IN_AIR_GRAPHICS = imgStore.loadImg(in_air);
//  uint64_t JUMP_END_GRAPHICS = imgStore.loadImg(jump_end);
//  uint64_t JUMP_START_GRAPHICS = imgStore.loadImg(jump_start);
//  uint64_t STAND_GRAPHICS = imgStore.loadImg(stand);
//
//  zombienoid::ImgSrcDef playerGraphics;
//  playerGraphics.frameAmount = 24;
//  playerGraphics.frameDisplacemet = Vector2D({205.0,0.0});
//  playerGraphics.frameTime = SECOND / 24;
//  playerGraphics.intialRegion = Region2D({0.0,0.0},{205.0,299.0});
//  playerGraphics.imgSrcId = WALK_GRAPHICS;
//
//  zombienoid::MultiSpriteSheet* playerSheet = new zombienoid::MultiSpriteSheet(6, playerGraphics);
//
//  playerGraphics.imgSrcId = DMG_WALK_GRAPHICS;
//  playerSheet->setImgSrcDef(1,playerGraphics);
//
//  playerGraphics.frameAmount = 12;
//  //playerGraphics.frameTime = SECOND / 12;
//  playerGraphics.imgSrcId = JUMP_START_GRAPHICS;
//  playerSheet->setImgSrcDef(2,playerGraphics);
//
//  playerGraphics.frameAmount = 12;
//  //playerGraphics.frameTime = SECOND / 12;
//  playerGraphics.imgSrcId = IN_AIR_GRAPHICS;
//  playerSheet->setImgSrcDef(3,playerGraphics);
//
//  playerGraphics.frameAmount = 6;
//  //playerGraphics.frameTime = SECOND / 12;
//  playerGraphics.imgSrcId = JUMP_END_GRAPHICS;
//  playerSheet->setImgSrcDef(4,playerGraphics);
//
//  playerGraphics.frameAmount = 12;
//  //playerGraphics.frameTime = SECOND / 12;
//  playerGraphics.imgSrcId = STAND_GRAPHICS;
//  playerSheet->setImgSrcDef(5,playerGraphics);
//
//  zombienoid::ImgSrcDef bulletGraphics;
//  bulletGraphics.frameAmount = 11;
//  bulletGraphics.frameDisplacemet = Vector2D({20.0,0.0});
//  bulletGraphics.frameTime = SECOND / 24;
//  bulletGraphics.intialRegion = Region2D({0.0,0.0},{20.0,20.0});
//  bulletGraphics.imgSrcId = ballgraphics[4];
//
//  zombienoid::MultiSpriteSheet* bulletSheet = new zombienoid::MultiSpriteSheet(1, bulletGraphics);
//
//  const int AS_LIST = SysIdGenerator::getId();
//  const int PLAYER_SS = SysIdGenerator::getId();
//  const int BULLET_SS = SysIdGenerator::getId();
//
//  ResourceManager<SpriteSheet<AnimatedSprite> >& rmss = ResourceManager<SpriteSheet<AnimatedSprite> >::getInstance();
//  std::shared_ptr<SpriteSheet<AnimatedSprite> > playerSS(playerSheet);
//  rmss.insert(PLAYER_SS, playerSS);
//  std::shared_ptr<SpriteSheet<AnimatedSprite> > bulletSS(bulletSheet);
//  rmss.insert(BULLET_SS, bulletSS);
//
//  ResourceManager<TicketedAEC<AnimatedSprite> >& rmtfaecas = ResourceManager<TicketedAEC<AnimatedSprite> >::getInstance();
//  std::shared_ptr<TicketedAEC<AnimatedSprite> > itemAnimatedSpriteList(new TicketedAEC<AnimatedSprite>());
//  rmtfaecas.insert(AS_LIST, itemAnimatedSpriteList);
//  std::shared_ptr<Daemon> mssDrawerDaemon(new  BehaviorDaemon<AnimatedSprite, TicketedAEC<AnimatedSprite> >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(&window, &imgStore), AS_LIST));
//  drawMaster->addDaemon(mssDrawerDaemon);
//
//  std::shared_ptr<GraphicElement> ge = std::make_shared<GraphicElement>(800, 50, 205, 299, 0, PLAYER_SS, 0, 0);
//  std::shared_ptr<Adaptor<AnimatedSprite> > sAdaptor = std::make_shared<GraphicElementAnimatedSpriteAdaptor>(ge);
//  std::shared_ptr<AvatarEntityAdapted<AnimatedSprite> > aeaas = std::make_shared<AvatarEntityAdapted<AnimatedSprite> >();
//  setAdaptor(aeaas, sAdaptor);
//  std::shared_ptr<AvatarEntityContainer<AnimatedSprite> > aecas = std::make_shared<AvatarEntityContainer<AnimatedSprite> >(aeaas);
//
//  std::shared_ptr<Daemon> stateRotator(new  StateRotator(ge, 0, 5));
//  std::shared_ptr<TimeHandler> stateRotatorTimer = std::make_shared<DemonRecurrentTimeHandler>(stateRotator, teg, SECOND * 2);
//  teg->addTimer(stateRotatorTimer, SECOND * 2);
//
//  itemAnimatedSpriteList->push_front(aecas);
//
//  std::shared_ptr<GraphicElement> ge1 = std::make_shared<GraphicElement>(700, 50, 100, 150, 0, PLAYER_SS, 0, 0);
//  sAdaptor = std::make_shared<GraphicElementAnimatedSpriteAdaptor>(ge1);
//  aeaas = std::make_shared<AvatarEntityAdapted<AnimatedSprite> >();
//  setAdaptor(aeaas, sAdaptor);
//  aecas = std::make_shared<AvatarEntityContainer<AnimatedSprite> >(aeaas);
//
//  std::shared_ptr<Daemon> stateRotator1(new  StateRotator(ge1, 0, 5));
//  std::shared_ptr<TimeHandler> stateRotatorTimer1 = std::make_shared<DemonRecurrentTimeHandler>(stateRotator1, teg, SECOND * 2);
//  teg->addTimer(stateRotatorTimer1, SECOND * 2);
//
//  TicketedForwardList<GraphicElement> bullets;
//
//  itemAnimatedSpriteList->push_front(aecas);
//  for(int i = 0;i < 9; i++){
//    for(int j = 0;j < 12; j++){
//      std::shared_ptr<GraphicElement> ge2 = std::make_shared<GraphicElement>(700 + 30*i , 340 + 30*j , 60, 60, 0, BULLET_SS, 0, ((SECOND / 24) * (i+j))) ;
//      sAdaptor = std::make_shared<GraphicElementAnimatedSpriteAdaptor>(ge2);
//      aeaas = std::make_shared<AvatarEntityAdapted<AnimatedSprite> >();
//      setAdaptor(aeaas, sAdaptor);
//      aecas = std::make_shared<AvatarEntityContainer<AnimatedSprite> >(aeaas);
//
//      itemAnimatedSpriteList->push_front(aecas);
//      bullets.push_front(ge2);
//    }
//  }
//
//
//  printf("|=================== Starting up system ===================|\n");fflush(stdout);
//  printf("Starting SysTimer\n");fflush(stdout);
//  sysTimer->start();
//  printf("Acquiring sdl info for the first time\n");fflush(stdout);
//  printf("Input data will be stored into the InputReader\n");fflush(stdout);
//  sdlEventDist.run();
//  printf("Updating system time.\n");fflush(stdout);
//  sysTime.update();
//  printf("|=================== adding some timers ===================|\n");fflush(stdout);
//  std::shared_ptr<Daemon> leftRotator(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntityContainer<Movable<2> > > >(std::make_shared<Rotator>(-0.1f), LROTATORS));
//  std::shared_ptr<TimeHandler> rotatorL = std::make_shared<DemonRecurrentTimeHandler>(leftRotator, teg, SECOND/8);
//  teg->addTimer(rotatorL, SECOND);
//
//  std::shared_ptr<Daemon> rightRotator(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntityContainer<Movable<2> > > >(std::make_shared<Rotator>(0.1f), RROTATORS));
//  std::shared_ptr<TimeHandler> rotatorR = std::make_shared<DemonRecurrentTimeHandler>(rightRotator, teg, SECOND/8);
//  teg->addTimer(rotatorR, SECOND);
//
//  std::shared_ptr<Daemon> ballParticles(new  BehaviorDaemon<Movable<2>, TicketedForwardList<AvatarEntityContainer<Movable<2> > > >(std::make_shared<BackBallParticlesLauncher>(8, ballgraphics[4], RSPRITELIST, teg), MOVABLELIST));
//  std::shared_ptr<TimeHandler> expeller = std::make_shared<DemonRecurrentTimeHandler>(ballParticles, teg, SECOND/16);
//  teg->addTimer(expeller, SECOND/16);
//  printf("|==========================================================|\n");fflush(stdout);
//
//  std::shared_ptr<Daemon> prltd = std::make_shared<BasicPreLoopTimeDaemon>();
//  std::shared_ptr<Daemon> prlsdl = std::make_shared<BasicPreLoopSDLDaemon>(&window);
//  std::shared_ptr<Daemon> postLoop = std::make_shared<BasicPostLoopSDLDaemon>(&window);
//  std::shared_ptr<DaemonMaster> preLoop(new DaemonMaster());
//
//  preLoop->addDaemon(prlsdl);
//  preLoop->addDaemon(prltd);
//
//  MainLoop mainLoop(preLoop, postLoop, gema, commonBehaviorMaster, reactBehaviorMaster, drawMaster);
//  mainLoop.run();
//
  return 0;
}

} //namespace Ludo
