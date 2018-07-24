#include "testing.h"


#include <algorithm>
#include <cstdio>
#include <fstream>
#include <set>
#include <vector>
#include <cstring>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vulkan/vulkan.h>

namespace testing {

int testingmain(int, char** ) {
  SDL_Window *window;                    // Declare a pointer

  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
      "An SDL2 window",                  // window title
      SDL_WINDOWPOS_UNDEFINED,           // initial x position
      SDL_WINDOWPOS_UNDEFINED,           // initial y position
      640,                               // width, in pixels
      480,                               // height, in pixels
      SDL_WINDOW_VULKAN                  // flags - see below
  );
  printf("ERRORS:%s\n", SDL_GetError());
  // Check that the window was successfully created
  if (window == NULL) {
      // In the case that the window could not be made...
      printf("Could not create window: %s\n", SDL_GetError());
      return 1;
  }
  printf("ERRORS:%s\n", SDL_GetError());


  int vkll = SDL_Vulkan_LoadLibrary(nullptr);

  SDL_DisplayMode mode;
  int dw = 0, dh = 0;

  printf("vkll:%d\n", vkll);
  printf("ERRORS:%s\n", SDL_GetError());

  SDL_GetCurrentDisplayMode(0, &mode);
  printf("bpp: %d - ERRORS:%s\n", SDL_BITSPERPIXEL(mode.format), SDL_GetError());
  SDL_GetWindowSize(window, &dw, &dh);
  printf("window: %d x %d - ERRORS:%s\n", dw, dh, SDL_GetError());
  SDL_Vulkan_GetDrawableSize(window, &dw, &dh);
  printf("vulkan: %d x %d - ERRORS:%s\n", dw, dh, SDL_GetError());

  // The window is open: could enter program loop here (see SDL_PollEvent())

  SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

  // Close and destroy the window
  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();
  return 0;
}

} //namespace Ludo
