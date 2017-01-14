#include <cinttypes>
#include <iostream>
#include <chrono>
#include <thread>

#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/Timer.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/daemons/Punishers.h"
#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"
#include "ZBE/SDL/system/Window.h"
#include "ZBE/SDL/drawers/SimpleSpriteSDLDrawer.h"
#include "ZBE/entities/adaptors/implementations/SimpleDrawableSimpleSpriteAdaptor.h"
#include "ZBE/entities/adaptors/implementations/BasePositionablePositionAdaptor.h"
#include "ZBE/behaviors/UniformLinearMotion.h"
#include "ZBE/archetypes/Mobile.h"

#include "gamemain.h"
#include "game/GameReactor.h"
#include "game/entities/GameBall.h"
#include "game/events/handlers/StepInputHandler.h"

int gamemain(int, char** ) {
  printf("--- GAME main ---\n\n");

  enum {
    INPUTEVENT = 0,
    COLLISIONEVENT = 1,
    TIMEEVENT = 2,

    COLLISIONATORLIST = 1
  };

  const char ballfilename[] = "data/images/zombieball/zomball_st_32.png";
  unsigned ballgraphics;

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
  zbe::Window window(640,480);
  ballgraphics = window.loadImg(ballfilename);
  printf("Building the drawer to paint SimpleSprite's \n");fflush(stdout);
  zbe::SimpleSpriteSDLDrawer drawer(&window);
  printf("|------------------- Creating entities --------------------|\n");fflush(stdout);
  printf("Creating a ball and giving it a position and size\n");fflush(stdout);
  game::GameBall ball(320,240,32,32,ballgraphics);
  printf("Building an sprite adaptor for the ball\n");fflush(stdout);
  zbe::SimpleSpriteAdaptor<zbe::Drawable>* spriteAdaptor = new zbe::SimpleDrawableSimpleSpriteAdaptor();
  ball.setSimpleSpriteAdaptor(spriteAdaptor);
  zbe::BasePositionablePositionAdaptor<2> * positionableAdaptor = new zbe::BasePositionablePositionAdaptor<2>();
  ball.setPositionableAdaptor(positionableAdaptor);
  game::StepInputHandler ihright(&ball, 5, 0);
  game::StepInputHandler ihleft(&ball, -5, 0);
  ieg.addHandler(zbe::ZBEK_a, &ihleft);
  ieg.addHandler(zbe::ZBEK_d, &ihright);
  std::vector<zbe::Mobile<2>*> vmobile;
  vmobile.push_back(&ball);
  zbe::ListManager< std::vector<zbe::Mobile<2>*> >& lmmobile = zbe::ListManager< std::vector<zbe::Mobile<2>*> >::getInstance();
  lmmobile.insert(1, &vmobile);
  zbe::BehaviorDaemon< zbe::Mobile<2>, std::vector<zbe::Mobile<2>*> > bball(new zbe::UniformLinearMotion<2>(), 1);
  printf("|=================== Starting up system ===================|\n");fflush(stdout);
  printf("Starting SysTimer\n");fflush(stdout);
  sysTimer->start();
  printf("Acquiring sdl info for the first time\n");fflush(stdout);
  printf("Input data will be stored into the InputReader\n");fflush(stdout);
  sdlEventDist.run();
  printf("Updating system time.\n");fflush(stdout);
  sysTime.update();
  printf("Acquiring initial times.\n");fflush(stdout);
  uint64_t endT = sysTime.getTotalTime();// instant at which the frame ends
  uint64_t initT = 0;//Lets start
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
    endT = sysTime.getTotalTime();// instant at which the frame ends
    //frameTime = sysTime.getFrameTime();// frame duration

    //printf("frameTime = 0x%" PRIx64 " ", frameTime);fflush(stdout);
    //printf("initT = 0x%" PRIx64 " ", initT);fflush(stdout);
    //printf("endT = 0x%" PRIx64 "\n", endT);fflush(stdout);

    //printf("init: %llu, end: %llu\n", initT, endT);
    while (initT < endT) {
      /* Generating input events:
       * It will take the events that sdlEventDist has stored
       * into the InputReader and send it to the event store.
       */
      ieg.generate(initT,endT);
      teg.generate(initT,endT);
      ceg.generate(initT,endT);

      uint64_t eventTime = store.getTime();
      if (eventTime <= endT) {
        bball.run(eventTime-initT);
        store.manageCurrent();
        initT = eventTime;
      } else {
        bball.run(endT-initT);
        store.clearStore();
        initT = endT;
      }
    }  // while frameTime

    drawer.apply(ball.getSimpleSprite().get());

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
