/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDL_Window.cpp
 *
 * @since 2015/05/30
 * @date 2017/06/11
 * @author Degryll Ludo
 * @brief Create a SDLWindows using SDL 2.0.
 */

#include "ZBE/SDL/system/SDLWindow.h"

#include <string>
#include <SDL2/SDL_image.h>

namespace zbe {

SDLWindow::SDLWindow(int width, int height, Uint32 window_flags)
  : sdl(SDL_Starter::getInstance(SDL_INIT_VIDEO)), window(0), renderer(0),
    output(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height)){
  if(SDL_CreateWindowAndRenderer(width, height, window_flags, &window, &renderer)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not create a SDLWindow and/or a renderer! SDL ERROR: ") + SDL_GetError());
  }
}

SDLWindow::SDLWindow(const char* title, int width, int height, Uint32 SDLWindow_flags, Uint32 rederer_flags)
  : SDLWindow(title, 0, 0, width, height, SDLWindow_flags, rederer_flags){}

SDLWindow::SDLWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags, Uint32 rederer_flags)
       : sdl(SDL_Starter::getInstance(SDL_INIT_VIDEO)), window(SDL_CreateWindow(title, x, y, width, height, window_flags)),
         renderer(SDL_CreateRenderer(window, -1, rederer_flags)),
         output(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height)) {

  if (window == nullptr){
    zbe::SysError::setError(std::string("ERROR: SDL could not create a SDLWindow! SDL ERROR: ") + SDL_GetError());
  }
  if (renderer == nullptr){
    SDL_DestroyWindow(window);
    zbe::SysError::setError(std::string("ERROR: SDL could not create a renderer! SDL ERROR: ") + SDL_GetError());
  }
}

SDLWindow::~SDLWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  sdl.quitSubSystem(SDL_INIT_VIDEO);
}

void SDLWindow::clear() {
  if(SDL_RenderClear(renderer)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not clear the SDLWindow! SDL ERROR: ") + SDL_GetError());
  }
}

//void SDLWindow::render(uint64_t texID, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
//  if(SDL_RenderCopy(renderer, imgCollection[texID], srcrect, dstrect)) {
//    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
//  }
//}
//
//void SDLWindow::render(uint64_t texID, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
//  if(SDL_RenderCopyEx(renderer, imgCollection[texID], srcrect, dstrect, angle, center, flip)) {
//    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
//  }
//}

void SDLWindow::render(SDL_Texture *tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
  if(SDL_RenderCopy(renderer, tex, srcrect, dstrect)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
  }
}

void SDLWindow::render(SDL_Texture *tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
  if(SDL_RenderCopyEx(renderer, tex, srcrect, dstrect, angle, center, flip)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
  }
}

void SDLWindow::render(SDL_Surface *surf, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
  if(SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, surf), srcrect, dstrect)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
  }
}

void SDLWindow::render(SDL_Surface *surf, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
  if(SDL_RenderCopyEx(renderer, SDL_CreateTextureFromSurface(renderer, surf), srcrect, dstrect, angle, center, flip)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
  }
}

//void SDLWindow::render(uint64_t fontID, const char *text, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
//  if(SDL_RenderCopy(renderer, t, srcrect, dstrect)) {
//    zbe::SysError::setError(std::string("ERROR: SDL could not render the text! SDL ERROR: ") + SDL_GetError());
//  }
//  if(t) SDL_DestroyTexture(t);
//}
//
//void SDLWindow::render(uint64_t fontID, const char *text, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
//  ZBE_Font font = fontCollection[fontID];
//  SDL_Surface * s = TTF_RenderUTF8_Solid(font.font, text, font.color);
//  SDL_Texture * t = SDL_CreateTextureFromSurface(renderer, s);
//  if(SDL_RenderCopyEx(renderer, t, srcrect, dstrect, angle, center, flip)) {
//    zbe::SysError::setError(std::string("ERROR: SDL could not render the text! SDL ERROR: ") + SDL_GetError());
//  }
//  if(s) SDL_FreeSurface(s);
//  if(t) SDL_DestroyTexture(t);
//}

}  // namespace zbe
