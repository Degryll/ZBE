#include "gtest/gtest.h"

#include <SDL2/SDL.h>
#include <climits>
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputStatus.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

TEST(SDLEventDispatcher, SDLEventDispatcher) {
  //  SDL context initialization
  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    FAIL()<< "SDL_Init Error: " << SDL_GetError() << std::endl;
  }
  //  Three events. Mouse movement must generate two outputs
  SDL_Event user_event0 = {};
  user_event0.type = SDL_KEYDOWN;
  user_event0.key.keysym.sym = SDLK_RIGHT;
  user_event0.key.timestamp = 1;
  printf("timestamp: %u\n", user_event0.key.timestamp); fflush(stdout);
  SDL_Event user_event1 = {};
  user_event1.type = SDL_KEYUP;
  user_event1.key.keysym.sym = SDLK_LEFT;
  user_event1.key.timestamp = 2;
  SDL_Event user_event2 = {};
  user_event2.type = SDL_MOUSEMOTION;
  user_event2.motion.x = 100;
  user_event2.motion.y = 100;
  user_event2.key.timestamp = 1;

  SDL_PushEvent(&user_event0);
  SDL_PushEvent(&user_event1);
  SDL_PushEvent(&user_event2);

  zbe::SDLEventDispatcher &sed = zbe::SDLEventDispatcher::getInstance();
  std::shared_ptr<zbe::InputBuffer> ib = sed.getInputBuffer();
  printf("INI:\n"); fflush(stdout);
  sed.run();
  std::vector<zbe::InputStatus> input;
  // So 4 outputs are expected
  ib->getRange(0, UINT_MAX, input);
  EXPECT_EQ(input.size(),4)<< "4 inputStatus must be found";

  SDL_Quit();
}
