/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDL_Window.cpp
 *
 * @since 2015/05/30
 * @date 2016-08-04
 * @author Degryll
 * @brief Create a windows using SDL 2.0.
 */

#include "ZBE/core/system/SDL/Window.h"

#include <string>
#include <SDL2/SDL_image.h>

#include "ZBE/core/starters/SDL/SDL_Starter.h"
#include "ZBE/core/system/SysError.h"


namespace zbe {

Window::Window(int width, int height, Uint32 window_flags) : window(0), renderer(0), ntextures(0), imgCollection(), m() {
  SDL_Starter::getInstance(SDL_INIT_VIDEO);
  if(SDL_CreateWindowAndRenderer(width, height, window_flags, &window, &renderer)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not create a window and/or a renderer! SDL ERROR: ") + SDL_GetError());
  }
}

Window::Window(const char* title, int width, int height, Uint32 window_flags, Uint32 rederer_flags)
  : Window(title, 0, 0, width, height, window_flags, rederer_flags){

  SDL_Starter::getInstance(SDL_INIT_VIDEO);
}

Window::Window(const char* title, int x, int y, int width, int height, Uint32 window_flags, Uint32 rederer_flags)
       : window(SDL_CreateWindow(title, x, y, width, height, window_flags)),
         renderer(SDL_CreateRenderer(window, -1, rederer_flags)),
         ntextures(0), imgCollection(), m() {

  SDL_Starter::getInstance(SDL_INIT_VIDEO);

  if (window == nullptr){
    zbe::SysError::setError(std::string("ERROR: SDL could not create a window! SDL ERROR: ") + SDL_GetError());
  }
  if (renderer == nullptr){
    SDL_DestroyWindow(window);
    zbe::SysError::setError(std::string("ERROR: SDL could not create a renderer! SDL ERROR: ") + SDL_GetError());
  }
}

Window::~Window() {
  for(auto iter = imgCollection.begin(); iter != imgCollection.end(); iter++ ) {
    SDL_DestroyTexture(*iter);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Window::clear() {
  if(SDL_RenderClear(renderer)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not clear the window! SDL ERROR: ") + SDL_GetError());
  }
}

void Window::setBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
  if(SDL_SetRenderDrawColor(renderer, red, green, blue, alpha)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not set the background color! SDL ERROR: ") + SDL_GetError());
  }
}

void Window::render(unsigned texID, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
  if(SDL_RenderCopy(renderer, imgCollection[texID], srcrect, dstrect)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
  }
}

void Window::render(unsigned texID, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
  if(SDL_RenderCopyEx(renderer, imgCollection[texID], srcrect, dstrect, angle, center, flip)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
  }
}

unsigned Window::loadImg(const char *url) {
  m.lock();
    imgCollection.push_back(IMG_LoadTexture(renderer, url));
    unsigned rid = ntextures++;  // Avoid race condition
  m.unlock();

  return (rid);
}

unsigned Window::reloadImg(const char *url, unsigned id) {
  m.lock();
    if (id >= ntextures) {
      zbe::SysError::setError(std::string("ERROR: Can't reload Texture: ") + std::to_string(id) + std::string(". Texture doesn't exist."));
    } else {
      imgCollection[id] = IMG_LoadTexture(renderer, url);
    }
  m.unlock();

  return (id);
}

}  // namespace zbe
