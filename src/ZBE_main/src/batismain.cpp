//#include <cinttypes>
//#include <iostream>
//#include <chrono>
//#include <thread>
//#include <cstdlib>
//
//#include "ZBE/core/daemons/DaemonMaster.h"
//#include "ZBE/core/entities/avatars/implementations/SimpleCollisioner.h"
//#include "ZBE/core/events/Event.h"
//#include "ZBE/core/events/EventStore.h"
//#include "ZBE/core/events/TimeEvent.h"
//#include "ZBE/core/events/InputEvent.h"
//#include "ZBE/core/events/CollisionEvent2D.h"
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
//#include "ZBE/SDL/drawers/SimpleSpriteSDLDrawer.h"
//#include "ZBE/entities/adaptors/SimpleDrawableSimpleSpriteAdaptor.h"
//#include "ZBE/behaviors/UniformLinearMotion.h"
//#include "ZBE/archetypes/Mobile.h"
//#include "ZBE/archetypes/MobileAPO.h"
//
//#include "gamemain.h"
//#include "game/GameReactor.h"
//#include "batis/entities/GameBall.h"
//#include "game/entities/GameBoard.h"
//#include "game/entities/GameBlock.h"
//#include "game/events/handlers/StepInputHandler.h"
//#include "batis/events/handlers/MKBallInputHandler.h"
//#include "batis/events/handlers/MouseXKeepInputHandler.h"
//#include "batis/events/handlers/MouseYKeepInputHandler.h"
//#include "game/events/handlers/ExitInputHandler.h"
//#include "game/events/handlers/GameBallBouncer.h"
//
//#define PI 3.14159265



//  printf("--- GAME main ---\n\n");
//
//  enum {
//    INPUTEVENT = 0,
//    COLLISIONEVENT = 1,
//    TIMEEVENT = 2,
//
//    COLLISIONATORLIST = 1,
//    MOBILELIST = 1,
//    BALLACTUATORLIST = 1,
//    COLLISIONABLELIST = 1,
//    BOARDACTUATORLIST = 1,
//    BRICKACTUATORLIST = 2,
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
//  printf("Event store\n");fflush(stdout);
//  printf("Will store all event independently of its type\n");fflush(stdout);
//  zbe::EventStore& store = zbe::EventStore::getInstance();
//
//  printf("|------------------------ Input Event Generator-------------|\n");fflush(stdout);
//  printf("Building SDLEventDispatcher\n");fflush(stdout);
//  printf("Will extract data from SDL and get it usable for the engine\n");fflush(stdout);
//  zbe::SDLEventDispatcher & sdlEventDist = zbe::SDLEventDispatcher::getInstance();
//
//  printf("Acquiring InputBuffer\n");fflush(stdout);
//  printf("SDLEventDispatcher Will store input changes for a frame into it\n");fflush(stdout);
//  zbe::InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
//
//  printf("Acquiring and configuring InputEventGenerator with that InputReader\n");fflush(stdout);
//  printf("Will read events from the InputReader and send them to the store\n");fflush(stdout);
//  printf("Input events will use id 0\n");fflush(stdout);
//  zbe::InputEventGenerator ieg(inputBuffer,INPUTEVENT);
//
//  printf("|------------------- Collision Event Generator-------------|\n");fflush(stdout);
//  //zbe::TicketedForwardList<zbe::CollisionerEntity<GameReactor>*> cnl;
//  printf("Building list for collisionator entinties. Currently empty.\n");fflush(stdout);
//  printf("It will store entities that will search for a collision.\n");fflush(stdout);
//  zbe::TicketedForwardList<zbe::CollisionatorEntity<game::GameReactor>*> ctl;
//
//  printf("Acquiring singleton list-manager for this list (ctl).\n");fflush(stdout);
//  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<game::GameReactor>*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<game::GameReactor>*> >::getInstance();
//
//  printf("Storing ctl in that list-manager.\n");fflush(stdout);
//  lmct.insert(COLLISIONATORLIST, &ctl);
//
//  printf("Building collision event generator with list id and the event id to use (1).\n");fflush(stdout);
//  zbe::CollisionEventGenerator<game::GameReactor> ceg(COLLISIONATORLIST, COLLISIONEVENT);
//
//  printf("|------------------- Time Event Generator -----------------|\n");fflush(stdout);
//  printf("Building time event generator with the event id to use (2)\n");fflush(stdout);
//  zbe::TimeEventGenerator teg(TIMEEVENT);
//
//  printf("|------------------------- Time ---------------------------|\n");fflush(stdout);
//  printf("Building a SDL implementation of Timer\n");fflush(stdout);
//  zbe::Timer *sysTimer = new zbe::SDLTimer(true);
//
//  printf("Acquiring and configuring SysTime with that Timer\n");fflush(stdout);
//  printf("It will be the time reference for all the game context\n");fflush(stdout);
//  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
//  sysTime.setSystemTimer(sysTimer);
//
//  printf("|-------------------- Drawing system ----------------------|\n");fflush(stdout);
//  printf("Building the window to draw on\n");fflush(stdout);
//  zbe::Window window(WIDTH,HEIGHT);
//  ballgraphics = window.loadImg(ballfilename);
//  brickgraphics = window.loadImg(brickfilename);
//
//  printf("Building the drawer to paint SimpleSprite's \n");fflush(stdout);
//  zbe::SimpleSpriteSDLDrawer drawer(&window);
//
//  printf("|-------------------- Daemons ----------------------|\n");fflush(stdout);
//  zbe::DaemonMaster dMaster;
//  std::vector<zbe::Mobile<2>*> vmobile;
//  zbe::ListManager< std::vector<zbe::Mobile<2>*> >& lmmobile = zbe::ListManager< std::vector<zbe::Mobile<2>*> >::getInstance();
//  lmmobile.insert(MOBILELIST, &vmobile);
//  std::shared_ptr<zbe::Daemon> bball(new  zbe::BehaviorDaemon< zbe::Mobile<2>, std::vector<zbe::Mobile<2>*> >(new zbe::UniformLinearMotion<2>(), MOBILELIST));
//  dMaster.addDaemon(bball);
//
//  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
//  printf("Creating drawables list\n");fflush(stdout);
//  std::forward_list<zbe::SimpleSpriteEntity*> sprites;
//
//  game::ExitInputHandler terminator;
//  ieg.addHandler(zbe::ZBEK_ESCAPE, &terminator);
//  ieg.addHandler(zbe::ZBEK_RETURN, &terminator);
//
//  batis::MouseXKeepInputHandler xKeep;
//  batis::MouseYKeepInputHandler yKeep;
//  ieg.addHandler(zbe::ZBEK_MOUSE_OFFSET_X, &xKeep);
//  ieg.addHandler(zbe::ZBEK_MOUSE_OFFSET_Y, &yKeep);
//
//  batis::MKBallInputHandler ballMaker;
//  ieg.addHandler(zbe::ZBEK_MOUSE_LEFT, &ballMaker);
//
//  printf("Creating a ball and giving it a position and size\n");fflush(stdout);
//  srand(time(NULL));
//
//  //ball
//  std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >*> ballActuatorsList;
//  zbe::ListManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >* > >& lmBallActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >* > >::getInstance();
//  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
//  game::GameBallBouncer gbBouncer;
//  ballActuatorsList.push_front(&gbBouncer);
//
//  zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> collisionablesList;
//  zbe::ListManager<zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >& lmCollisionablesList = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >::getInstance();
//  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);
//
//  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
//  zbe::SimpleSpriteAdaptor<zbe::Drawable>* spriteAdaptor = new zbe::SimpleDrawableSimpleSpriteAdaptor();
//  zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2> * movableCatorAdaptor = new zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2>();
//
//  //zbe::ListManager<std::forward_list<batis::GameBall*>> balls;
//  std::forward_list<batis::GameBall*> balls;
//
//  for(int i = 0; i<100 ; i++){
//
//      int64_t vt = 200;
//
//      int minAngle = 0;
//      int maxAngle = 360;
//
//      double vAngleL = (minAngle * 10) + rand()%((maxAngle-minAngle)*10);
//      vAngleL/=10;
//      double vAngleR = rand()%10000;
//      vAngleR/=100000;
//      double vAngle = vAngleL + vAngleR;
//      int64_t vx = sin(vAngle*PI/180)*vt;
//      int64_t vy = cos(vAngle*PI/180)*vt;
//      //-162 -117 falla
//
//      //printf("Ball %d: %lld, %lld\n", i, vx, vy);
//
//      batis::GameBall* ball = new batis::GameBall((WIDTH/2),(HEIGHT/2), 16, vx, vy, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics, i);
//      //game::GameBall* ball = new game::GameBall(31407009,1063841, 16 << zbe::PRECISION_DIGITS, 1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
//      ctl.push_front(ball);
//      ball->setSimpleSpriteAdaptor(spriteAdaptor);
//      ball->setMovableCollisionatorAdaptor(movableCatorAdaptor);
//      vmobile.push_back(ball);
//      balls.push_front(ball);
//    	sprites.push_front(ball);
//  }
//
//  printf("Creating the bricks\n");fflush(stdout);
//  //bricks
//  zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >& lmSimpleConerActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >::getInstance();
//  std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> brickActuatorsList;
//  lmSimpleConerActuatorsList.insert(BRICKACTUATORLIST, &brickActuatorsList);
//  //GameBlock(double x, double y, double width, double height, uint64_t graphics, uint64_t actuatorsList)
//
//  std::forward_list<game::GameBlock*> bricks;
//
//  int margin = 2;
//  int space = 9;
//  int brickWidth = 51;
//  int brickHeight = 32;
//  int cols = (WIDTH - margin - margin) / (brickWidth + space);
//  int rows = 2 * (HEIGHT - margin - margin) / (3 * (brickHeight + space));
//  margin += (WIDTH - ((margin * 2) + (cols*(brickWidth + space)) - space))/2;
//  int brickProb = 30;
//
//  for (int i = 0; i < cols; i++){
//    for (int j = 0; j < rows; j++){
//      if (rand()%100 < brickProb) {
//        game::GameBlock* brick = new game::GameBlock(margin + ((space+brickWidth)*i), margin + ((space+brickHeight)*j), brickWidth, brickHeight, brickgraphics, BRICKACTUATORLIST);
//        brick->setSimpleSpriteAdaptor(spriteAdaptor);
//        collisionablesList.push_front(brick);
//        sprites.push_front(brick);
//        bricks.push_front(brick);
//      }
//    }
//  }
//
//	printf("Creating the board and giving it a size\n");fflush(stdout);
//  //board
//  std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> boardActuatorsList;
//  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, &boardActuatorsList);
//  game::GameBoard board(WIDTH, HEIGHT, BOARDACTUATORLIST);
//  collisionablesList.push_front(&board);
//
//  printf("|=================== Starting up system ===================|\n");fflush(stdout);
//  printf("Starting SysTimer\n");fflush(stdout);
//  sysTimer->start();
//  printf("Acquiring sdl info for the first time\n");fflush(stdout);
//  printf("Input data will be stored into the InputReader\n");fflush(stdout);
//  sdlEventDist.run();
//  printf("Updating system time.\n");fflush(stdout);
//  sysTime.update();
//  printf("Acquiring initial times.\n");fflush(stdout);
//  int64_t endT = sysTime.getTotalTime();// instant at which the frame ends
//  int64_t initT = 0;//Lets start
//  printf("|==========================================================|\n");fflush(stdout);
//  printf("initT = 0x%" PRIx64 " ", initT);fflush(stdout);
//  printf("endT = 0x%" PRIx64 "\n", endT);fflush(stdout);
//
//  int64_t maxFrameTime = zbe::SECOND / 32;
//  bool keep = true;
//  while(keep){
//
//    /*Finds balls inside block area.
//
//    std::forward_list<batis::GameBall*>::iterator ballIt;
//    for (ballIt = balls.begin(); ballIt != balls.end(); ballIt++){
//      if ((*ballIt)->getX()>35 && (*ballIt)->getX()<97 && (*ballIt)->getY()>35 && (*ballIt)->getY()<97) {
//          printf("Bola %d, FATALMAL: %lld, %lld\n", (*ballIt)->getId(), (*ballIt)->getX(), (*ballIt)->getY());
//      }
//    }*/
//
//
//
//    /* Clear screen.
//     */
//    window.clear();
//
//    /* Acquiring sdl info
//     * Input data will be stored into the InputReader
//     */
//    sdlEventDist.run();
//
//    /* Updating system time.
//     */
//    sysTime.update();
//
//    /* Reading that updated time info
//     */
//    initT = endT;// init time
//    endT = sysTime.getTotalTime(); //initT + (int64_t(1) << zbe::PRECISION_DIGITS); // instant at which the frame ends
//
//    if((endT - maxFrameTime)>initT){
//      initT = endT - maxFrameTime;
//    }
//
//    while (initT < endT) {
//      /* Generating input events:
//       * It will take the events that sdlEventDist has stored
//       * into the InputReader and send it to the event store.
//       */
//      ieg.generate(initT,endT);
//      teg.generate(initT,endT);
//      ceg.generate(initT,endT);
//
//      int64_t eventTime = store.getTime();
//      if (eventTime <= endT) {
//        dMaster.run(eventTime-initT);
//        store.manageCurrent();
//        initT = eventTime;
//      } else {
//        dMaster.run(endT-initT);
//        store.clearStore();
//        initT = endT;
//      }
//    }
//
//    for(auto s : sprites){
//        drawer.apply(s->getSimpleSprite().get());
//    }
//
//    /* If one or more error occurs, the ammount and the first one
//     * wille be stored into SysError estructure, so it can be consulted.
//     *
//     * If there are errors, the first one will be prompted.
//     */
//    int errcount = zbe::SysError::getNErrors();
//    if(errcount>0){
//        printf("Error: %s",zbe::SysError::getFirstErrorString().c_str());fflush(stdout);
//    }
//    window.present();
//  }
//
//  return 0;
//}
#include <cinttypes>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "ZBE/core/daemons/DaemonMaster.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/implementations/SimpleCollisioner.h"
#include "ZBE/core/events/generators/GeneratorMaster.h"
#include "ZBE/core/events/generators/Generator.h"
#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/Actuator.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/Timer.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/daemons/Punishers.h"
#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"
#include "ZBE/SDL/system/Window.h"
#include "ZBE/SDL/drawers/SimpleSpriteSDLDrawer.h"
#include "ZBE/entities/adaptors/SimpleDrawableSimpleSpriteAdaptor.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/behaviors/Bounce.h"
#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/MobileAPO.h"

#include "gamemain.h"
#include "game/GameReactor.h"
#include "game/entities/GameBall.h"
#include "game/entities/GameBoard.h"
#include "game/entities/GameBlock.h"
#include "game/entities/adaptors/GameBallCollisionatorAdaptor.h"
#include "game/events/handlers/StepInputHandler.h"
#include "game/events/handlers/ExitInputHandler.h"
#include "game/events/handlers/GameBallBouncer.h"
#include "batis/events/handlers/MKBallInputHandler.h"
#include "batis/events/handlers/MouseXKeepInputHandler.h"
#include "batis/events/handlers/MouseYKeepInputHandler.h"

#define PI 3.14159265

int batismain(int, char** ) {

  printf("--- GAME main ---\n\n");

  enum {
    GENERATORLIST = 1,

    INPUTEVENT = 0,
    COLLISIONEVENT = 1,
    TIMEEVENT = 2,

    COLLISIONATORLIST = 1,
    MOVABLELIST = 1,
    BOUNCERLIST = MOVABLELIST,
    BALLACTUATORLIST = 1,
    COLLISIONABLELIST = 1,
    BOARDACTUATORLIST = 1,
    BRICKACTUATORLIST = 2,
    SPRITELIST = 1,

    WIDTH = 1024,
    HEIGHT = 768
  };

  const char ballfilename[] = "data/images/zombieball/zomball_st_32.png";
  const char brickfilename[] = "data/images/zombieball/braikn_32.png";
  uint64_t ballgraphics;
  uint64_t brickgraphics;

  printf("3 / 5 %d\n", 3/5);fflush(stdout);
  printf("2 / 5 %d\n", 2/5);fflush(stdout);

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

  printf("|------------------- Collision Event Generator-------------|\n");fflush(stdout);
  printf("Building list for collisionator entinties. Currently empty.\n");fflush(stdout);
  printf("It will store entities that will search for a collision.\n");fflush(stdout);
  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<game::GameReactor> >*> ctl;
  printf("Acquiring singleton list-manager for this list (ctl).\n");fflush(stdout);
  zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<game::GameReactor> >*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<game::GameReactor> >*> >::getInstance();
  printf("Storing ctl in that list-manager.\n");fflush(stdout);
  lmct.insert(COLLISIONATORLIST, &ctl);
  printf("Building collision event generator with list id and the event id to use (1).\n");fflush(stdout);
  zbe::CollisionEventGenerator<game::GameReactor> ceg(COLLISIONATORLIST, COLLISIONEVENT);
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
  std::forward_list<zbe::AvatarEntity<zbe::SimpleSprite>*> sprites;
  zbe::ListManager< std::forward_list<zbe::AvatarEntity<zbe::SimpleSprite >*> >& lmAESimpleSprite = zbe::ListManager<std::forward_list<zbe::AvatarEntity<zbe::SimpleSprite >*> >::getInstance();
  lmAESimpleSprite.insert(SPRITELIST, &sprites);
  printf("Loading imgs\n");fflush(stdout);
  ballgraphics = window.loadImg(ballfilename);
  brickgraphics = window.loadImg(brickfilename);
  printf("Building the drawer to paint SimpleSprite's \n");fflush(stdout);
  std::shared_ptr<zbe::Daemon> drawerDaemon(new  zbe::DrawerDaemon<zbe::SimpleSprite, std::forward_list<zbe::AvatarEntity<zbe::SimpleSprite >*> >(std::make_shared<zbe::SimpleSpriteSDLDrawer>(&window), SPRITELIST));
  drawMaster.addDaemon(drawerDaemon);

  printf("|-------------------- Daemons ----------------------|\n");fflush(stdout);
  zbe::TimedDaemonMaster behavMaster;
  std::vector<zbe::AvatarEntity<zbe::Movable<2> >*> vAEMovable;
  zbe::ListManager< std::vector<zbe::AvatarEntity<zbe::Movable<2> >*> >& lmAEMovable = zbe::ListManager< std::vector<zbe::AvatarEntity<zbe::Movable<2> >*> >::getInstance();
  lmAEMovable.insert(MOVABLELIST, &vAEMovable);
  std::vector<zbe::AvatarEntity<zbe::Bouncer<2> >*> vAEBouncer;
  zbe::ListManager< std::vector<zbe::AvatarEntity<zbe::Bouncer<2> >*> >& lmAEBouncer = zbe::ListManager< std::vector<zbe::AvatarEntity<zbe::Bouncer<2> >*> >::getInstance();
  lmAEBouncer.insert(BOUNCERLIST, &vAEBouncer);
  std::shared_ptr<zbe::TimedDaemon> ballBounce(new  zbe::BehaviorDaemon<zbe::Bouncer<2>, std::vector<zbe::AvatarEntity<zbe::Bouncer<2> >*> >(std::make_shared<zbe::Bounce<2> >(), BOUNCERLIST));
  std::shared_ptr<zbe::TimedDaemon> ballULM(new  zbe::BehaviorDaemon<zbe::Movable<2>, std::vector<zbe::AvatarEntity<zbe::Movable<2> >*> >(std::make_shared<zbe::UniformLinearMotion<2> >(), MOVABLELIST));
  behavMaster.addDaemon(ballULM);
  behavMaster.addDaemon(ballBounce);

  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
  printf("Creating a ball and giving it a position and size\n");fflush(stdout);

  //ball
  std::forward_list< zbe::Actuator< zbe::Bouncer<2>, game::GameReactor >*> ballActuatorsList;
  zbe::ListManager< std::forward_list< zbe::Actuator< zbe::Bouncer<2>, game::GameReactor >* > >& lmBallActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator< zbe::Bouncer<2>, game::GameReactor >* > >::getInstance();
  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
  game::GameBallBouncer gbBouncer;
  ballActuatorsList.push_front(&gbBouncer);

  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<game::GameReactor> >* > collisionablesList;
  zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<game::GameReactor> >* > >& lmCollisionablesList = zbe::ListManager< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisioner<game::GameReactor> >* > >::getInstance();
  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);

  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
  game::ExitInputHandler terminator;
  ieg.addHandler(zbe::ZBEK_ESCAPE, &terminator);

  std::forward_list<game::GameBall*> balls;
  for(int i = 0; i<1000 ; i++){//98.623993, 85.728439

    int64_t vt = 200;

    int minAngle = 0;
    int maxAngle = 360;

    double vAngleL = (minAngle * 10) + rand()%((maxAngle-minAngle)*10);
    vAngleL/=10;
    double vAngleR = rand()%10000;
    vAngleR/=100000;
    double vAngle = vAngleL + vAngleR;
    int64_t vx = sin(vAngle*PI/180)*vt;
    int64_t vy = cos(vAngle*PI/180)*vt;

    game::GameBall* ball = new game::GameBall(WIDTH/2, HEIGHT/2, 16 , vx, vy, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
    std::shared_ptr<zbe::Adaptor<zbe::SimpleSprite> > spriteAdaptor = std::make_shared<zbe::SimpleDrawableSimpleSpriteAdaptor>(ball);
    ((zbe::AvatarEntityAdapted<zbe::SimpleSprite>*)ball)->setAdaptor(spriteAdaptor);
    std::shared_ptr<zbe::Adaptor<zbe::Collisionator<game::GameReactor> > > gbca = std::make_shared<game::GameBallCollisionatorAdaptor>(ball);
    ((zbe::AvatarEntityAdapted<zbe::Collisionator<game::GameReactor> >*)ball)->setAdaptor(gbca);
    ctl.push_front(ball);
    vAEMovable.push_back(ball);
    vAEBouncer.push_back(ball);
    balls.push_front(ball);
    sprites.push_front(ball);
  }

  printf("Creating the bricks\n");fflush(stdout);
  //bricks
  zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >& lmSimpleConerActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >::getInstance();
  std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> brickActuatorsList;
  lmSimpleConerActuatorsList.insert(BRICKACTUATORLIST, &brickActuatorsList);
  for(int i = 0; i<8 ; i++){
      for(int j = 0; j<8 ; j++){
          game::GameBlock *brick = new game::GameBlock(i*51+ 100, j*32 + 100, 51, 32, brickgraphics, BRICKACTUATORLIST);
          std::shared_ptr<zbe::Adaptor<zbe::SimpleSprite> > spriteAdaptor = std::make_shared<zbe::SimpleDrawableSimpleSpriteAdaptor>(brick);
          ((zbe::AvatarEntityAdapted<zbe::SimpleSprite>*)brick)->setAdaptor(spriteAdaptor);
          collisionablesList.push_front(brick);
          sprites.push_front(brick);
      }
  }

  printf("Creating the board and giving it a size\n");fflush(stdout);
  //board
  std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> boardActuatorsList;
  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, &boardActuatorsList);
  game::GameBoard board(0, 0, WIDTH, HEIGHT, BOARDACTUATORLIST);
  collisionablesList.push_front(&board);

  printf("|=================== Starting up system ===================|\n");fflush(stdout);
  printf("Starting SysTimer\n");fflush(stdout);
  sysTimer->start();
  printf("Acquiring sdl info for the first time\n");fflush(stdout);
  printf("Input data will be stored into the InputReader\n");fflush(stdout);
  sdlEventDist.run();
  printf("Updating system time.\n");fflush(stdout);
  sysTime.update();
  printf("Acquiring initial times.\n");fflush(stdout);
  int64_t endT = sysTime.getTotalTime();// instant at which the frame ends
  int64_t initT = 0;//Lets start
  printf("|==========================================================|\n");fflush(stdout);
  printf("initT = 0x%" PRIx64 " ", initT);fflush(stdout);
  printf("endT = 0x%" PRIx64 "\n", endT);fflush(stdout);

  int64_t maxFrameTime = zbe::SECOND / 64;

  bool keep = true;
  while(keep){

    /* Clear screen.
     */
    window.clear();

    /* Acquiring sdl info
     * Input data will be stored into the InputReader
     */
    sdlEventDist.run();

    /* Updating system time.
     */
    sysTime.update();

    /* Reading that updated time info
     */
    initT = endT;// init time
    endT = sysTime.getTotalTime(); //initT + (int64_t(1) << zbe::PRECISION_DIGITS); // instant at which the frame ends

    if((endT - maxFrameTime)>initT){
      initT = endT - maxFrameTime;
    }

    while (initT < endT) {
      /* Generating events
       */
      gema.generate(initT,endT);

      int64_t eventTime = store.getTime();
      if (eventTime <= endT) {
        store.manageCurrent();
        behavMaster.run(eventTime-initT);
        initT = eventTime;
      } else {
        behavMaster.run(endT-initT);
        store.clearStore();
        initT = endT;
      }
    }

    drawMaster.run();

    /* If one or more error occurs, the ammount and the first one
     * wille be stored into SysError estructure, so it can be consulted.
     *
     * If there are errors, the first one will be prompted.
     */
    int errcount = zbe::SysError::getNErrors();
    if(errcount>0){
        printf("Error: %s",zbe::SysError::getFirstErrorString().c_str());fflush(stdout);
    }
    window.present();
  }

  return 0;
}
