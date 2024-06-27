/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDL_Window.cpp
 * @since 2015-05-30
 * @date 2018-03-28
 * @author Degryll Ludo Batis
 * @brief Create a SDLWindows using SDL 2.0.
 */

#include "ZBE/SDL/system/SDLWindow.h"

#include <string>

#include <SDL3/SDL_image.h>

namespace zbe {

SDLWindow::SDLWindow(const char* title, int width, int height, Uint32 SDLWindow_flags, Uint32 renderer_flags)
  : SDLWindow(title, 0, 0, width, height, SDLWindow_flags, renderer_flags) {}

SDLWindow::SDLWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags, Uint32 renderer_flags)
       : title(title), x(x), y(y), width(width), height(height), window_flags(window_flags), renderer_flags(renderer_flags),
         sdl(SDL_Starter::getInstance(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER)), window(SDL_CreateWindow(title, x, y, width, height, window_flags)),
         renderer(SDL_CreateRenderer(window, -1, renderer_flags)),
         output(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height)),
         imgStore(std::make_shared<SDLImageStore>(renderer)), fontStore(std::make_shared<SDLTextFontStore>(imgStore, renderer)) {

  SDL_CaptureMouse(SDL_TRUE);
  checkWidowCreation();
}

SDLWindow::~SDLWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  sdl.quitSubSystem(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
}

void SDLWindow::run() {
  window = SDL_CreateWindow(title, x, y, width, height, window_flags);
  renderer = SDL_CreateRenderer(window, -1, renderer_flags);
  output = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
  imgStore = std::make_shared<SDLImageStore>(renderer);
  fontStore = std::make_shared<SDLTextFontStore>(imgStore, renderer);

  checkWidowCreation();
}


void SDLWindow::clear() {
  if(SDL_RenderClear(renderer)) {
    zbe::SysError::setError(std::string("ERROR: SDL could not clear the SDLWindow! SDL ERROR: ") + SDL_GetError());
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

SDLImageStore::SDLImageStore(SDL_Renderer* renderer): ntextures(0), imgCollection(), m(), renderer(renderer) {
  imgCollection.push_back(nullptr);  // Id zero is discouraged
}

SDLImageStore::~SDLImageStore(){
  // ++ Because id zero is discouraged, element zero is avoided
  for(auto iter = ++(imgCollection.begin()); iter != imgCollection.end(); iter++ ) {
    SDL_DestroyTexture(*iter);
  }
}

uint64_t SDLImageStore::loadImg(const char *url) {
  SDL_Texture * texture = IMG_LoadTexture(renderer, url);
  if(!texture) {
    zbe::SysError::setError(std::string("ERROR: Can't reload Texture: ") + url + std::string(". IMG_LoadTexture return null and say:") + SDL_GetError());
  }
  return storeTexture(texture);
}

uint64_t SDLImageStore::storeTexture(SDL_Texture * texture) {
  m.lock();
    imgCollection.push_back(texture);
    ntextures++;  // Avoid race condition
  m.unlock();
  return (ntextures);
}

uint64_t SDLImageStore::loadImg(const char *data, int width, int height, int depth, int pitch) {
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
    ntextures++;  // Avoid race condition
  m.unlock();

  return (ntextures);
}

uint64_t SDLImageStore::reloadImg(const char *url, uint64_t id) {
  m.lock();
    if (id >= ntextures) {
      zbe::SysError::setError(std::string("ERROR: Can't reload Texture: ") + std::to_string(id) + std::string(". Texture doesn't exist."));
    } else {
      imgCollection[id] = IMG_LoadTexture(renderer, url);
    }
  m.unlock();

  return (id);
}

SDL_Texture* SDLImageStore::getTexture(uint64_t id) {
    return imgCollection.at(id);
}


SDLTextFontStore::SDLTextFontStore(std::shared_ptr<SDLImageStore> imageStore, SDL_Renderer* renderer) : nfonts(0), fontCollection(), m(), mf(), imageStore(imageStore), renderer(renderer) {
    TTF_Init();
}

uint64_t SDLTextFontStore::loadText(char *text, TTF_Font *font, SDL_Color color) {
  m.lock();
    SDL_Surface* surface;
    surface = TTF_RenderUTF8_Blended(font, text, color);
    uint64_t rid = imageStore->storeTexture(SDL_CreateTextureFromSurface(renderer, surface));
  m.unlock();

  return (rid);
}

uint64_t SDLTextFontStore::loadFont(const char *fontName, int size, SDL_Color color) {
  mf.lock();
  	ZBE_Font font;
  	font.font = TTF_OpenFont(fontName, size);
  	font.color = color;
    fontCollection.push_back(font);
    uint64_t rid = nfonts++;  // Avoid race condition
  mf.unlock();

  return (rid);
}

SDL_Texture* SDLTextFontStore::renderText(uint64_t fontID, const char *text) {
  ZBE_Font font = fontCollection[fontID];
  SDL_Surface * s = TTF_RenderUTF8_Blended(font.font, text, font.color);
  if(!s) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the surface! SDL ERROR: ") + SDL_GetError());
    return nullptr;
  }
  SDL_Texture * t = SDL_CreateTextureFromSurface(renderer, s);
  if(s) SDL_FreeSurface(s);
  return t;
}

}  // namespace zbe
