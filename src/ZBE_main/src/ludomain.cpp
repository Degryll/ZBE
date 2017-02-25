#include <cinttypes>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "ZBE/core/daemons/DaemonMaster.h"
#include "ZBE/core/entities/avatars/implementations/SimpleCollisioner.h"
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
#include "ZBE/entities/adaptors/implementations/SimpleDrawableSimpleSpriteAdaptor.h"
#include "ZBE/entities/adaptors/implementations/BaseSphereMCMAPOAdaptor.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/archetypes/Mobile.h"
#include "ZBE/archetypes/MobileAPO.h"
#include "ZBE/actuators/MovableBouncer.h"

#include "gamemain.h"
#include "game/GameReactor.h"
#include "game/entities/GameBall.h"
#include "game/entities/GameBoard.h"
#include "game/events/handlers/StepInputHandler.h"
#include "game/events/handlers/ExitInputHandler.h"
#include "game/events/handlers/GameBallBouncer.h"
#include "ludo/LudoReactor.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/events/handlers/LudoHandlers.h"
#include "ludo/events/handlers/LudoActuators.h"

int ludomain(int, char** ) {

  printf("--- GAME main ---\n\n");

  enum {
    INPUTEVENT = 0,
    COLLISIONEVENT = 1,
    TIMEEVENT = 2,

    COLLISIONATORLIST = 1,
    MOBILELIST = 1,
    BALLACTUATORLIST = 1,
    COLLISIONABLELIST = 1,
    BOARDACTUATORLIST = 1,

    WIDTH = 1024,
    HEIGHT = 768
  };

  const char zomballImg[] = "data/images/zombieball/zomball_st_32.png";
  const char simpleBallImg[] = "data/images/zombieball/simple_ball_32.png";
  const char mouseImg[] = "data/images/zombieball/mouse.png";
  unsigned ballgraphics[3];

  printf("3 / 5 %d\n", 3/5);fflush(stdout);
  printf("2 / 5 %d\n", 2/5);fflush(stdout);

  printf("|=================== Building up system ===================|\n");fflush(stdout);
  printf("Event store\n");fflush(stdout);
  printf("Will store all event independently of its type\n");fflush(stdout);
  zbe::EventStore& store = zbe::EventStore::getInstance();
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
  printf("|------------------- Collision Event Generator-------------|\n");fflush(stdout);
  //zbe::TicketedForwardList<zbe::CollisionerEntity<GameReactor>*> cnl;
  printf("Building list for collisionator entinties. Currently empty.\n");fflush(stdout);
  printf("It will store entities that will search for a collision.\n");fflush(stdout);
  zbe::TicketedForwardList<zbe::CollisionatorEntity<game::GameReactor>*> ctl;
  printf("Acquiring singleton list-manager for this list (ctl).\n");fflush(stdout);
  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<game::GameReactor>*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<game::GameReactor>*> >::getInstance();
  printf("Storing ctl in that list-manager.\n");fflush(stdout);
  lmct.insert(COLLISIONATORLIST, &ctl);
  printf("Building collision event generator with list id and the event id to use (1).\n");fflush(stdout);
  zbe::CollisionEventGenerator<game::GameReactor> ceg(COLLISIONATORLIST, COLLISIONEVENT);
  printf("|------------------- Time Event Generator -----------------|\n");fflush(stdout);
  printf("Building time event generator with the event id to use (2)\n");fflush(stdout);
  zbe::TimeEventGenerator teg(TIMEEVENT);
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
  ballgraphics[0] = window.loadImg(zomballImg);
  ballgraphics[1] = window.loadImg(simpleBallImg);
  ballgraphics[2] = window.loadImg(mouseImg);
  printf("Building the drawer to paint SimpleSprite's \n");fflush(stdout);
  zbe::SimpleSpriteSDLDrawer drawer(&window);
  printf("|-------------------- Daemons ----------------------|\n");fflush(stdout);
  zbe::DaemonMaster dMaster;
  std::vector<zbe::Mobile<2>*> vmobile;
  zbe::ListManager< std::vector<zbe::Mobile<2>*> >& lmmobile = zbe::ListManager< std::vector<zbe::Mobile<2>*> >::getInstance();
  lmmobile.insert(MOBILELIST, &vmobile);
  std::shared_ptr<zbe::Daemon> bball(new  zbe::BehaviorDaemon< zbe::Mobile<2>, std::vector<zbe::Mobile<2>*> >(new zbe::UniformLinearMotion<2>(), MOBILELIST));
  dMaster.addDaemon(bball);
  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
  printf("Creating a ball and giving it a position and size\n");fflush(stdout);

  //ball
  std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >*> ballActuatorsList;
  zbe::ListManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >* > >& lmBallActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<game::GameReactor, 2>, game::GameReactor >* > >::getInstance();
  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
  game::GameBallBouncer gbBouncer;
  ballActuatorsList.push_front(&gbBouncer);

  zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> collisionablesList;
  zbe::ListManager<zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >& lmCollisionablesList = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >::getInstance();
  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);

  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
  zbe::SimpleSpriteAdaptor<zbe::Drawable>* spriteAdaptor = new zbe::SimpleDrawableSimpleSpriteAdaptor();
  zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2> * movableCatorAdaptor = new zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2>();
  /*game::StepInputHandler ihright(&ball, 5, 0);
  game::StepInputHandler ihleft(&ball, -5, 0);
  ieg.addHandler(zbe::ZBEK_a, &ihleft);
  ieg.addHandler(zbe::ZBEK_d, &ihright);*/
  game::ExitInputHandler terminator;
  ieg.addHandler(zbe::ZBEK_RETURN, &terminator);

  int ballCount = 0;
  std::forward_list<game::GameBall*> balls;
  for(int i = 0; i<1 ; i++){
      unsigned graphId = ballgraphics[(rand()%3)];
      game::GameBall* ball = new game::GameBall((WIDTH/2 + rand()%100-50) << zbe::PRECISION_DIGITS ,(HEIGHT/2 + rand()%100-50) << zbe::PRECISION_DIGITS, 8 << zbe::PRECISION_DIGITS, (rand()%2000 - 1000) << zbe::PRECISION_DIGITS, (rand()%2000 - 1000) << zbe::PRECISION_DIGITS, BALLACTUATORLIST, COLLISIONABLELIST, graphId);
      //game::GameBall* ball = new game::GameBall(31407009,1063841, 16 << zbe::PRECISION_DIGITS, 1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
      ctl.push_front(ball);
      ball->setSimpleSpriteAdaptor(spriteAdaptor);
      ball->setMovableCollisionatorAdaptor(movableCatorAdaptor);
      vmobile.push_back(ball);
      balls.push_front(ball);
      ballCount++;
  }

  printf("Creating the board and giving it a size\n");fflush(stdout);
  //board
  std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> boardActuatorsList;
  zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >& lmBoardActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<game::GameReactor>, game::GameReactor>*> >::getInstance();
  lmBoardActuatorsList.insert(BOARDACTUATORLIST, &boardActuatorsList);

  game::GameBoard board((WIDTH) << zbe::PRECISION_DIGITS, (HEIGHT) << zbe::PRECISION_DIGITS, BOARDACTUATORLIST);
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

  bool keep = true;
  int i = 0;
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

    if((endT-initT)==0){
      continue;
    }
    if((endT - 32768)>initT){
      initT = endT - 32768;
    }

    while (initT < endT) {
      /* Generating input events:
       * It will take the events that sdlEventDist has stored
       * into the InputReader and send it to the event store.
       */
      ieg.generate(initT,endT);
      teg.generate(initT,endT);
      ceg.generate(initT,endT);

      int64_t eventTime = store.getTime();
      if (eventTime <= endT) {
        dMaster.run(eventTime-initT);
        store.manageCurrent();
        initT = eventTime;
      } else {
        dMaster.run(endT-initT);
        store.clearStore();
        initT = endT;
      }
    }

    for(auto b : balls){
        drawer.apply(b->getSimpleSprite().get());
    }
    if(!(i%100)){
        for(int i = 0; i<10 ; i++){
          unsigned graphId = ballgraphics[(rand()%3)];
          game::GameBall* ball = new game::GameBall((WIDTH/2 + rand()%100-50) << zbe::PRECISION_DIGITS ,(HEIGHT/2 + rand()%100-50) << zbe::PRECISION_DIGITS, 16 << zbe::PRECISION_DIGITS, (rand()%2000 - 1000) << zbe::PRECISION_DIGITS, (rand()%2000 - 1000) << zbe::PRECISION_DIGITS, BALLACTUATORLIST, COLLISIONABLELIST, graphId);
          //game::GameBall* ball = new game::GameBall(31407009,1063841, 16 << zbe::PRECISION_DIGITS, 1000 << zbe::PRECISION_DIGITS,1000 << zbe::PRECISION_DIGITS, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
          ctl.push_front(ball);
          ball->setSimpleSpriteAdaptor(spriteAdaptor);
          ball->setMovableCollisionatorAdaptor(movableCatorAdaptor);
          vmobile.push_back(ball);
          balls.push_front(ball);
          ballCount++;
        }
    }
    i++;
    if(!(ballCount%100)){
        printf("%d ",ballCount);
    }

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
