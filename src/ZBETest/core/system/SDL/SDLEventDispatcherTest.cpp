#include "gtest/gtest.h"

#include <SDL2/SDL.h>

#include "ZBE/core/io/InputReader.h"
#include "ZBE/core/io/SDL/SDLInputReader.h"
#include "ZBE/core/system/SDL/SDLEventDispatcher.h"

TEST(SDLEventDispatcher, SDLEventDispatcher) {
  //  SDL context initialization
  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    FAIL()<< "SDL_Init Error: " << SDL_GetError() << std::endl;
  }
  //  Three events. Mouse movement must generate two outputs
  SDL_Event user_event = {};
  user_event.type = SDL_KEYDOWN;
  user_event.key.keysym.sym = SDLK_RIGHT;
  user_event.key.timestamp = 1;
  SDL_Event user_event1 = {};
  user_event1.type = SDL_KEYUP;
  user_event1.key.keysym.sym = SDLK_LEFT;
  user_event1.key.timestamp = 2;
  SDL_Event user_event2 = {};
  user_event2.type = SDL_MOUSEMOTION;
  user_event2.motion.x = 100;
  user_event2.motion.y = 100;
  user_event2.key.timestamp = 1;

  SDL_PushEvent(&user_event);
  SDL_PushEvent(&user_event1);
  SDL_PushEvent(&user_event2);

  zbe::InputReader * ir = zbe::SDLInputReader::getInstance();
  zbe::SDLEventDispatcher * sed = new zbe::SDLEventDispatcher();
  sed->run();
  // So 4 outputs are expected
  EXPECT_EQ(ir->changes()->size(),4u)<< "and event must be found";
  // Checking values
  EXPECT_EQ(ir->getStatus(zbe::ZBEK_MOUSE_OFFSET_X),100.0);
  EXPECT_EQ(ir->getStatus(zbe::ZBEK_MOUSE_OFFSET_Y),100.0);
  EXPECT_EQ(ir->getStatus(zbe::ZBEK_LEFT),0.0);
  EXPECT_EQ(ir->getStatus(zbe::ZBEK_RIGHT),1.0);
  // Checking values
  EXPECT_GE(ir->getTime(zbe::ZBEK_RIGHT),ir->getTime(zbe::ZBEK_LEFT));
  EXPECT_GE(ir->getTime(zbe::ZBEK_LEFT),ir->getTime(zbe::ZBEK_MOUSE_OFFSET_X));
}
