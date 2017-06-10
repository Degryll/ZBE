/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDL_SDLWindow.cpp
 *
 * @since 2015/05/30
 * @date 2017/04/13
 * @author Degryll
 * @brief Create a SDLWindows using SDL 2.0.
 */

#include "ZBE/SDL/system/SDLWindow.h"

#include <string>
#include <SDL2/SDL_image.h>

namespace zbe {

SDLWindow::SDLWindow(int width, int height, Uint32 window_flags) : sdl(SDL_Starter::getInstance(SDL_INIT_VIDEO)), window(0), renderer(0), output(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height)), ntextures(0), imgCollection(), nfonts(0), fontCollection(), m(), mf() {
  if(SDL_CreateWindowAndRenderer(width, height, window_flags, &window, &renderer)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not create a SDLWindow and/or a renderer! SDL ERROR: ") + SDL_GetError());
  }
}

SDLWindow::SDLWindow(const char* title, int width, int height, Uint32 SDLWindow_flags, Uint32 rederer_flags)
  : SDLWindow(title, 0, 0, width, height, SDLWindow_flags, rederer_flags){}

SDLWindow::SDLWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags, Uint32 rederer_flags)
       : sdl(SDL_Starter::getInstance(SDL_INIT_VIDEO)), window(SDL_CreateWindow(title, x, y, width, height, window_flags)),
         renderer(SDL_CreateRenderer(window, -1, rederer_flags)),
         output(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height)),
         ntextures(0), imgCollection(), nfonts(0), fontCollection(), m(), mf() {

  if (window == nullptr){
    zbe::SysError::setError(std::string("ERROR: SDL could not create a SDLWindow! SDL ERROR: ") + SDL_GetError());
  }
  if (renderer == nullptr){
    SDL_DestroyWindow(window);
    zbe::SysError::setError(std::string("ERROR: SDL could not create a renderer! SDL ERROR: ") + SDL_GetError());
  }
}

SDLWindow::~SDLWindow() {
  for(auto iter = imgCollection.begin(); iter != imgCollection.end(); iter++ ) {
    SDL_DestroyTexture(*iter);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  sdl.quitSubSystem(SDL_INIT_VIDEO);
}

void SDLWindow::clear() {
  if(SDL_RenderClear(renderer)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not clear the SDLWindow! SDL ERROR: ") + SDL_GetError());
  }
}

void SDLWindow::render(uint64_t texID, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
  if(SDL_RenderCopy(renderer, imgCollection[texID], srcrect, dstrect)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
  }
}

void SDLWindow::render(uint64_t texID, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
  if(SDL_RenderCopyEx(renderer, imgCollection[texID], srcrect, dstrect, angle, center, flip)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the texture! SDL ERROR: ") + SDL_GetError());
  }
}

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

void SDLWindow::render(uint64_t fontID, const char *text, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
  ZBE_Font font = fontCollection[fontID];
  SDL_Surface * s = TTF_RenderUTF8_Solid(font.font, text, font.color);
  SDL_Texture * t = SDL_CreateTextureFromSurface(renderer, s);
  if(!s) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the surface! SDL ERROR: ") + SDL_GetError());
    return;
  }
  if(SDL_RenderCopy(renderer, t, srcrect, dstrect)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the text! SDL ERROR: ") + SDL_GetError());
  }
  if(s) SDL_FreeSurface(s);
  if(t) SDL_DestroyTexture(t);
}

void SDLWindow::render(uint64_t fontID, const char *text, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
  ZBE_Font font = fontCollection[fontID];
  SDL_Surface * s = TTF_RenderUTF8_Solid(font.font, text, font.color);
  SDL_Texture * t = SDL_CreateTextureFromSurface(renderer, s);
  if(SDL_RenderCopyEx(renderer, t, srcrect, dstrect, angle, center, flip)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the text! SDL ERROR: ") + SDL_GetError());
  }
  if(s) SDL_FreeSurface(s);
  if(t) SDL_DestroyTexture(t);
}

uint64_t SDLWindow::loadImg(const char *url) {
  m.lock();
    imgCollection.push_back(IMG_LoadTexture(renderer, url));
    uint64_t rid = ntextures++;  // Avoid race condition
  m.unlock();

  return (rid);
}

uint64_t SDLWindow::loadImg(const char *data, int width, int height, int depth, int pitch) {
  Uint32 rmask, gmask, bmask;
  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0x00ff0000;
    gmask = 0x0000ff00;
    bmask = 0x000000ff;
  #else // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
  #endif

  SDL_Surface* s = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch, rmask, gmask, bmask, 0xff);

  SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);

  SDL_FreeSurface(s);

  m.lock();
    imgCollection.push_back(t);
    uint64_t rid = ntextures++;  // Avoid race condition
  m.unlock();

  return (rid);
}

uint64_t SDLWindow::reloadImg(const char *url, uint64_t id) {
  m.lock();
    if (id >= ntextures) {
      zbe::SysError::setError(std::string("ERROR: Can't reload Texture: ") + std::to_string(id) + std::string(". Texture doesn't exist."));
    } else {
      imgCollection[id] = IMG_LoadTexture(renderer, url);
    }
  m.unlock();

  return (id);
}

uint64_t SDLWindow::loadText(char *text, TTF_Font *font, SDL_Color color) {
  m.lock();
    SDL_Surface* surface;
    surface = TTF_RenderUTF8_Solid(font, text, color);
    imgCollection.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    uint64_t rid = ntextures++;  // Avoid race condition
  m.unlock();

  return (rid);
}

uint64_t SDLWindow::loadFont(const char *fontName, int size, SDL_Color color) {
  mf.lock();
  	ZBE_Font font;
  	font.font = TTF_OpenFont(fontName, size);
  	font.color = color;

    fontCollection.push_back(font);
    uint64_t rid = nfonts++;  // Avoid race condition
  mf.unlock();

  return (rid);
}

}  // namespace zbe
