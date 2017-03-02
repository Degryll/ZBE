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

#include "game/events/handlers/StepInputHandler.h"
#include "game/events/handlers/ExitInputHandler.h"

#include "ludo/LudoReactor.h"
#include "ludo/drawers/LudoDrawers.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/entities/LudoAvatars.h"
#include "ludo/entities/LudoAdaptors.h"
#include "ludo/events/handlers/LudoHandlers.h"
#include "ludo/events/handlers/LudoActuators.h"

#include "ludomain.h"

int ludomain(int, char** ) {

  printf("--- Ludo main ---\n\n");

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
  const char arrowImg[] = "data/images/ludo/arrow_r_000_32.png";
  unsigned ballgraphics[4];

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
  printf("Building list for collisionator entinties. Currently empty.\n");fflush(stdout);
  printf("It will store entities that will search for a collision.\n");fflush(stdout);
  zbe::TicketedForwardList<zbe::CollisionatorEntity<ludo::LudoReactor>*> ctl;
  printf("Acquiring singleton list-manager for this list (ctl).\n");fflush(stdout);
  zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<ludo::LudoReactor>*> >& lmct = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionatorEntity<ludo::LudoReactor>*> >::getInstance();
  printf("Storing ctl in that list-manager.\n");fflush(stdout);
  lmct.insert(COLLISIONATORLIST, &ctl);
  printf("Building collision event generator with list id and the event id to use (1).\n");fflush(stdout);
  zbe::CollisionEventGenerator<ludo::LudoReactor> ceg(COLLISIONATORLIST, COLLISIONEVENT);
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
  ballgraphics[3] = window.loadImg(arrowImg);
  printf("Building the drawer to paint SimpleSprite's \n");fflush(stdout);
  ludo::SimpleRotatedSpriteSDLDrawer drawer(&window);
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
  std::forward_list< zbe::Actuator< zbe::MovableCollisioner<ludo::LudoReactor, 2>, ludo::LudoReactor >*> ballActuatorsList;
  zbe::ListManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<ludo::LudoReactor, 2>, ludo::LudoReactor >* > >& lmBallActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator< zbe::MovableCollisioner<ludo::LudoReactor, 2>, ludo::LudoReactor >* > >::getInstance();
  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
  ludo::MovableCollisionerBouncer<ludo::LudoReactor> bBouncer;
  ballActuatorsList.push_front(&bBouncer);

  zbe::TicketedForwardList<zbe::CollisionerEntity<ludo::LudoReactor>*> collisionablesList;
  zbe::ListManager<zbe::TicketedForwardList<zbe::CollisionerEntity<ludo::LudoReactor>*> >& lmCollisionablesList = zbe::ListManager< zbe::TicketedForwardList<zbe::CollisionerEntity<ludo::LudoReactor>*> >::getInstance();
  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);

  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
  ludo::RotatedDrawableSimpleRotatedSpriteAdaptor* spriteAdaptor = new ludo::RotatedDrawableSimpleRotatedSpriteAdaptor();
  zbe::BaseSphereMCMAPOAdaptor<ludo::LudoReactor, 2> * movableCatorAdaptor = new zbe::BaseSphereMCMAPOAdaptor<ludo::LudoReactor, 2>();
  game::ExitInputHandler terminator;
  ieg.addHandler(zbe::ZBEK_RETURN, &terminator);

  int ballCount = 0;
  std::forward_list<ludo::LudoBall<ludo::LudoReactor>*> balls;
  for(int i = 0; i<100 ; i++){
      unsigned graphId = ballgraphics[(rand()%4)];
      //ludo::LudoBall<ludo::LudoReactor>* ball = new ludo::LudoBall<ludo::LudoReactor>((WIDTH/2 + rand()%100-50) ,(HEIGHT/2 + rand()%100-50) , 16 , (rand()%2000 - 1000), (rand()%2000 - 1000) , BALLACTUATORLIST, COLLISIONABLELIST, graphId);
      ludo::LudoBall<ludo::LudoReactor>* ball = new ludo::LudoBall<ludo::LudoReactor>((WIDTH/2 + rand()%100-50) ,(HEIGHT/2 + rand()%100-50) , 16 , (rand()%2000 - 1000), (rand()%2000 - 1000) , BALLACTUATORLIST, COLLISIONABLELIST, graphId);
      ctl.push_front(ball);
      ball->setSimpleRotatedSpriteAdaptor(spriteAdaptor);
      ball->setMovableCollisionatorAdaptor(movableCatorAdaptor);
      vmobile.push_back(ball);
      balls.push_front(ball);
      ballCount++;
  }

  printf("Creating the board and giving it a size\n");fflush(stdout);
  //board
  std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<ludo::LudoReactor>, ludo::LudoReactor>*> boardActuatorsList;
  zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<ludo::LudoReactor>, ludo::LudoReactor>*> >& lmBoardActuatorsList = zbe::ListManager< std::forward_list< zbe::Actuator<zbe::SimpleCollisioner<ludo::LudoReactor>, ludo::LudoReactor>*> >::getInstance();
  lmBoardActuatorsList.insert(BOARDACTUATORLIST, &boardActuatorsList);

  ludo::LudoBoard<ludo::LudoReactor> board((WIDTH), (HEIGHT), BOARDACTUATORLIST);
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
        drawer.apply(b->getSimpleRotatedSprite().get());
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
