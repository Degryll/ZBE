/*
 * Copyright 2011 Batis Degryll Ludo
 * @file SDL_Window.cpp
 *
 * @since 2015/05/30
 * @date 2015/05/30
 * @author Degryll
 * @brief Create a windows using SDL 2.0.
 */

#include "ZBE/core/starters/SDL_Window.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

SDL_Window::(int width, int height, Uint32 window_flags) {
  if(SDL_CreateWindowAndRenderer(width, height, window_flags, &window, &renderer)) {
    zbe::SysError::setError("SDL ERROR: SDL could not create a window and/or a renderer!");
    // añadir al mensaje de error SDL_GetError()
  }
}

SDL_Window::SDL_Window(const char* title, int width, int height, Uint32 window_flags, Uint32 rederer_flags)
  : SDL_Window(title, 0, 0, width, height, window_flags, rederer_flags){}

SDL_Window::SDL_Window(const char* title, int x, int y, int width, int height, Uint32 window_flags, Uint32 rederer_flags) {
  window = SDL_CreateWindow(title, x, y, width, height, window_flags);
  if (window == nullptr){
    zbe::SysError::setError("SDL ERROR: SDL could not create a window!");
    // añadir al mensaje de error SDL_GetError()
  }
  renderer = SDL_CreateRenderer(window, -1, rederer_flags);
  if (renderer == nullptr){
    SDL_DestroyWindow(window);
    zbe::SysError::setError("SDL ERROR: SDL could not create a renderer!");
    // añadir al mensaje de error SDL_GetError()
  }
}

SDL_Window::~SDL_Window() {
  for(auto iter = imgCollection.begin(); iter != imgCollection.end(); iter++ ) {
    SDL_DestroyTexture(iter->second);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void SDL_Window::clear() {
  if(SDL_RenderClear(render)) {
    zbe::SysError::setError("SDL ERROR: SDL could not clear the window!");
    // añadir al mensaje de error SDL_GetError()
  }
}

void SDL_Window::render(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
  if(SDL_RenderCopy(render, texture, srcrect, dstrect)) {
    zbe::SysError::setError("SDL ERROR: SDL could not render the texture!");
    // añadir al mensaje de error SDL_GetError()
  }
}

void SDL_Window::render(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
  if(SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle, center, flip)) {
    zbe::SysError::setError("SDL ERROR: SDL could not render the texture!");
    // añadir al mensaje de error SDL_GetError()
  }
}

void SDL_Window::render(unsigned texID, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
  if(SDL_RenderCopy(render, imgCollection[texID], srcrect, dstrect)) {
    zbe::SysError::setError("SDL ERROR: SDL could not render the texture!");
    // añadir al mensaje de error SDL_GetError()
  }
}

void SDL_Window::render(unsigned texID, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
  if(SDL_RenderCopyEx(renderer, imgCollection[texID], srcrect, dstrect, angle, center, flip)) {
    zbe::SysError::setError("SDL ERROR: SDL could not render the texture!");
    // añadir al mensaje de error SDL_GetError()
  }
}

unsigned SDL_Window::loadImg(const char *url) {
  imgCollection.insert(IMG_LoadTexture(renderer, url));
}

unsigned SDL_Window::reloadImg(const char *url, int id) {
  imgCollection[id] = IMG_LoadTexture(renderer, url);
}

}  // namespace zbe
