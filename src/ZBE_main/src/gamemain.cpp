//#include <cinttypes>
//#include <iostream>
//#include <chrono>
//#include <thread>
//#include <cstdlib>
//
//#include "ZBE/core/daemons/DaemonMaster.h"
//#include "ZBE/core/entities/avatars/Interactioner.h"
//#include "ZBE/core/entities/avatars/Interactionator.h"
//#include "ZBE/core/entities/avatars/Interactioner.h"
//#include "ZBE/core/events/Event.h"
//#include "ZBE/core/events/EventStore.h"
//#include "ZBE/core/events/TimeEvent.h"
//#include "ZBE/core/events/InputEvent.h"
//#include "ZBE/core/events/InteractionEvent.h"
//#include "ZBE/core/events/generators/util/CollisionSelector.h"
//#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"
//#include "ZBE/core/events/generators/InputEventGenerator.h"
////#include "ZBE/core/events/generators/CollisionEventGenerator.h"
//#include "ZBE/core/events/generators/TimeEventGenerator.h"
//#include "ZBE/core/events/handlers/Actuator.h"
//#include "ZBE/core/system/SysTime.h"
//#include "ZBE/core/tools/time/Timer.h"
//#include "ZBE/core/system/SysError.h"
//#include "ZBE/core/daemons/Punishers.h"
//#include "ZBE/SDL/tools/SDLTimer.h"
//#include "ZBE/SDL/events/SDLEventDispatcher.h"
//#include "ZBE/SDL/system/SDLWindow.h"
//#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"
//#include "ZBE/entities/adaptors/SimpleDrawableSingleSpriteAdaptor.h"
//#include "ZBE/behaviors/UniformLinearMotion.h"
//#include "ZBE/behaviors/Bounce.h"
//#include "ZBE/archetypes/Mobile.h"
//#include "ZBE/archetypes/MobileAPO.h"
//
#include "gamemain.h"
//#include "game/GameReactor.h"
//#include "game/entities/GameBall.h"
//#include "game/entities/GameBoard.h"
//#include "game/entities/GameBlock.h"
//#include "game/entities/adaptors/GameBallCollisionatorAdaptor.h"
//#include "game/entities/adaptors/GameBlockCollisionerAdaptor.h"
//#include "game/events/handlers/StepInputHandler.h"
//#include "game/events/handlers/ExitInputHandler.h"
//#include "game/events/handlers/GameBallBouncer.h"
////#include "game/events/handlers/TtpHandler.h" // header not working
//
//#include "ZBE/core/daemons/MainLoop.h"
//#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"
//#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"

int gamemain(int, char** ) {

//  printf("--- GAME main ---\n\n");
//
//  enum {
//    GENERATORLIST = 1,
//
//    INPUTEVENT = 0,
//    COLLISIONEVENT = 1,
//    TIMEEVENT = 2,
//
//    COLLISIONATORLIST = 1,
//    MOVABLELIST = 1,
//    BOUNCERLIST = MOVABLELIST,
//    BALLACTUATORLIST = 1,
//    COLLISIONABLELIST = 1,
//    BOARDACTUATORLIST = 1,
//    BRICKACTUATORLIST = 2,
//    SPRITELIST = 1,
//
//    WIDTH = 1024,
//    HEIGHT = 768
//  };
//
//  const char ballfilename[] = "data/images/zombieball/zomball_st_32.png";
//  const char brickfilename[] = "data/images/zombieball/braikn_32.png";
//  uint64_t ballgraphics;
//  uint64_t brickgraphics;
//
//  printf("3 / 5 %d\n", 3/5);fflush(stdout);
//  printf("2 / 5 %d\n", 2/5);fflush(stdout);
//
//  printf("|=================== Building up system ===================|\n");fflush(stdout);
//
//  printf("Building generator master\n");fflush(stdout);
//  std::shared_ptr<zbe::DaemonMaster> gema(new zbe::DaemonMaster());
//  printf("|------------------------ Input Event Generator-------------|\n");fflush(stdout);
//  printf("Building SDLEventDispatcher\n");fflush(stdout);
//  printf("Will extract data from SDL and get it usable for the engine\n");fflush(stdout);
//  zbe::SDLEventDispatcher & sdlEventDist = zbe::SDLEventDispatcher::getInstance();
//  printf("Acquiring InputBuffer\n");fflush(stdout);
//  printf("SDLEventDispatcher Will store input changes for a frame into it\n");fflush(stdout);
//  std::shared_ptr<zbe::InputBuffer> inputBuffer = sdlEventDist.getInputBuffer();
//  printf("Acquiring and configuring InputEventGenerator with that InputReader\n");fflush(stdout);
//  printf("Will read events from the InputReader and send them to the store\n");fflush(stdout);
//  printf("Input events will use id 0\n");fflush(stdout);
//  std::shared_ptr<zbe::InputEventGenerator> ieg(new zbe::InputEventGenerator(inputBuffer,INPUTEVENT));
//  gema->addDaemon(ieg);
//  printf("|------------------- Collision Event Generator-------------|\n");fflush(stdout);
//  printf("Building list for collisionator entinties. Currently empty.\n");fflush(stdout);
//  printf("It will store entities that will search for a collision.\n");fflush(stdout);
//  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<game::GameReactor> > > > ctl(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<game::GameReactor> > >());
//  //zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<game::GameReactor> > > ctl;
//  printf("Acquiring singleton list-manager for this list (ctl).\n");fflush(stdout);
//  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<game::GameReactor> > > >& lmct = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<game::GameReactor> > > >::getInstance();
//  printf("Storing ctl in that list-manager.\n");fflush(stdout);
//  lmct.insert(COLLISIONATORLIST, ctl);
//  printf("Building collision event generator with list id and the event id to use (1).\n");fflush(stdout);
//  std::shared_ptr<zbe::CollisionEventGenerator<game::GameReactor> > ceg(new zbe::CollisionEventGenerator<game::GameReactor>(COLLISIONATORLIST, COLLISIONEVENT, new zbe::BaseCollisionSelector<game::GameReactor>()));
//  gema->addDaemon(ceg);
//  printf("|------------------- Time Event Generator -----------------|\n");fflush(stdout);
//  printf("Building time event generator with the event id to use (2)\n");fflush(stdout);
//  std::shared_ptr<zbe::TimeEventGenerator> teg(new zbe::TimeEventGenerator(TIMEEVENT));
//  gema->addDaemon(teg);
//  printf("|------------------------- Time ---------------------------|\n");fflush(stdout);
//  printf("Building a SDL implementation of Timer\n");fflush(stdout);
//  zbe::Timer *sysTimer = new zbe::SDLTimer(true);
//  printf("Acquiring and configuring SysTime with that Timer\n");fflush(stdout);
//  printf("It will be the time reference for all the game context\n");fflush(stdout);
//  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
//  sysTime.setSystemTimer(sysTimer);
//  printf("|-------------------- Drawing system ----------------------|\n");fflush(stdout);
//  printf("Building the window to draw on\n");fflush(stdout);
//  std::shared_ptr<zbe::SDLWindow> window = std::make_shared<zbe::SDLWindow>("Game Main", WIDTH,HEIGHT);
//  zbe::SDLImageStore imgStore(window->getRenderer());
//  printf("Creating draw master list\n");fflush(stdout);
//  std::shared_ptr<zbe::DaemonMaster> drawMaster(new zbe::DaemonMaster());
//  printf("Creating drawables list\n");fflush(stdout);
//  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::SingleSprite> > > sprites(new zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::SingleSprite> >());
//  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::SingleSprite > > >& lmAESimpleSprite = zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::SingleSprite > > >::getInstance();
//  lmAESimpleSprite.insert(SPRITELIST, sprites);
//  printf("Loading imgs\n");fflush(stdout);
//  ballgraphics = imgStore.loadImg(ballfilename);
//  brickgraphics = imgStore.loadImg(brickfilename);
//  printf("Building the drawer to paint SingleSprite's \n");fflush(stdout);
//  std::shared_ptr<zbe::Daemon> drawerDaemon(new  zbe::BehaviorDaemon<zbe::SingleSprite, zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::SingleSprite > > >(std::make_shared<zbe::SingleSpriteSDLDrawer>(window, &imgStore), SPRITELIST));
//  drawMaster->addDaemon(drawerDaemon);
//  printf("|-------------------- Daemons ----------------------|\n");fflush(stdout);
//  std::shared_ptr<zbe::DaemonMaster> commonBehaviorMaster(new zbe::DaemonMaster());
//  std::shared_ptr<zbe::DaemonMaster> reactBehaviorMaster(new zbe::DaemonMaster());
//  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::Movable<2> > > > vAEMovable(new zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::Movable<2> > >());
//  auto& lmAEMovable = zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::Movable<2> > > >::getInstance();
//  lmAEMovable.insert(MOVABLELIST, vAEMovable);
//  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::Bouncer<2> > > > vAEBouncer(new zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::Bouncer<2> > >());
//  auto& lmAEBouncer = zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::Bouncer<2> > > >::getInstance();
//  lmAEBouncer.insert(BOUNCERLIST, vAEBouncer);
//  std::shared_ptr<zbe::Daemon> ballBounce(new  zbe::BehaviorDaemon<zbe::Bouncer<2>, zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::Bouncer<2> > > >(std::make_shared<zbe::Bounce<2> >(), BOUNCERLIST));
//  std::shared_ptr<zbe::Daemon> ballULM(new  zbe::BehaviorDaemon<zbe::Movable<2>, zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::Movable<2> > > >(std::make_shared<zbe::UniformLinearMotion<2> >(), MOVABLELIST));
//  commonBehaviorMaster->addDaemon(ballULM);
//  reactBehaviorMaster->addDaemon(ballBounce);
//  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
//  printf("Creating a ball and giving it a position and size\n");fflush(stdout);
//
//  //ball
//  std::shared_ptr<std::forward_list< zbe::ActuatorWrapper<game::GameReactor , zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> > >*> > ballActuatorsList(new std::forward_list< zbe::ActuatorWrapper<game::GameReactor , zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> > >*>());
//  zbe::RsrcStore< std::forward_list< zbe::ActuatorWrapper<game::GameReactor, zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> > >* > >& lmBallActuatorsList = zbe::RsrcStore< std::forward_list< zbe::ActuatorWrapper<game::GameReactor, zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> > >* > >::getInstance();
//  lmBallActuatorsList.insert(BALLACTUATORLIST, ballActuatorsList);
//  zbe::ActuatorWrapper<game::GameReactor, zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> > >* bouncerWrapper = new  zbe::ActuatorWrapperCommon<game::GameReactor, zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> >, zbe::WeakAvatarEntityContainer<zbe::Bouncer<2> > >(new game::GameBallBouncer());
//  ballActuatorsList->push_front(bouncerWrapper);
//
//  std::shared_ptr<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<game::GameReactor> > > > collisionablesList(new zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<game::GameReactor> > >());
//  zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<game::GameReactor> > > >& lmCollisionablesList = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<game::GameReactor> > > >::getInstance();
//  lmCollisionablesList.insert(COLLISIONABLELIST, collisionablesList);
//
//  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
//  game::ExitInputHandler terminator;
//  ieg->addHandler(zbe::ZBEK_ESCAPE, &terminator);
//
//  std::shared_ptr<zbe::AvatarEntityContainer<zbe::SingleSprite> > aecss;
//
//  for(int i = 0; i<1000 ; i++){//98.623993, 85.728439
//    std::shared_ptr<game::GameBall> ball = std::make_shared<game::GameBall>((rand()%200 + 400), (rand()%200 + 400), 16 , (rand()%2000 - 1000), (rand()%2000 - 100), BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
//    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(ball);
//    zbe::setAdaptor(ball,spriteAdaptor);
//    std::shared_ptr<zbe::Adaptor<zbe::Interactionator<game::GameReactor> > > gbca = std::make_shared<game::GameBallCollisionatorAdaptor>(ball);
//    zbe::setAdaptor(ball,gbca);
//
//    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2> > > aecm2;
//    std::shared_ptr<zbe::AvatarEntityContainer<zbe::Bouncer<2> > > aecb2;
//
//    zbe::wrapAEC(&aecm2, ball);
//    zbe::wrapAEC(&aecb2, ball);
//    zbe::wrapAEC(&aecss, ball);
//
//    ctl->push_front(ball);
//    vAEMovable->push_front(aecm2);
//    vAEBouncer->push_front(aecb2);
//    sprites->push_front(aecss);
//  }
//
//  printf("Creating the bricks\n");fflush(stdout);
//  //bricks
//  zbe::RsrcStore< std::forward_list<zbe::ActuatorWrapper<game::GameReactor, void>*> >& lmSimpleConerActuatorsList = zbe::RsrcStore< std::forward_list< zbe::ActuatorWrapper<game::GameReactor, void>*> >::getInstance();
//  std::shared_ptr<std::forward_list<zbe::ActuatorWrapper<game::GameReactor, void>*> > brickActuatorsList(new std::forward_list<zbe::ActuatorWrapper<game::GameReactor, void>*>());
//  lmSimpleConerActuatorsList.insert(BRICKACTUATORLIST, brickActuatorsList);
////  for(int i = 0; i<8 ; i++){
////      for(int j = 0; j<8 ; j++){
//          std::shared_ptr<game::GameBlock> brick = std::make_shared<game::GameBlock>(100, 100, 51, 32, brickgraphics, BRICKACTUATORLIST);
//
//          std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(brick);
//          zbe::setAdaptor(brick, spriteAdaptor);
//
//          std::shared_ptr<zbe::Adaptor<zbe::Interactioner<game::GameReactor> > >gBrCA = std::make_shared<game::GameBlockCollisionerAdaptor>(brick);
//          zbe::setAdaptor(brick, gBrCA);
//
//          zbe::wrapAEC(&aecss, brick);
//
//          collisionablesList->push_front(brick);
//          sprites->push_front(aecss);
//          std::shared_ptr<zbe::TimeHandler> teleporter = std::make_shared<game::TtpHandler>(brick, teg);
//          teg->addTimer(teleporter, zbe::SECOND*2);
////      }
////  }
//
//  printf("Creating the board and giving it a size\n");fflush(stdout);
//  //board
//  std::shared_ptr<std::forward_list<zbe::ActuatorWrapper<game::GameReactor, void>*> > boardActuatorsList(new std::forward_list<zbe::ActuatorWrapper<game::GameReactor, void>*>());
//  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, boardActuatorsList);
//  std::shared_ptr<game::GameBoard> board = std::make_shared<game::GameBoard>(0, 0, WIDTH, HEIGHT, BOARDACTUATORLIST);
//  collisionablesList->push_front(board);
//
//  printf("|=================== Starting up system ===================|\n");fflush(stdout);
//  printf("Starting SysTimer\n");fflush(stdout);
//  sysTimer->start();
//  printf("Acquiring sdl info for the first time\n");fflush(stdout);
//  printf("Input data will be stored into the InputReader\n");fflush(stdout);
//  sdlEventDist.run();
//  printf("Updating system time.\n");fflush(stdout);
//  sysTime.update();
//
//  std::shared_ptr<zbe::Daemon> prltd = std::make_shared<zbe::BasicPreLoopTimeDaemon>();
//  std::shared_ptr<zbe::Daemon> prlsdl = std::make_shared<zbe::BasicPreLoopSDLDaemon>(window);
//  std::shared_ptr<zbe::Daemon> postLoop = std::make_shared<zbe::BasicPostLoopSDLDaemon>(window);
//  std::shared_ptr<zbe::DaemonMaster> preLoop(new zbe::DaemonMaster());
//
//  preLoop->addDaemon(prlsdl);
//  preLoop->addDaemon(prltd);
//
//  zbe::MainLoop mainLoop(preLoop, postLoop, gema, commonBehaviorMaster, reactBehaviorMaster, drawMaster);
//  mainLoop.run();
//
  return 0;
}
