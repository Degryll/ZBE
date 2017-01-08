/*
 * SDLFontLoader.cpp
 *
 *  Created on: 17/08/2012
 *      Author: ludo
 */

#include "ZBE/SDL/loaders/SDLFontLoader.h"

namespace zbe {

SDLFontLoader* SDLFontLoader::_instance = NULL;

SDLFontLoader* SDLFontLoader::createInstance() {
  _instance = new SDLFontLoader;
  _instance->fontCollection.clear();
  return (_instance);
}

void SDLFontLoader::deleteInstance() {
  for(auto iter = _instance->fontCollection.begin(); iter != _instance->fontCollection.end(); iter++ ) {
    TTF_Font* aux = iter->second;
    TTF_CloseFont(aux);
  }
  delete _instance;
}

SDLFontLoader* SDLFontLoader::getInstance() {
  return (_instance);
}

void zbe::SDLFontLoader::loadFont(const char *url,int size, int id) {
  std::map<int,TTF_Font*>::iterator it = fontCollection.find(id);
  if (it==fontCollection.end()) {
    fontCollection.insert(std::pair<int,TTF_Font*>(id, TTF_OpenFont(url, size)));
  }
}

void zbe::SDLFontLoader::reloadFont(const char *url,int size, int id) {
  removeFont(id);
  fontCollection.insert(std::pair<int,TTF_Font*>(id, TTF_OpenFont(url, size)));
}

void zbe::SDLFontLoader::removeFont(int id) {
  std::map<int,TTF_Font*>::iterator it = fontCollection.find(id);
  if (it!=fontCollection.end()) {
    TTF_Font*aux = it->second;
    TTF_CloseFont(aux);
    fontCollection.erase(id);
  }
}


TTF_Font* zbe::SDLFontLoader::getFont(int id) {
  std::map<int,TTF_Font*>::iterator it = fontCollection.find(id);
  TTF_Font* aux = 0;
  if (it!=fontCollection.end()) {
    aux = it->second;
  }
  return (aux);
}

}  // namespace zbe
