//#include <cinttypes>
//#include <iostream>
//#include <chrono>
//#include <thread>
//#include <cstdlib>
//#include <SDL3_ttf/SDL_ttf.h>
//
//#include "ZBE/core/daemons/Daemon.h"
//#include "ZBE/core/daemons/DaemonMaster.h"
//
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
//#include "ZBE/core/events/generators/CollisionEventGenerator.h"
//#include "ZBE/core/events/generators/TimeEventGenerator.h"
//#include "ZBE/core/events/handlers/Actuator.h"
//#include "ZBE/core/system/SysTime.h"
//#include "ZBE/core/tools/Timer.h"
//#include "ZBE/core/system/SysError.h"
//#include "ZBE/core/daemons/Punishers.h"
//#include "ZBE/SDL/tools/SDLTimer.h"
//#include "ZBE/SDL/system/SDLEventDispatcher.h"
//#include "ZBE/SDL/system/Window.h"
//#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"
//#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"
//#include "ZBE/entities/adaptors/SimpleDrawableSingleSpriteAdaptor.h"
//#include "ZBE/behaviors/UniformLinearMotion.h"
//#include "ZBE/behaviors/Bounce.h"
//#include "ZBE/archetypes/Mobile.h"
//#include "ZBE/archetypes/MobileAPO.h"
//
//#include "gamemain.h"
//#include "game/GameReactor.h"
//#include "game/entities/GameBall.h"
//#include "game/entities/GameBlock.h"
//#include "batis/entities/GameBoard.h"
//#include "batis/entities/Sign.h"
//#include "game/entities/adaptors/GameBallCollisionatorAdaptor.h"
//#include "game/entities/adaptors/GameBlockCollisionerAdaptor.h"
//#include "ZBE/entities/adaptors/TextDrawableSingleTextSpriteAdaptor.h"
//#include "ZBE/entities/avatars/SingleTextSprite.h"
//#include "game/events/handlers/StepInputHandler.h"
//#include "game/events/handlers/ExitInputHandler.h"
//#include "game/events/handlers/GameBallBouncer.h"
//#include "batis/events/handlers/MKBallInputHandler.h"
//#include "batis/events/handlers/MouseXKeepInputHandler.h"
//#include "batis/events/handlers/MouseYKeepInputHandler.h"
//#include "game/events/handlers/ExitInputHandler.h"
//#include "batis/events/handlers/TtpHandler.h"
//
//#include "ZBE/core/system/MainLoop.h"
//#include "ZBE/core/daemons/BasicPreLoopTimeDaemon.h"
//#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"
//#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
//
//#define PI 3.14159265
//
int batismain(int, char** ) {
//
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
//    TEXTSPRITELIST = 2,
//
//    WIDTH = 1024,
//    HEIGHT = 768
//  };
//
//  const char ballfilename[] = "data/images/zombieball/zomball_st_32.png";
//  const char brickfilename[] = "data/images/zombieball/braikn_32.png";
//  const char fontFileName[] = "data/fonts/PublicEnemyNF.ttf";
//
//  uint64_t ballgraphics;
//  uint64_t brickgraphics;
//  uint64_t signfont;
//
//  SDL_Color lejia;
//  lejia.r = 255;
//  lejia.g = 128;
//  lejia.b = 0;
//  lejia.a = 255;
//
//  printf("3 / 5 %d\n", 3/5);fflush(stdout);
//  printf("2 / 5 %d\n", 2/5);fflush(stdout);
//
//  printf("|=================== Building up system ===================|\n");fflush(stdout);
//  printf("TTF INIT\n");fflush(stdout);
//  if (TTF_Init() < 0) {
//    printf("Cannot TTF INIT\n");
//  }
//  printf("Event store\n");fflush(stdout);
//  printf("Will store all event independently of its type\n");fflush(stdout);
//  zbe::EventStore& store = zbe::EventStore::getInstance();
//  printf("Building generator master\n");fflush(stdout);
//  std::shared_ptr<zbe::DaemonMaster> gema(new zbe::DaemonMaster());
//  printf("|------------------------ Input Event Generator-------------|\n");fflush(stdout);
//  printf("Building SDLEventDispatcher\n");fflush(stdout);
//  printf("Will extract data from SDL and get it usable for the engine\n");fflush(stdout);
//  zbe::SDLEventDispatcher & sdlEventDist = zbe::SDLEventDispatcher::getInstance();
//  printf("Acquiring InputBuffer\n");fflush(stdout);
//  printf("SDLEventDispatcher Will store input changes for a frame into it\n");fflush(stdout);
//  zbe::InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
//  printf("Acquiring and configuring InputEventGenerator with that InputReader\n");fflush(stdout);
//  printf("Will read events from the InputReader and send them to the store\n");fflush(stdout);
//  printf("Input events will use id 0\n");fflush(stdout);
//  std::shared_ptr<zbe::InputEventGenerator> ieg(new zbe::InputEventGenerator(inputBuffer,INPUTEVENT));
//  gema->addDaemon(ieg);
//  printf("|------------------- Collision Event Generator-------------|\n");fflush(stdout);
//  printf("Building list for collisionator entinties. Currently empty.\n");fflush(stdout);
//  printf("It will store entities that will search for a collision.\n");fflush(stdout);
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<game::GameReactor> > > ctl;
//  printf("Acquiring singleton list-manager for this list (ctl).\n");fflush(stdout);
//  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<game::GameReactor> > > >& lmct = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<game::GameReactor> > > >::getInstance();
//  printf("Storing ctl in that list-manager.\n");fflush(stdout);
//  lmct.insert(COLLISIONATORLIST, &ctl);
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
//  zbe::Window window(WIDTH,HEIGHT);
//  printf("Creating draw master list\n");fflush(stdout);
//  std::shared_ptr<zbe::DaemonMaster> drawMaster(new zbe::DaemonMaster());
//  printf("Creating drawables list\n");fflush(stdout);
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite> > sprites;
//  zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite > > >& lmAESingleSprite = zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite> > >::getInstance();
//  lmAESingleSprite.insert(SPRITELIST, &sprites);
//
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleTextSprite> > textSprites;
//  zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleTextSprite > > >& lmAESingleTextSprite = zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleTextSprite> > >::getInstance();
//  lmAESingleTextSprite.insert(TEXTSPRITELIST, &textSprites);
//
//  printf("Loading imgs\n");fflush(stdout);
//
//  ballgraphics = window.loadImg(ballfilename);
//  brickgraphics = window.loadImg(brickfilename);
//  signfont = window.loadFont(fontFileName, 20, lejia);
//
//  printf("Building the drawer to paint SingleSprite's \n");fflush(stdout);
//  std::shared_ptr<zbe::Daemon> drawerDaemon(new  zbe::DrawerDaemon<zbe::SingleSprite, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite> > >(std::make_shared<zbe::SingleSpriteSDLDrawer>(&window), SPRITELIST));
//  drawMaster->addDaemon(drawerDaemon);
//
//  std::shared_ptr<zbe::Daemon> textDrawerDaemon(new  zbe::DrawerDaemon<zbe::SingleTextSprite, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleTextSprite> > >(std::make_shared<zbe::SingleTextSDLDrawer>(&window), TEXTSPRITELIST));
//  drawMaster->addDaemon(textDrawerDaemon);
//  printf("|-------------------- Daemons ----------------------|\n");fflush(stdout);
//  std::shared_ptr<zbe::DaemonMaster> commonBehaviorMaster(new zbe::DaemonMaster());
//  std::shared_ptr<zbe::DaemonMaster> reactBehaviorMaster(new zbe::DaemonMaster());
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > vAEMovable;
//  auto& lmAEMovable = zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > >::getInstance();
//  lmAEMovable.insert(MOVABLELIST, &vAEMovable);
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Bouncer<2> > > vAEBouncer;
//  auto& lmAEBouncer = zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Bouncer<2> > > >::getInstance();
//  lmAEBouncer.insert(BOUNCERLIST, &vAEBouncer);
//  std::shared_ptr<zbe::Daemon> ballBounce(new  zbe::BehaviorDaemon<zbe::Bouncer<2>, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Bouncer<2> > > >(std::make_shared<zbe::Bounce<2> >(), BOUNCERLIST));
//  std::shared_ptr<zbe::Daemon> ballULM(new  zbe::BehaviorDaemon<zbe::Movable<2>, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Movable<2> > > >(std::make_shared<zbe::UniformLinearMotion<2> >(), MOVABLELIST));
//  commonBehaviorMaster->addDaemon(ballULM);
//  reactBehaviorMaster->addDaemon(ballBounce);
//  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
//
//  printf("Creating the board and giving it a size\n");fflush(stdout);
//  //board
//  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<game::GameReactor> > > collisionablesList;
//  zbe::RsrcStore< std::forward_list<zbe::ActuatorWrapper<game::GameReactor, void>*> >& lmSimpleConerActuatorsList = zbe::RsrcStore< std::forward_list< zbe::ActuatorWrapper<game::GameReactor, void>*> >::getInstance();
//  std::forward_list<zbe::ActuatorWrapper<game::GameReactor, void>*> boardActuatorsList;
//  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, &boardActuatorsList);
//  batis::Board boardCfg;
//
//  boardCfg.margin = 2;
//  boardCfg.space = 9;
//  boardCfg.brickWidth = 51;
//  boardCfg.brickHeight = 32;
//  boardCfg.brickAreaWidth = WIDTH;
//  boardCfg.brickAreaHeight = HEIGHT*2/3;
//  boardCfg.cols = (boardCfg.brickAreaWidth - boardCfg.margin - boardCfg.margin) / (boardCfg.brickWidth + boardCfg.space);
//  boardCfg.rows = (boardCfg.brickAreaHeight - boardCfg.margin - boardCfg.margin) / (boardCfg.brickHeight + boardCfg.space);
//  boardCfg.margin += (boardCfg.brickAreaWidth - ((boardCfg.margin * 2) + (boardCfg.cols*(boardCfg.brickWidth + boardCfg.space)) - boardCfg.space))/2;
//
//  std::shared_ptr<batis::GameBoard> board = std::make_shared<batis::GameBoard>(0, 0, WIDTH, HEIGHT, BOARDACTUATORLIST, boardCfg);
//  collisionablesList.push_front(board);
//
//  printf("Creating a ball and giving it a position and size\n");fflush(stdout);
//  //ball
//  std::forward_list< zbe::ActuatorWrapper<game::GameReactor , zbe::Bouncer<2>>*> ballActuatorsList;
//  zbe::RsrcStore< std::forward_list< zbe::ActuatorWrapper<game::GameReactor, zbe::Bouncer<2> >* > >& lmBallActuatorsList = zbe::RsrcStore< std::forward_list< zbe::ActuatorWrapper<game::GameReactor, zbe::Bouncer<2> >* > >::getInstance();
//  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
//  zbe::ActuatorWrapper<game::GameReactor, zbe::Bouncer<2> >* bouncerWrapper = new  zbe::ActuatorWrapperCommon<game::GameReactor, zbe::Bouncer<2>, zbe::Bouncer<2> >(new game::GameBallBouncer());
//  ballActuatorsList.push_front(bouncerWrapper);
//
//  zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<game::GameReactor> > > >& lmCollisionablesList = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactioner<game::GameReactor> > > >::getInstance();
//  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);
//
//  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
//  game::ExitInputHandler terminator;
//  ieg->addHandler(zbe::ZBEK_ESCAPE, &terminator);
//  ieg->addHandler(zbe::ZBEK_RETURN, &terminator);
//
//  batis::MouseXKeepInputHandler xKeep;
//  batis::MouseYKeepInputHandler yKeep;
//  ieg->addHandler(zbe::ZBEK_MOUSE_OFFSET_X, &xKeep);
//  ieg->addHandler(zbe::ZBEK_MOUSE_OFFSET_Y, &yKeep);
//
//  batis::MKBallInputHandler ballMaker;
//  ieg->addHandler(zbe::ZBEK_MOUSE_LEFT, &ballMaker);
//
//  for(int i = 0; i<100 ; i++){//98.623993, 85.728439
//    int64_t vt = 200;
//
//    int minAngle = 0;
//    int maxAngle = 360;
//
//    double vAngleL = (minAngle * 10) + rand()%((maxAngle-minAngle)*10);
//    vAngleL/=10;
//    double vAngleR = rand()%10000;
//    vAngleR/=100000;
//    double vAngle = vAngleL + vAngleR;
//    int64_t vx = sin(vAngle*PI/180)*vt;
//    int64_t vy = cos(vAngle*PI/180)*vt;
//
//    std::shared_ptr<game::GameBall> ball = std::make_shared<game::GameBall>(WIDTH/2, HEIGHT/2, 16 , vx, vy, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
//    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(&(*ball));
//    zbe::setAdaptor(ball,spriteAdaptor);
//
//    std::shared_ptr<zbe::Adaptor<zbe::Interactionator<game::GameReactor> > > gbca = std::make_shared<game::GameBallCollisionatorAdaptor>(&(*ball));
//    zbe::setAdaptor(ball,gbca);
//
//    ctl.push_front(ball);
//    vAEMovable.push_front(ball);
//    vAEBouncer.push_front(ball);
//    sprites.push_front(ball);
//  }
//
//  printf("Creating the bricks\n");fflush(stdout);
//  //bricks
//  std::forward_list<zbe::ActuatorWrapper<game::GameReactor, void>*> brickActuatorsList;
//  lmSimpleConerActuatorsList.insert(BRICKACTUATORLIST, &brickActuatorsList);
//
//  int brickProb = 30;
//
//  for (int i = 0; i < boardCfg.cols; i++){
//    for (int j = 0; j < boardCfg.rows; j++){
//      if (rand()%100 < brickProb) {
//        std::shared_ptr<game::GameBlock> brick = std::make_shared<game::GameBlock>(boardCfg.margin + ((boardCfg.space+boardCfg.brickWidth)*i),
//                    boardCfg.margin + ((boardCfg.space+boardCfg.brickHeight)*j), boardCfg.brickWidth, boardCfg.brickHeight,
//                    brickgraphics, BRICKACTUATORLIST);
//
//        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(&(*brick));
//        zbe::setAdaptor(brick, spriteAdaptor);
//
//        std::shared_ptr<zbe::Adaptor<zbe::Interactioner<game::GameReactor> > >gBrCA = std::make_shared<game::GameBlockCollisionerAdaptor>(&(*brick));
//        zbe::setAdaptor(brick, gBrCA);
//
//        collisionablesList.push_front(brick);
//        sprites.push_front(brick);
//        std::shared_ptr<zbe::TimeHandler> teleporter = std::make_shared<batis::TtpHandler>(brick, teg, board);
//
//        teg->addTimer(teleporter, zbe::SECOND);
//      }
//    }
//  }
//
//  printf("Creating a sign\n");
//
//  std::shared_ptr<batis::Sign> sign = std::make_shared<batis::Sign>(0, 0, 200, 20, signfont,"Esto funciona");
//  std::shared_ptr<zbe::Adaptor<zbe::SingleTextSprite> > textSpriteAdaptor = std::make_shared<zbe::TextDrawableSingleTextSpriteAdaptor>(&(*sign));
//  zbe::setAdaptor(sign, textSpriteAdaptor);
//  textSprites.push_front(sign);
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
//  printf("|=================== Starting the game loop ===================|\n");fflush(stdout);
//
////  std::shared_ptr<zbe::Daemon> prltd = std::make_shared<zbe::BasicPreLoopTimeDaemon>();
////  std::shared_ptr<zbe::Daemon> prlsdl = std::make_shared<zbe::BasicPreLoopSDLDaemon>(&window);
////  std::shared_ptr<zbe::Daemon> postLoop = std::make_shared<zbe::BasicPostLoopSDLDaemon>(&window);
////  std::shared_ptr<zbe::DaemonMaster> preLoop(new zbe::DaemonMaster());
////
////  preLoop->addDaemon(prlsdl);
////  preLoop->addDaemon(prltd);
////
////  zbe::MainLoop mainLoop(preLoop, postLoop, gema, commonBehaviorMaster, reactBehaviorMaster, drawMaster);
//  //mainLoop.loop();
//
//
//  bool keep = true;
//  while(keep){
//    //Pre
//    window.clear();
//    sdlEventDist.run();
//    sysTime.update();
//    // Inner loop
//    while (sysTime.isFrameRemaining()) {
//      // Generating events
//      gema->run();
//      sysTime.setEventTime(store.getTime());
//      if (sysTime.isPartialFrame()) {
//        commonBehaviorMaster->run();
//        store.manageCurrent();
//        reactBehaviorMaster->run();
//      } else {
//        commonBehaviorMaster->run();
//        store.clearStore();
//      }
//      sysTime.updateInitTime();
//    }
//    //Post
//    drawMaster->run();
//    int errcount = zbe::SysError::getNErrors();
//    if(errcount>0){
//        printf("Error: %s",zbe::SysError::getFirstErrorString().c_str());fflush(stdout);
//    }
//    window.present();
//  }
//
///*
//  bool keep = true;
//  while(keep){
//    //Pre daemon
//    window.clear();
//    sdlEventDist.run();
//    sysTime.update();
//    // Inner loop
//    while (sysTime.isFrameRemaining()) {
//      // Timed events daemon (gema)
//      gema->run();
//      sysTime.setEventTime(store.getTime());
//      if (sysTime.isPartialFrame()) {
//        // commonBehaviorMaster
//        commonBehaviorMaster->run();
//        store.clearStore();
//        // reactBehaviorMaster
//        reactBehaviorMaster->run();
//      } else {
//        // commonBehaviorMaster
//        commonBehaviorMaster->run();
//        store.clearStore();
//      }
//      sysTime.updateInitTime();
//    }
//    //Post daemon
//    drawMaster->run();
//    postLoop->run();
//    // end
//  }*/
//
//
//
//
//
//
//
//  TTF_Quit();
  return 0;
}
