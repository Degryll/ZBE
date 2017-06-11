/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLTextFontStore.cpp
 *
 * @since 2015/05/30
 * @date 2017/06/11
 * @author Degryll Ludo
 * @brief Create a SDLWindows using SDL 2.0.
 */

#include "ZBE/SDL/system/SDLTextFontStore.h"

#include <string>
#include <SDL2/SDL_image.h>

namespace zbe {

SDLTextFontStore::SDLTextFontStore(SDLImageStore* imageStore, SDL_Renderer* renderer) : nfonts(0), fontCollection(), m(), mf(), imageStore(imageStore), renderer(renderer) {}

uint64_t SDLTextFontStore::loadText(char *text, TTF_Font *font, SDL_Color color) {
  m.lock();
    SDL_Surface* surface;
    surface = TTF_RenderUTF8_Solid(font, text, color);
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
  SDL_Surface * s = TTF_RenderUTF8_Solid(font.font, text, font.color);
  if(!s) {
    zbe::SysError::setError(std::string("ERROR: SDL could not render the surface! SDL ERROR: ") + SDL_GetError());
    return nullptr;
  }
  SDL_Texture * t = SDL_CreateTextureFromSurface(renderer, s);
  if(s) SDL_FreeSurface(s);
  return t;
}

}  // namespace zbe
