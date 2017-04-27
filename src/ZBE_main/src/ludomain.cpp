#include <cinttypes>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "ZBE/core/daemons/DaemonMaster.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/implementations/VoidCollisioner.h"
#include "ZBE/core/events/generators/GeneratorMaster.h"
#include "ZBE/core/events/generators/Generator.h"
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
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/Timer.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/daemons/Punishers.h"
#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"
#include "ZBE/SDL/system/Window.h"
#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"
#include "ZBE/entities/adaptors/SimpleDrawableSingleSpriteAdaptor.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/Bounce.h"
#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/MobileAPO.h"

#include "game/events/handlers/ExitInputHandler.h"

#include "ludo/LudoReactor.h"
#include "ludo/drawers/LudoDrawers.h"
#include "ludo/behaviors/LudoBehaviors.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/entities/LudoAvatars.h"
#include "ludo/entities/LudoAdaptors.h"
#include "ludo/events/handlers/LudoHandlers.h"
#include "ludo/events/handlers/LudoActuators.h"

#include "ludomain.h"

#define PI 3.14159265

namespace ludo {

int ludomain(int, char** ) {

  printf("--- Ludo main ---\n\n");

  enum {
    GENERATORLIST = 1,

    INPUTEVENT = 0,
    COLLISIONEVENT = 1,
    TIMEEVENT = 2,

    COLLISIONATORLIST = 1,
    MOVABLELIST = 1,
    BOUNCERLIST = MOVABLELIST,
    LROTATORS = 4,
    RROTATORS = 5,
    PARTICLES = 6,
    BALLACTUATORLIST = 1,
    COLLISIONABLELIST = 1,
    BOARDACTUATORLIST = 1,
    BRICKACTUATORLIST = 2,
    SPRITELIST = 1,
    RSPRITELIST = 2,
    SETABLEGRAPHSLIST = 1,

    WIDTH = 1024,
    HEIGHT = 768
  };

  const char zomballImg[] = "data/images/zombieball/zomball_st_32.png";
  const char simpleBallImg[] = "data/images/zombieball/simple_ball_32.png";
  const char mouseImg[] = "data/images/zombieball/mouse.png";
  const char arrowImg[] = "data/images/ludo/arrow_r_000_32.png";
//  const char brickfilename[] = "data/images/zombieball/braikn_32.png";
  const char bulletImg[] = "data/images/zombieball/bullet001.png";
  unsigned ballgraphics[5];

  printf("|=================== Building up system ===================|\n");fflush(stdout);
  printf("Event store\n");fflush(stdout);
  printf("Will store all event independently of its type\n");fflush(stdout);
  zbe::EventStore& store = zbe::EventStore::getInstance();
  printf("Building generator master\n");fflush(stdout);
  std::vector<zbe::Generator*> vGenetators;
  zbe::ListManager<std::vector<zbe::Generator*> >::getInstance().insert(GENERATORLIST, &vGenetators);
  zbe::GeneratorMaster gema(GENERATORLIST);
  printf("|------------------------ Input Event Generator-------------|\n");fflush(stdout);
  printf("Building SDLEventDispatcher\n");fflush(stdout);
  printf("Will extract data from SDL and get it usable for the engine\n");fflush(stdout);
  zbe::SDLEventDispatcher & sdlEventDist = zbe::SDLEventDispatcher::getInstance();
  printf("Acquiring InputBuffer\n");fflush(stdout);
  printf("SDLEventDispatcher Will store input changes for a frame into it\n");fflush(stdout);
  zbe::InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
  printf("Acquiring and configuring InputEventGenerator with that InputReader\n");fflush(stdout);
  printf("Will read events from the InputReader and send them to the store\n");fflush(stdout);
  printf("Input events will use id 0\n");fflush(stdout);
  zbe::InputEventGenerator ieg(inputBuffer,INPUTEVENT);
  vGenetators.push_back(&ieg);
  printf("|-------------------- Input keys config -------------------|\n");fflush(stdout);
  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
  game::ExitInputHandler terminator;
  ieg.addHandler(zbe::ZBEK_ESCAPE, &terminator);
  ieg.addHandler(zbe::ZBEK_RETURN, &terminator);
  printf("|------------------- Collision Event Generator-------------|\n");fflush(stdout);
  printf("Building list for collisionator entinties. Currently empty.\n");fflush(stdout);
  printf("It will store entities that will search for a collision.\n");fflush(stdout);
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<LudoReactor> > > ctl;
  printf("Acquiring singleton list-manager for this list (ctl).\n");fflush(stdout);
  zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<LudoReactor> > > >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<LudoReactor> > > >::getInstance();
  printf("Storing ctl in that list-manager.\n");fflush(stdout);
  lmct.insert(COLLISIONATORLIST, &ctl);
  printf("Building collision event generator with list id and the event id to use (1).\n");fflush(stdout);
  zbe::CollisionEventGenerator<LudoReactor> ceg(COLLISIONATORLIST, COLLISIONEVENT, new zbe::BaseCollisionSelector<LudoReactor>());
  vGenetators.push_back(&ceg);
  printf("|------------------- Time Event Generator -----------------|\n");fflush(stdout);
  printf("Building time event generator with the event id to use (2)\n");fflush(stdout);
  zbe::TimeEventGenerator teg(TIMEEVENT);
  vGenetators.push_back(&teg);
  printf("|------------------------- Time ---------------------------|\n");fflush(stdout);
  printf("Building a SDL implementation of Timer\n");fflush(stdout);
  zbe::Timer *sysTimer = new zbe::SDLTimer(true);
  printf("Acquiring and configuring SysTime with that Timer\n");fflush(stdout);
  printf("It will be the time reference for all the game context\n");fflush(stdout);
  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
  sysTime.setSystemTimer(sysTimer);
  printf("|-------------------- Drawing system ----------------------|\n");fflush(stdout);
  printf("Building the window to draw on\n");fflush(stdout);
  zbe::Window window(WIDTH,HEIGHT);
  printf("Creating draw master list\n");fflush(stdout);
  zbe::DaemonMaster drawMaster;
  printf("Creating drawables list\n");fflush(stdout);
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite> > sprites;
  zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite > > >& lmAESingleSprite = zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite> > >::getInstance();
  lmAESingleSprite.insert(SPRITELIST, &sprites);
  zbe::TicketedForwardList<zbe::AvatarEntity<SimpleRotatedSprite> > rsprites;
  zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<SimpleRotatedSprite > > >& lmAESimpleRotatedSprite = zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<SimpleRotatedSprite> > >::getInstance();
  lmAESimpleRotatedSprite .insert(RSPRITELIST, &rsprites);
  printf("Loading imgs\n");fflush(stdout);
  ballgraphics[0] = window.loadImg(zomballImg);
  ballgraphics[1] = window.loadImg(simpleBallImg);
  ballgraphics[2] = window.loadImg(mouseImg);
  ballgraphics[3] = window.loadImg(arrowImg);
  ballgraphics[4] = window.loadImg(bulletImg);
  //brickgraphics = window.loadImg(brickfilename);
  printf("Building the drawer to paint SimpleRotatedSprite's \n");fflush(stdout);
  std::shared_ptr<zbe::Daemon> drawerDaemon(new  zbe::DrawerDaemon<zbe::SingleSprite, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite > > >(std::make_shared<zbe::SingleSpriteSDLDrawer>(&window), SPRITELIST));
  drawMaster.addDaemon(drawerDaemon);
  std::shared_ptr<zbe::Daemon> rDrawerDaemon(new  zbe::DrawerDaemon<SimpleRotatedSprite, zbe::TicketedForwardList<zbe::AvatarEntity<SimpleRotatedSprite > > >(std::make_shared<SimpleRotatedSpriteSDLDrawer>(&window), RSPRITELIST));
  drawMaster.addDaemon(rDrawerDaemon);
  printf("|-------------------- Daemons ----------------------|\n");fflush(stdout);
  zbe::DaemonMaster commonBehaviorMaster;
  zbe::DaemonMaster reactBehaviorMaster;
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > vAEMovable;
  auto& lmAEMovable = zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > >::getInstance();
  lmAEMovable.insert(MOVABLELIST, &vAEMovable);
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Positionable<2> > > vAEPositionable;
  auto& lmAEPositionable = zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Positionable<2> > > >::getInstance();
  lmAEPositionable.insert(PARTICLES, &vAEPositionable);
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Bouncer<2> > > vAEBouncer;
  auto& lmAEBouncer = zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Bouncer<2> > > >::getInstance();
  lmAEBouncer.insert(BOUNCERLIST, &vAEBouncer);
  std::shared_ptr<zbe::Daemon> ballBounce(new  zbe::BehaviorDaemon<zbe::Bouncer<2>, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Bouncer<2> > > >(std::make_shared<zbe::Bounce<2> >(), BOUNCERLIST));
  std::shared_ptr<zbe::Daemon> ballULM(new  zbe::BehaviorDaemon<zbe::Movable<2>, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > >(std::make_shared<zbe::UniformLinearMotion<2> >(), MOVABLELIST));
  commonBehaviorMaster.addDaemon(ballULM);
  reactBehaviorMaster.addDaemon(ballBounce);
  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
  printf("Creating a ball and giving it a position and size\n");fflush(stdout);

  //ball
  std::forward_list< zbe::Actuator< zbe::Bouncer<2>, LudoReactor >*> ballActuatorsList;
  zbe::ListManager< std::forward_list< zbe::Actuator< zbe::Bouncer<2>, LudoReactor >* > >& lmBallActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator< zbe::Bouncer<2>, LudoReactor >* > >::getInstance();
  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
  LudoBallBouncer<LudoReactor> gbBouncer;
  ballActuatorsList.push_front(&gbBouncer);

  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<LudoReactor> > > collisionablesList;
  zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<LudoReactor> > > >& lmCollisionablesList = zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<LudoReactor> > > >::getInstance();
  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);

  zbe::ListManager<zbe::TicketedForwardList<SetableGraphics> >& lmSG = zbe::ListManager<zbe::TicketedForwardList<SetableGraphics> >::getInstance();
  zbe::TicketedForwardList<SetableGraphics> setableGs;
  lmSG.insert(SETABLEGRAPHSLIST, &setableGs);

  GraphicsSet gSet0(ballgraphics[0],SETABLEGRAPHSLIST);
  GraphicsSet gSet1(ballgraphics[1],SETABLEGRAPHSLIST);
  GraphicsSet gSet2(ballgraphics[2],SETABLEGRAPHSLIST);
  GraphicsSet gSet3(ballgraphics[3],SETABLEGRAPHSLIST);
  ieg.addHandler(zbe::ZBEK_z, &gSet0);
  ieg.addHandler(zbe::ZBEK_x, &gSet1);
  ieg.addHandler(zbe::ZBEK_c, &gSet2);
  ieg.addHandler(zbe::ZBEK_v, &gSet3);

  srand(time(0));
  for(int i = 0; i<100 ; i++){
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
    std::shared_ptr<zbe::Adaptor<SimpleRotatedSprite> > spriteAdaptor = std::make_shared<RotatedDrawableSimpleRotatedSpriteAdaptor>(&(*ball));
    zbe::setAdaptor(ball, spriteAdaptor);
    std::shared_ptr<zbe::Adaptor<zbe::Collisionator<LudoReactor> > > lbca = std::make_shared<LudoBallCollisionatorAdaptor<LudoReactor> >(&(*ball));
    zbe::setAdaptor(ball, lbca);
    ctl.push_front(ball);
    vAEMovable.push_front(ball);
    vAEBouncer.push_front(ball);
    rsprites.push_front(ball);
    setableGs.push_front(ball);
  }

  printf("Creating a rotator\n");fflush(stdout);
  auto& lmTflAEMovable = zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > >::getInstance();
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > tflRAEMovable;
  lmTflAEMovable.insert(LROTATORS, &tflRAEMovable);
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > tflLAEMovable;
  lmTflAEMovable.insert(RROTATORS, &tflLAEMovable);

  std::shared_ptr<LudoBall<LudoReactor> > rotator = std::make_shared<LudoBall<ludo::LudoReactor> >( WIDTH/2, HEIGHT/2, 16, 200, 100, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics[3]);
  std::shared_ptr<zbe::Adaptor<SimpleRotatedSprite> > spriteAdaptor = std::make_shared<RotatedDrawableSimpleRotatedSpriteAdaptor>(&(*rotator));
  zbe::setAdaptor(rotator, spriteAdaptor);
  std::shared_ptr<zbe::Adaptor<zbe::Collisionator<LudoReactor> > > lbca = std::make_shared<LudoBallCollisionatorAdaptor<LudoReactor> >(&(*rotator));
  zbe::setAdaptor(rotator, lbca);
  ctl.push_front(rotator);
  vAEBouncer.push_front(rotator);
  rsprites.push_front(rotator);


  auto fticket = vAEMovable.push_front(rotator);
  fticket->setINACTIVE();
  TicketToggler ftoggler(fticket);
  ieg.addHandler(zbe::ZBEK_UP, &ftoggler);
  auto lticket = tflLAEMovable.push_front(rotator);
  lticket->setINACTIVE();
  TicketToggler ltoggler(lticket);
  ieg.addHandler(zbe::ZBEK_LEFT, &ltoggler);
  auto rticket = tflRAEMovable.push_front(rotator);
  rticket->setINACTIVE();
  TicketToggler rtoggler(rticket);
  ieg.addHandler(zbe::ZBEK_RIGHT, &rtoggler);

  printf("Pasive enities\n");fflush(stdout);
  zbe::ListManager<std::forward_list< zbe::Actuator<zbe::VoidCollisioner<LudoReactor>, LudoReactor>*> >& lmSimpleConerActuatorsList = zbe::ListManager<std::forward_list< zbe::Actuator<zbe::VoidCollisioner<LudoReactor>, LudoReactor>*> >::getInstance();
  printf("Creating the bricks\n");fflush(stdout);

  printf("Creating the board and giving it a size\n");fflush(stdout);
  std::forward_list< zbe::Actuator<zbe::VoidCollisioner<LudoReactor>, LudoReactor>*> boardActuatorsList;
  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, &boardActuatorsList);
  std::shared_ptr<LudoBoard<LudoReactor> > board = std::make_shared<LudoBoard<LudoReactor> >(50, 50, WIDTH - 50, HEIGHT - 50, BOARDACTUATORLIST);
  collisionablesList.push_front(board);
  std::shared_ptr<LudoBoard<LudoReactor> > board2 = std::make_shared<LudoBoard<LudoReactor> >(0, 0, WIDTH , HEIGHT , BOARDACTUATORLIST);
  collisionablesList.push_front(board2);

  printf("|=================== Starting up system ===================|\n");fflush(stdout);
  printf("Starting SysTimer\n");fflush(stdout);
  sysTimer->start();
  printf("Acquiring sdl info for the first time\n");fflush(stdout);
  printf("Input data will be stored into the InputReader\n");fflush(stdout);
  sdlEventDist.run();
  printf("Updating system time.\n");fflush(stdout);
  sysTime.update();
  printf("|=================== adding some timers ===================|\n");fflush(stdout);
  std::shared_ptr<zbe::Daemon> leftRotator(new  zbe::BehaviorDaemon<zbe::Movable<2>, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > >(std::make_shared<Rotator>(-0.1f), LROTATORS));
  std::shared_ptr<zbe::TimeHandler> rotatorL = std::make_shared<DemonRecurrentTimeHandler>(leftRotator, teg, zbe::SECOND/8);
  teg.addTimer(rotatorL, zbe::SECOND);

  std::shared_ptr<zbe::Daemon> rightRotator(new  zbe::BehaviorDaemon<zbe::Movable<2>, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > >(std::make_shared<Rotator>(0.1f), RROTATORS));
  std::shared_ptr<zbe::TimeHandler> rotatorR = std::make_shared<DemonRecurrentTimeHandler>(rightRotator, teg, zbe::SECOND/8);
  teg.addTimer(rotatorR, zbe::SECOND);

  std::shared_ptr<zbe::Daemon> ballParticles(new  zbe::BehaviorDaemon<zbe::Movable<2>, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > >(std::make_shared<BackBallParticlesLauncher>(8, ballgraphics[4], RSPRITELIST, &teg), MOVABLELIST));
  std::shared_ptr<zbe::TimeHandler> expeller = std::make_shared<DemonRecurrentTimeHandler>(ballParticles, teg, zbe::SECOND/16);
  teg.addTimer(expeller, zbe::SECOND/16);
  printf("|==========================================================|\n");fflush(stdout);

  bool keep = true;
  while(keep){
    //Pre
    window.clear();
    sdlEventDist.run();
    sysTime.update();
    // Inner loop
    while (sysTime.isFrameRemaining()) {
      /* Generating events
       */
      gema.generate();
      sysTime.setPartialFrameTime(store.getTime());
      if (sysTime.isPartialFrame()) {
        commonBehaviorMaster.run();
        store.manageCurrent();
        reactBehaviorMaster.run();
      } else {
        commonBehaviorMaster.run();
        store.clearStore();
      }
    }
    //Post
    drawMaster.run();
    int errcount = zbe::SysError::getNErrors();
    if(errcount>0){
        printf("Error: %s",zbe::SysError::getFirstErrorString().c_str());fflush(stdout);
    }
    window.present();
  }

  return 0;
}

} //namespace Ludo
