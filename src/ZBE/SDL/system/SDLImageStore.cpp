/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLImageStore.cpp
 *
 * @since 2015/05/30
 * @date 2017/06/11
 * @author Degryll Ludo
 * @brief Create a SDLWindows using SDL 2.0.
 */

#include "ZBE/SDL/system/SDLImageStore.h"

#include <string>
#include <SDL2/SDL_image.h>

namespace zbe {

SDLImageStore::SDLImageStore(SDL_Renderer* renderer): ntextures(0), imgCollection(), m(), mf(), renderer(renderer) { }

SDLImageStore::~SDLImageStore(){
  for(auto iter = imgCollection.begin(); iter != imgCollection.end(); iter++ ) {
    SDL_DestroyTexture(*iter);
  }
}

uint64_t SDLImageStore::loadImg(const char *url) {
  m.lock();
    imgCollection.push_back(IMG_LoadTexture(renderer, url));
    uint64_t rid = ntextures++;  // Avoid race condition
  m.unlock();

  return (rid);
}

uint64_t SDLImageStore::storeTexture(SDL_Texture * texture) {
  m.lock();
    imgCollection.push_back(texture);
    uint64_t rid = ntextures++;  // Avoid race condition
  m.unlock();

  return (rid);
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
    uint64_t rid = ntextures++;  // Avoid race condition
  m.unlock();

  return (rid);
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
    return imgCollection[id];
}

}  // namespace zbe
