
#include "ludomain.h"
#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/TimeEvent.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/CollisionEvent2D.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/CollisionEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/core/tools/Timer.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include <cinttypes>
#include <iostream>
#include <chrono>
#include <thread>


int ludomain(int , char** ) {
  printf("--- Ludo main ---\n\n");

  getchar();

  // Starting sdl systems.
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  // Creating a sdl window
  SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (win == nullptr){
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  printf("|=================== Building up system ===================|\n");fflush(stdout);
  printf("Event store\n");fflush(stdout);
  printf("Will store all event independently of its type\n");fflush(stdout);
  zbe::EventStore& store = zbe::EventStore::getInstance();
  printf("|------------------------ Input ---------------------------|\n");fflush(stdout);
  printf("Building SDLEventDispatcher\n");fflush(stdout);
  printf("Will extract data from SDL and get it usable for the engine\n");fflush(stdout);
  zbe::SDLEventDispatcher & sdlEventDist = zbe::SDLEventDispatcher::getInstance();
  printf("Acquiring InputBuffer\n");fflush(stdout);
  printf("SDLEventDispatcher Will store input changes for a frame into it\n");fflush(stdout);
  zbe::InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
  printf("Acquiring and configuring InputEventGenerator with that InputReader\n");fflush(stdout);
  printf("Will read events from the InputReader and send them to the store\n");fflush(stdout);
  printf("Input events will use id 0\n");fflush(stdout);
  zbe::InputEventGenerator* ieg = new zbe::InputEventGenerator(inputBuffer,0);
  printf("|------------------------- Time ---------------------------|\n");fflush(stdout);
  printf("Building a SDL implementation of Timer\n");fflush(stdout);
  zbe::Timer *sysTimer = new zbe::SDLTimer(true);
  printf("Acquiring and configuring SysTime with that Timer\n");fflush(stdout);
  printf("It will be the time reference for all the game context\n");fflush(stdout);
  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
  sysTime.setSystemTimer(sysTimer);
  printf("|------------------------ Phisics -------------------------|\n");fflush(stdout);
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

    /* sleeping to simulate some work.
     */
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

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
    printf("initT = 0x%" PRIx64 " ", initT);fflush(stdout);
    printf("endT = 0x%" PRIx64 "\n", endT);fflush(stdout);

    /* Generating input events:
     * It will take the events that sdlEventDist has stored
     * into the InputReader and send it to the event store.
     */
    ieg->generate(initT,endT);

    /* Time for look for those events!
     * the closest input event (or events) found must be now
     * on the event store.
     */
    const std::forward_list<zbe::Event*> & eventList = store.getEvents();

    /* If there are event, we need to do something about it!
     * For example... exit the program.
     */
    if(!eventList.empty()){
      for ( auto it = eventList.begin(); it != eventList.end(); ++it ) {
        zbe::InputEvent *e = (zbe::InputEvent*) (*it);
        printf(" -> T = 0x%" PRIx64 " ", e->getTime());fflush(stdout);
        printf("K = 0x%" PRIx32 " ", e->getKey());fflush(stdout);
        printf("S = 0x%f\n", e->getState());fflush(stdout);
        if(e->getKey() == 0x78){
          keep = false;
        }
      }
    }

    store.clearStore();

    /* If one or more error occurs, the ammount and the first one
     * wille be stored into SysError estructure, so it can be consulted.
     *
     * If there are errors, the first one will be prompted.
     */
    int errcount = zbe::SysError::getNErrors();
    if(errcount>0){
        printf("Error: %s",zbe::SysError::getFirstErrorString().c_str());fflush(stdout);
    }
  }

  return 0;
}
